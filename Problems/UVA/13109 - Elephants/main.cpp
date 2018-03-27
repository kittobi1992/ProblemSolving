#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
  
  int test; cin >> test;
  while(test--) {
    ll m, w; cin >> m >> w;
    vector<ll> a(m); 
    for(int i = 0; i < m; ++i) cin >> a[i];
    sort(a.begin(),a.end());
    int res = 0, i = 0; ll sum = 0;
    while(i < a.size() && sum <= w) {
      res++; sum += a[i++];
    }
    cout << ((sum > w) ? (res-1) : res) << endl;
  }
  
  return 0;
}
