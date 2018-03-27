#include <bits/stdc++.h>

using namespace std;


using ll = long long;

ll trailing_zero(ll n) {
    ll t = 0;
    for(ll i = 1; pow(5,i) <= n; ++i) {
        t += n/pow(5,i);
    }
    return t;
}

int main() {
    ll cnt = 0;
    for(ll i = 0; i <= 125; ++i) {
        ll t = trailing_zero(i);
        //cout << i << "! has " << t << " trailing zeros" << endl;
        if(t % 2 == 0) cnt++;
        cout << "h("<< i << "!) = " << cnt << endl;
        
    }
    
    ll n;
    while(cin >> n) {
        if(n == -1) break;
        
        cout << n << "! has " << trailing_zero(n) << " trailing zeros" << endl;
        
    }
    
    return 0;
}
