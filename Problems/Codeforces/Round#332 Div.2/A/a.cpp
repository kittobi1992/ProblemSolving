#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;

int main() {
	
	ll d1, d2, d3; cin >> d1 >> d2 >> d3;

	ll v1 = d1 + d2 + d3;
	ll v2 = 2*d1 + 2*d2;
	ll v3 = 2*d2 + 2*d3;
	ll v4 = 2*d1 + 2*d3;

	cout << min(v1,min(v2,min(v3,v4))) << endl;

	return 0;
}
