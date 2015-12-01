#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;

int main() {

	int n; cin >> n;
	vector<ll> b(n,0);
	for(int i = 0; i < n; i++)
		cin >> b[i];

	ll c = 0;
	ll steps = 0;
	for(int i = 0; i < n; i++) {
		steps += abs(b[i]-c);
		c += (b[i]-c);
	}

	cout << steps << endl;

}
