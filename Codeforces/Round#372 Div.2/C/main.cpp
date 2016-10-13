#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


int main() {
  
    ll n; cin >> n;
    
    ll i = 2;
    for(ll k = 1; k <= n; ++k) {
        ll c = k;
        ll p = c*c*k + 2*c*c + c - i;
        cout << p << endl;
        i = c;
    }
    
	return 0;
}
