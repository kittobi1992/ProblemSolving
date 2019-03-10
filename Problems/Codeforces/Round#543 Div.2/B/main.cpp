#include <bits/stdc++.h>

using namespace std;

int main() {
  
    int N; cin >> N;
    vector<int> a(N);
    for ( int i = 0; i < N; ++i )
      cin >> a[i];
    sort( a.begin(), a.end() );

    unordered_map< int, int > cnt;
    for ( int i = 0; i < N; ++i )
    {
      for ( int j = i + 1; j < N; ++j )
      {
        cnt[a[i]+a[j]]++;
      }
    }

    int res = 0;
    for ( auto& i : cnt )
    {
      res = max(res, i.second);
    }
    cout << res << endl;

    return 0;
}
