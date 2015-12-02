#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef pair<int,int> ii;

class SuffixArray {

public:
  #define MAXN 5050
  typedef pair<int,int> rank;
  
  SuffixArray(string& s) : n(s.size()+1), s(s), sa(s.size()+1) {
    s.push_back('$');
    memset(ra,0,sizeof(ra)); memset(temp_ra,0,sizeof(temp_ra)); memset(sa_idx,0,sizeof(sa_idx));
    memset(phi,0,sizeof(phi)); memset(lcp,0,sizeof(lcp)); memset(plcp,0,sizeof(plcp));
    for(int i = 0; i < sa.size(); i++)	{ sa[i] = i; sa_idx[i] = i; }
    constructSA();
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
      cout << sa[i] << " " << s.substr(sa[i]) << endl;
  }
  
private:
  
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
    
    computeLCP();
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
    cout << sa.longestRepeatedSubstring() << endl;
  }
  
  
  
  return 0;
}