#include <bits/stdc++.h>

using namespace std;

int N, K;

int q( int m )
{
  double x = 100.0 * ( static_cast<double>(m) / static_cast<double>(N) ) + 0.5;
  return floor(x);
}

int find_min_idx( vector<int>& a )
{
  int min_val = numeric_limits<int>::max();
  int min_idx = -1;
  for ( int i = 0; i < a.size(); ++i )
  {
    if( min_val > a[i] )
    {
      min_val = a[i];
      min_idx = i;
    }
  }
  return min_idx;
}

int main() {
  
  cin >> N >> K;
  vector<int> a(N);
  for ( int i = 0; i < N; ++i )
    cin >> a[i];

  int k = min(N,K);
  vector<int> t(k,0);
  vector<int> idx(k,0);
  for ( int i = 0; i < k; ++i ) {
    t[i] = a[i];
    idx[i] = i;
  }
  
  int n = k;
  int m = 0;
  int running_tasks = k;
  vector<bool> vis(N);
  int interesting_solutions = 0;
  while( true )
  {
    vector<int> finished_tasks;
    int progress = q(m);
    for ( int i = 0; i < k; ++i )
    {
      t[i]--;
      if ( t[i] == 0 )
        finished_tasks.push_back(i);
      int test_progress = a[idx[i]] - t[i];
      if ( progress == test_progress && !vis[idx[i]] )
      {
        vis[idx[i]] = true;
        interesting_solutions++;
      }
    }

    for ( int i : finished_tasks )
    {
      m++;
      if ( n < N )
      {
        t[i] = a[n];
        idx[i] = n++;
      } else {
        t[i] = numeric_limits<int>::max();
        running_tasks--;
      }
    }

    if ( running_tasks == 0 )
      break;

  }

  cout << interesting_solutions << endl;

  return 0;
}
