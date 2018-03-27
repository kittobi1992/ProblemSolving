#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
  
    ll n, c; cin >> n >> c;
    vector<ll> t(n,0);
    for(int i = 0; i < n; ++i) cin >> t[i];
    
    int cnt = 1;
    for(int i = 1; i < n; ++i) {
        cnt++;
        if(t[i]-t[i-1] > c) cnt = 1;
    }
    
    cout << cnt << endl;
    
	return 0;
}
