#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef pair<int,int> ii;

class SuffixArray {

public:
  #define MAXN 5050
  typedef pair<int,int> rank;
  
  SuffixArray(string& s) : n(s.size()+1), s(s), sa(s.size()+1) {
    this->s = s + "$";
    memset(ra,0,sizeof(ra)); memset(temp_ra,0,sizeof(temp_ra)); memset(sa_idx,0,sizeof(sa_idx));
    memset(phi,0,sizeof(phi)); memset(lcp,0,sizeof(lcp)); memset(plcp,0,sizeof(plcp));
    for(int i = 0; i < sa.size(); i++)	{ sa[i] = i; sa_idx[i] = i; }
    inducedSorting();
    //constructSA();
    computeLCP();
  }
  
  ii findPattern(string& p) {
    int m = p.size();
    int l = 0, r = n-1;
    while(l < r) {
	int mid = (l+r)/2;
	if(strncmp(s.c_str() + sa[mid],p.c_str(),m) >= 0) r = mid;
	else l = mid+1;
    }
    if(strncmp(s.c_str() + sa[l],p.c_str(),m) != 0) return ii(-1,-1);
    ii res; res.first = l;
    l = 0; r = n-1;
    while(l < r) {
	int mid = (l+r)/2;
	if(strncmp(s.c_str() + sa[mid],p.c_str(),m) > 0) r = mid;
	else l = mid+1;
    }
    if(strncmp(s.c_str() + sa[r],p.c_str(),m) != 0) r--;
    res.second = r;
    return res;
  }
  
  int longestRepeatedSubstring() {
    int max_rs = 0;
    for(int i = 0; i < n; i++)
      max_rs = max(lcp[i],max_rs);
    return max_rs;
  }
  
  void printSuffixArray() {
    for(int i = 0; i < n; i++)
      cout << sa[i] << " " << (sa[i] < 10 ? " " : "") << s.substr(sa[i]) << endl;
  }
  
private:
  
  void inducedSorting() {
    //Use -1 as symbol for an empty entry
    for(int i = 0; i < n; i++) sa[i] = -1;
    int type[n]; memset(type,-1,sizeof(type));
    vector<int> s_star;
    vector<int> s_length(300,0), l_length(300,0), s_pos(300,0), l_pos(300,0);
    
    //Determine all L (type = 0) and S (type = 1) suffixes and precalculate datastructure for bucket borders
    type[n-1] = 1;
    for(int i = n-2; i >= 0; i--) {
      if(s[i] > s[i+1]) { type[i] = 0; l_length[s[i]]++; }
      else if(s[i] < s[i+1]) { type[i] = 1; s_length[s[i]]++; }
      else { type[i] = type[i+1]; if(type[i]) s_length[s[i]]++; else l_length[s[i]]++; }
    }    
    //Determine all S* suffixes
    for(int i = 1; i < n; i++) {
      if(i > 0 && type[i-1] == 0 && type[i] == 1) { s_star.push_back(i);}
    }
    
    //Determine bucket borders for L and S suffixes
    int pos = 1;
    for(char a = 'a'; a <= 'z'; a++) {
      l_pos[a] = pos; pos += l_length[a] + s_length[a];
      s_pos[a] = pos-1;
    }
    
    //Sort S* suffixes (naive variant)
    sort(s_star.begin(),s_star.end(),
	 [&](const int i1, const int i2) { return s.substr(i1,n-i1).compare(s.substr(i2,n-i2)) < 0; });
    
    //Insert S* suffixes into SA-Array
    vector<int> temp_pos(300,0);
    for(int i = s_star.size()-1; i >= 0; i--) {
      sa[s_pos[s[s_star[i]]]-temp_pos[s[s_star[i]]]++] = s_star[i];
    }
    
    //Induce from left to right and insert all L suffixes
    for(int i = 0; i < n; i++) {
      if(sa[i] > 0 && type[sa[i]-1] == 0)
	sa[l_pos[s[sa[i]-1]]++] = sa[i]-1;
    }
    //Induce from right to left and insert all S suffixes
    for(int i = n-1; i >= 0; i--) {
      if(sa[i] > 0 && type[sa[i]-1] == 1)
	sa[s_pos[s[sa[i]-1]]--] = sa[i]-1;
    }
  }
  
  void constructSA() {
    vector<rank> ra_p(n);
    for(int i = 0; i < n; i++)	ra[i] = s[i];
    for(int k = 1; k < n; k <<= 1) {
      for(int j = 0; j < n; j++) { 
	ra_p[j] = make_pair(ra[sa[j]],(sa[j] + k < n ? ra[sa[j] + k] : 0)); 
	sa_idx[sa[j]] = j;
      }
      sort(sa.begin(),sa.end(),[&](const int i, const int j) {
	return (ra_p[sa_idx[i]] < ra_p[sa_idx[j]]) || (ra_p[sa_idx[i]] == ra_p[sa_idx[j]] && sa_idx[i] < sa_idx[j]);
      });
      temp_ra[sa[0]] = 0; int r = 0;
      for(int j = 1; j < n; j++)
	temp_ra[sa[j]] = (ra[sa[j]] == ra[sa[j-1]] && ra[sa[j] + (sa[j] + k < n ? k : 0)] == ra[sa[j-1] + (sa[j-1] + k < n ? k : 0)]) ?
			 r : ++r;
      for(int j = 0; j < n; j++) ra[j] = temp_ra[j];
      if(ra[sa[n-1]] == n-1) break;
    }
  }
  
  void computeLCP() {
      int i, L; 
      phi[sa[0]] = -1;
      for(int i = 1; i < n; i++)
	phi[sa[i]] = sa[i-1];
      for(i = L = 0; i < n; i++) {
	if(phi[i] == -1) { plcp[i] = 0; continue; }
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
  int test; cin >> test;
  while(test--) {
    string s; cin >> s;
    int n = s.size();
    SuffixArray sa(s);
    //sa.printSuffixArray();
    cout << sa.longestRepeatedSubstring() << endl;
  }
  
  
  
  return 0;
}