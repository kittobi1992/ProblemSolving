#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;

#define PRIME 1000000007

ll p = PRIME;

ll x, y, d;
void extendedEuclid(ll a, ll b) {
	if (!b) {
		x = 1; y = 0; d = a;
		return;
	}
	extendedEuclid (b, a % b);
	ll x1 = y; ll y1 = x - (a / b) * y;
	x = x1; y = y1;
}

ll multInv(ll n) { 
	p = PRIME;
	extendedEuclid (n, p);
	x += ((x / PRIME) + 1) * PRIME;
	return x % PRIME;
}

ll fak(ll n) {
	if(n == 0 || n == 1)
		return 1;
	ll fak_n = 1;
	for(ll i = 1; i <= n; i++) {
		fak_n = (fak_n * i) % PRIME;
	}
	return fak_n;
}

ll binomial(vector<ll> k) {
	ll n = 0;
	for(int i = 0; i < k.size(); i++) {
		n += k[i];
	}
	ll d = (fak(k[k.size()-1]) * fak(n - k[k.size()-1])) % PRIME;
	ll fak_n = fak(n);
	ll mul_inv_d = multInv(d);
	return (fak_n * mul_inv_d) % PRIME;
}

int main() {
	
	int n;
	cin >> n;
	vector<ll> k(n);
	for(int i = 0; i < n; i++) {
		cin >> k[i];
	}

	vector<ll> dp(n,0);
	ll result = 1;
	for(int i = 1; i < n; i++) {
		vector<ll> ks(i+1,0);
		for(int j = 0; j < i; j++)
			ks[j] = k[j];
		ks[i] = k[i]-1;
		result =  (result * binomial(ks)) % PRIME;
	}

	cout << result << endl;



}
