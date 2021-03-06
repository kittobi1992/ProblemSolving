#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;

ll n, r, p;
vector<ll> dp;

ll calc(int n) {
	if(dp[n] != LLONG_MAX)
		return dp[n];

	for(int k = 1; k < n; k++) {
		dp[n] = min(dp[n],k*p + calc(ceil(((double)n)/(k+1))) + r);
	}

	return dp[n];

}

int main() {

	cin >> n >> r >> p;
	dp.assign(n+1,LLONG_MAX);
	dp[0] = 0;
	dp[1] = 0;

	cout << calc(n) << endl;

	return 0;
}
