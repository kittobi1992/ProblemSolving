#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

#define MAX 900

typedef long long ll;

vector<vector<ll>> dp(MAX+1,vector<ll>(MAX,0));
vector<ll> res(MAX+1,0);


int main() {
	dp[1][1] = 1;
	for(int i = 2; i <= MAX; i++) {
		for(int j = 1; j <= i; j++) {
			dp[i][j] = dp[i-1][j-1] + dp[i-1][j]*j;
		}
	}

	for(int i = 1; i <= MAX; i++) {
		for(int j = 1; j <= i; j++)
			res[i] += dp[i][j];
	}

	ll n;
	while(cin >> n) {
		if(n == 0)
			break;

		cout << n << ", "<< res[n] << endl;

	}
	

	return 0;
}
