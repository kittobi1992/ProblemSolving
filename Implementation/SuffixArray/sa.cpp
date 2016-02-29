#include <bits/stdc++.h>
#include <iostream>

#include "../Trie/trie.cpp"

using namespace std;

typedef pair<int,int> ii;

class SuffixArray {

public:
  #define MAXN 100010
  typedef pair<int,int> rank;
  
  SuffixArray(string& s) : n(s.size()+1), s(s), sa(s.size()+1) {
    this->s = s + '$';
    memset(ra,0,sizeof(ra)); memset(temp_ra,0,sizeof(temp_ra)); memset(sa_idx,0,sizeof(sa_idx));
    memset(phi,0,sizeof(phi)); memset(lcp,0,sizeof(lcp)); memset(plcp,0,sizeof(plcp));
    for(int i = 0; i < sa.size(); i++)	{ sa[i] = i; sa_idx[i] = i; }
    sa = inducedSorting(this->s);
    //computeLCP();
  }
  
  int operator[](const int i) {
    return sa[i];
  }
  
  int getLcp(const int i) {
    return lcp[i];
  }
  
  //Returns range of suffixes, which prefixes match with pattern p (|p| = m). Time Complexity O(m*log(n))
  ii findPattern(string& p) {
    int m = p.size();
    int l = 0, r = n-1;
    //Search lower bound of range
    while(l < r) {
	int mid = (l+r)/2;
	if(strncmp(s.c_str() + sa[mid],p.c_str(),m) >= 0) r = mid;
	else l = mid+1;
    }
    if(strncmp(s.c_str() + sa[l],p.c_str(),m) != 0) return ii(-1,-1);
    ii res; res.first = l;
    l = 0; r = n-1;
    //Search upper bound of range
    while(l < r) {
	int mid = (l+r)/2;
	if(strncmp(s.c_str() + sa[mid],p.c_str(),m) > 0) r = mid;
	else l = mid+1;
    }
    if(strncmp(s.c_str() + sa[r],p.c_str(),m) != 0) r--;
    res.second = r;
    return res;
  }
  
  
  void printSuffixArray() {
    for(int i = 0; i < n; i++)
      cout << sa[i] << " " << (sa[i] < 10 ? " " : "") << lcp[i] << " " << s.substr(sa[i]) << endl;
  }
  
private:
  
  //Construct a Suffix Array for a string s (Based on the prefix doubling algorithm). Time complexity O(n*log^2(n))
  void prefixDoublingSorting() {
    vector<rank> ra_p(n);
    //Initiliaze ra with ascii values of chars in s
    for(int i = 0; i < n; i++)	ra[i] = s[i];
    for(int k = 1; k < n; k <<= 1) {
      for(int j = 0; j < n; j++) { 
	ra_p[j] = make_pair(ra[sa[j]],(sa[j] + k < n ? ra[sa[j] + k] : 0)); 
	sa_idx[sa[j]] = j;
      }
      //If we want to construct Suffix-Array in O(n*log(n)) we have to replace this naive sorting
      //stradegy with Counting-Sort
      sort(sa.begin(),sa.end(),[&](const int i, const int j) {
	return (ra_p[sa_idx[i]] < ra_p[sa_idx[j]]) || (ra_p[sa_idx[i]] == ra_p[sa_idx[j]] && sa_idx[i] < sa_idx[j]);
      });
      //Re-rank after sorting
      temp_ra[sa[0]] = 0; int r = 0;
      for(int j = 1; j < n; j++)
	temp_ra[sa[j]] = (ra[sa[j]] == ra[sa[j-1]] && ra[sa[j] + (sa[j] + k < n ? k : 0)] == ra[sa[j-1] + (sa[j-1] + k < n ? k : 0)]) ?
			 r : ++r;
      for(int j = 0; j < n; j++) ra[j] = temp_ra[j];
      if(ra[sa[n-1]] == n-1) break;
    }
  }
  
