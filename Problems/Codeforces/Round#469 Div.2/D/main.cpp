#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

int main() {

	ll n, q; cin >> n >> q;

	for(int i = 0; i < q; ++i) {
		ll x; cin >> x;
		if(x % 2 == 0) {
			while( x % 2 != 1) {
				ll m = (2*n - x)/2;
				x += m--;
			}
		}
		cout << (x + 1) / 2 << endl;
	}

	return 0;
}
