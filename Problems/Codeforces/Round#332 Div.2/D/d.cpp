#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> sq;

ll p(ll n) {
	return (n*(n-1))/2;
}

ll q(ll n) {
	return ((n-1)*n*(2*n-1))/6;
}

ll squares(ll n, ll m) {
	return m*(n*n - p(n)) + q(n) - n*p(n);
}

ll solve(ll x, ll n) {
	ll m = ((ll) (((double) (x-q(n)+n*p(n)))/((double) (n*n-p(n)))));
	if(squares(n,m) == x)
		return m;
	else
		return -1;
}



ll squareCheck(ll n, ll m) {
	ll sum = 0;
	for(ll i = 1; i <= n; i++) {
		sum += (n-(i-1))*(m-(i-1));
	}
	return sum;
}

int main() {

	ll x; cin >> x;
	ll it = 2*ceil(pow((double) x, 1.0/3.0));
	vector<sq> sol;
	for(ll n = 1; n <= it; n++) {
		ll m = solve(x,n);
		if(m != -1 && n > m)
			break;
		if(m != -1)
			sol.push_back(make_pair(n,m));
	}

	int n = sol.size();


	if(n > 1)
		if(sol[n-1].first == sol[n-2].second && sol[n-1].second == sol[n-2].first) {
			sol.pop_back(); n--;
		}

	if(sol[n-1].first == sol[n-1].second)
		cout << (2*n-1) << endl;
	else
		cout << 2*n << endl;


	for(ll i = 0; i < n; i++)
		cout << sol[i].first << " " << sol[i].second << endl;

	for(ll i = n-1; i >= 0; i--) {
		if(sol[i].first == sol[i].second)
			continue;
		cout << sol[i].second << " " << sol[i].first << endl;
	}

	return 0;

}
