#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;

#define MOD 1000000007

int main() {

	int n; cin >> n;
	ll res = 20;
	ll s = 7;
	for(int i = 2; i <= n; i++) {
		res = ((res*((ll)27)) % MOD + (s*20) % MOD) % MOD;
		s = (s*7) % MOD;
	}

	cout << res << endl;

}