  //Construct a Suffix Array for a string s (Based on the induced sorting algorithm).
  //Normally Induced Sorting has a running time of O(n), but in this variant the S* suffixes
  //are sorted with a naiv variant (Time complexity O(|S*|^2*log(|S*|)))
  //Therefore the running time depends on the amount of S* suffixes in the text.
  vector<int> inducedSorting(string& T) {
    //Use -1 as symbol for an empty entry
    int n = T.size();
    vector<int> sa(n,-1);
    int type[n]; memset(type,-1,sizeof(type));
    vector<int> s_star, s_star_length;
    vector<int> s_length(300,0), l_length(300,0), s_pos(300,0), l_pos(300,0);
    
    //Determine all L (type = 0) and S (type = 1) suffixes and precalculate datastructure for bucket borders
    type[n-1] = 1;
    for(int i = n-2; i >= 0; i--) {
      if(T[i] > T[i+1]) { type[i] = 0; l_length[T[i]]++; }
      else if(T[i] < T[i+1]) { type[i] = 1; s_length[T[i]]++; }
      else { type[i] = type[i+1]; if(type[i]) s_length[T[i]]++; else l_length[T[i]]++; }
    }    
    //Determine all S* suffixes
    int last_s_star = -1;
    for(int i = 1; i < n; i++) {
      if(i > 0 && type[i-1] == 0 && type[i] == 1) { 
	if(last_s_star != -1) { s_star.push_back(last_s_star); s_star_length.push_back(i-last_s_star+1); }
	last_s_star = i;
      }
    }
    s_star.push_back(n-1); s_star_length.push_back(1);
    
    //Determine bucket borders for L and S suffixes
    int pos = 1;
    for(char a = 'A'; a <= 'z'; a++) {
      l_pos[a] = pos; pos += l_length[a] + s_length[a];
      s_pos[a] = pos-1;
    }
    
    //Sort S* suffixes (naive variant)
    /*vector<T> star;
    for(int i = 0; i < s_star.size(); i++) {
      T sub_star;
      for(int j = s_star[i]; j < s_star[i] + s_star_length[i]; j++)
	sub_star.push_back(T[i]);
      star.push_back(sub_star);
    }
    Trie trie(star);
    vector<int> supersigns = trie.getSortedRanks();
    bool is_unique = true; map<int,int> sign_count;
    for(int i = 0; i < supersigns.size(); i++) {
      sign_count[supersigns[i]]++;
      if(sign_count[supersigns[i]] > 1) is_unique = false;
    }
    if(!is_unique) {
      vector<int> super_sa = inducedSorting<vector<int>>(supersigns);
      vector<int> temp_s_star(s_star.size());
      for(int i = 0; i < s_star.size(); i++)
	temp_s_star[i] = s_star[super_sa[i]];
      swap(s_star,temp_s_star);
    }
    else {
      vector<int> temp_s_star(s_star.size());
      for(int i = 0; i < s_star.size(); i++)
	temp_s_star[supersigns[i]] = s_star[i];
      swap(s_star,temp_s_star);
    }*/
     sort(s_star.begin(),s_star.end(),
	 [&](const int i1, const int i2) { return s.substr(i1,n-i1).compare(s.substr(i2,n-i2)) < 0; });
    
    //Insert S* suffixes into SA-Array
    vector<int> temp_pos(300,0);
    for(int i = s_star.size()-1; i >= 0; i--) {
      sa[s_pos[T[s_star[i]]]-temp_pos[T[s_star[i]]]++] = s_star[i];
    }
    
    //Induce from left to right and insert all L suffixes
    for(int i = 0; i < n; i++) {
      if(sa[i] > 0 && type[sa[i]-1] == 0)
	sa[l_pos[T[sa[i]-1]]++] = sa[i]-1;
    }
    //Induce from right to left and insert all S suffixes
    for(int i = n-1; i >= 0; i--) {
      if(sa[i] > 0 && type[sa[i]-1] == 1)
	sa[s_pos[T[sa[i]-1]]--] = sa[i]-1;
    }
    return sa;
  }
  
  //Computes the Longest Common Prefix of all suffixes in s. Time Complexity O(n)
  void computeLCP() {
      int i, L; 
      phi[sa[0]] = -1;
      for(int i = 1; i < n; i++)
	phi[sa[i]] = sa[i-1];
      for(i = L = 0; i < n; i++) {
	if(phi[i] == -1) { plcp[i] = 0; continue; }
	//L is incremented by a maximum amount of n times => Time Complexity O(n)
	while(s[i + L] == s[phi[i] + L]) L++;
	plcp[i] = L;
	L = max(L-1,0);
      }
      for(int i = 0; i < n; i++)
	lcp[i] = plcp[sa[i]];
  }
  
  int n;
  string s;
  vector<int> sa;
  int ra[MAXN], temp_ra[MAXN], sa_idx[MAXN], phi[MAXN], lcp[MAXN], plcp[MAXN];
};

int main() {
  string s; cin >> s;
  SuffixArray sa(s);
  sa.printSuffixArray();
  
  /*vector<string> pattern { "GA", "TAG", "A", "C", "D" };
  for(int i = 0; i < pattern.size(); i++) {
    string p = pattern[i];
    ii res = sa.findPattern(p);
    cout << "Pattern \"" << p << "\" appears " << (res.first != -1 ? (res.second-res.first+1) : 0) << " times in string \"" << s<< "\"" << endl;
  }*/
  
  return 0;
}