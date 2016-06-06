#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
  
  ll n, k, h; cin >> n >> h >> k;
  vector<ll> a(n);
  for(int i = 0; i < n; ++i) cin >> a[i];
  a.push_back(h);
  
  ll res = 0;
  ll cur_h = 0;
  for(int i = 0; i < n+1; ++i) {
    ll space = h-cur_h;
    if(space >= a[i]) {
      cur_h += a[i];
      continue;
    }
    else {
      ll t = (max(static_cast<ll>(0),a[i]-space))/k;
      if((max(static_cast<ll>(0),a[i]-space)) % k > 0)
	t++;
      cur_h = max(static_cast<ll>(0),cur_h-t*k)+a[i]; res += t;
    }
  }
  
  cout << res << endl;
  
  return 0;
}
 