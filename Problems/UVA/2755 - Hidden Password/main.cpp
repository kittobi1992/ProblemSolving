#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ii;
#define MAXN 200010
int sa[MAXN], ra[MAXN], temp_ra[MAXN], sa_idx[MAXN];
ii ra_p[MAXN];

class SuffixArray {

public:
  
  SuffixArray(string& s) : n(s.size()+1), s(s) {
    this->s = s + '$';
    for(int i = 0; i < n; i++)	{ sa[i] = i; sa_idx[i] = i; }
    prefixDoublingSorting();
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
  
  int size() {
    return n;
  }
  
  int operator[](const int i) {
    return sa[i];
  }

  void printSuffixArray() {
    for(int i = 0; i < n; i++)
      cout << sa[i] << " " << (sa[i] < 10 ? " " : "")  << s.substr(sa[i]) << endl;
  }
  
private:
  
  //Construct a Suffix Array for a string s (Based on the prefix doubling algorithm). Time complexity O(n*log^2(n))
  void prefixDoublingSorting() {
    //Initiliaze ra with ascii values of chars in s
    for(int i = 0; i < n; i++)	ra[i] = s[i];
    for(int k = 1; k < n; k <<= 1) {
      for(int j = 0; j < n; j++) { 
	ra_p[j] = make_pair(ra[sa[j]],(sa[j] + k < n ? ra[sa[j] + k] : 0)); 
	sa_idx[sa[j]] = j;
      }
      //If we want to construct Suffix-Array in O(n*log(n)) we have to replace this naive sorting
      //stradegy with Counting-Sort
      sort(sa,sa + n,[&](const int i, const int j) {
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
  
  
  int n;
  string s;
};

int main() {
  memset(sa,0,sizeof(sa)); memset(ra,0,sizeof(ra)); memset(temp_ra,0,sizeof(temp_ra)); memset(sa_idx,0,sizeof(sa_idx));
  memset(ra_p,0,sizeof(ra_p));
  
  int test; cin >> test;
  while(test--) {
    int n; string s; cin >> n >> s;
    string t = s + s;
    SuffixArray sa(t);
    int cur = -1;
    bool find = false;
    for(int i = 0; i < sa.size(); i++) {
      if(sa[i] < n) {
	cur = sa[i];
	break;
      }
    }
    string cur_pattern = t.substr(cur,n);
    ii ival = sa.findPattern(cur_pattern);
    for(int i = ival.first; i <= ival.second; i++)
      cur = min(cur,sa[i]);
    cout << cur << endl;
  }
  
  return 0;
}
