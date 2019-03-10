#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ii;

int N, a, b;
string s;

class SuffixArray {

public:
  #define MAXN 100010
  typedef pair<int,int> rank;
  
  SuffixArray(string& s) : n(s.size()+1), s(s), sa(s.size()+1) {
    this->s = s + '$';
    memset(ra,0,sizeof(ra)); memset(temp_ra,0,sizeof(temp_ra)); memset(sa_idx,0,sizeof(sa_idx));
    for(int i = 0; i < sa.size(); i++)	{ sa[i] = i; sa_idx[i] = i; }
    prefixDoublingSorting();
  }
  
  int operator[](const int i) {
    return sa[i];
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
      cout << sa[i] << " " << (sa[i] < 10 ? " " : "") << " " << s.substr(sa[i]) << endl;
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
  
  int n;
  string s;
  vector<int> sa;
  int ra[MAXN], temp_ra[MAXN], sa_idx[MAXN];
};

int main() {
  
  cin >> N >> a >> b >> s;

  SuffixArray sa(s);
  // sa.printSuffixArray();

  vector<int> max_sub(N, 0);

  for ( size_t i = 1; i < N; ++i )
  {
    int l = 0;
    int r = N - i;

    while( r - l > 0 )
    {
      int m = ( r + l + 1 ) / 2;
      std::string pattern = s.substr( i, m );
      ii sa_range = sa.findPattern( pattern ); 

      bool occurs_before = false;
      for ( int j = sa_range.second; j >= sa_range.first; --j )
      {
        if ( sa[ j ] + m <= i )
        {
          occurs_before = true;
          break;
        }
      }

      if ( occurs_before )
        l = m;
      else
        r = m - 1;
    }

    max_sub[i] = l;
  }

  vector<int> cost(N + 1, std::numeric_limits<int>::max());
  cost[N] = 0;
  for ( int i = N - 1; i >= 0; --i )
  {
    if ( max_sub[ i ] == 0 ) {
      cost[ i ] = cost[ i + 1 ] + a;
    } else
    {
      for ( int j = 1; j <= max_sub[ i ]; ++j )
      {
        cost[ i ] = std::min( cost[ i ], cost[ i + j ] + std::min( j * a, b ) );
      }
    }
    
  }

  cout << cost[0] << endl;
  
  return 0;
}
