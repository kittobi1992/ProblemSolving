#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef pair<int,int> ii;

class SuffixArray {

public:
  #define MAXN 100010
  typedef pair<int,int> rank;
  
  SuffixArray(string& s) : n(s.size()+1), s(s), sa(s.size()+1) {
    s.push_back('$');
    memset(ra,0,sizeof(ra)); memset(temp_ra,0,sizeof(temp_ra)); memset(sa_idx,0,sizeof(sa_idx));
    memset(phi,0,sizeof(phi)); memset(lcp,0,sizeof(lcp)); memset(plcp,0,sizeof(plcp));
    for(int i = 0; i < sa.size(); i++)	{ sa[i] = i; sa_idx[i] = i; }
    constructSA();
    computeLCP();
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
      cout << sa[i] << " " << s.substr(sa[i]) << endl;
  }
  
private:
  
  //Construct a Suffix Array for a string s (Based on Ranking-Pairs). Time complexity O(n*log^2(n))
  void constructSA() {
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
  
  //Computes the Longest Common Prefix of all suffixes in s. Time Complexity O(n)
  void computeLCP() {
      int i, L; 
      phi[sa[0]] = -1;
      for(int i = 1; i < n; i++)
	phi[sa[i]] = sa[i-1];
      for(i = L = 0; i < n; i++) {
	if(phi[i] == -1) { plcp[i] = 0; continue; }
	//L is incremented by a maximum amount of n times => Time Complexity O(n)
	while(T[i + L] == T[phi[i] + L]) L++;
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
  string s = "GATAGACA";
  SuffixArray sa(s);
  sa.printSuffixArray();
  
  vector<string> pattern { "GA", "TAG", "A", "C", "D" };
  for(int i = 0; i < pattern.size(); i++) {
    string p = pattern[i];
    ii res = sa.findPattern(p);
    cout << "Pattern \"" << p << "\" appears " << (res.first != -1 ? (res.second-res.first+1) : 0) << " times in string \"" << s<< "\"" << endl;
  }
  
  return 0;
}