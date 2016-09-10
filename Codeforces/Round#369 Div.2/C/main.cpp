#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
  
	int n, m, k; cin >> n >> m >> k;
	vector<ll> f(n);
	for(int i = 0; i < n; ++i) { cin >> f[i]; }
	vector<vector<ll>> p(n, vector<ll>(m,0));
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) { cin >> p[i][j];	}
	}
	
	m++;
	
	vector<vector<vector<ll>>> dp(n+1,vector<vector<ll>>(m,vector<ll>(n+2,LLONG_MAX/4)));
	if(f[0] == 0) { for(int i = 1; i < m; ++i) dp[0][i][1] = p[0][i-1];}
	else dp[0][f[0]][1] = 0;
	
	for(int i = 1; i < n; ++i) {
		if(f[i] == 0) {
			for(int l = 1; l <= i+1; ++l) {
				for(int j = 1; j < m; ++j) {
					dp[i][j][l] = min(dp[i][j][l],dp[i-1][j][l] + p[i][j-1]);
					for(int u = 1; u < m; ++u) {
						if(j != u) dp[i][j][l] = min(dp[i][j][l],dp[i-1][u][l-1]+p[i][j-1]);
					}
				}
			}
		}
		else {
			for(int l = 1; l <= i+1; ++l) {
				dp[i][f[i]][l] = min(dp[i][f[i]][l],dp[i-1][f[i]][l]);
				for(int j = 1; j < m; ++j) {
					if(j != f[i]) dp[i][f[i]][l] = min(dp[i][f[i]][l],dp[i-1][j][l-1]);	
				}
			}
		}
	}
	
	ll res = LLONG_MAX/4;
	for(int i = 1; i < m; ++i) {
		res = min(res,dp[n-1][i][k]);	
	}
	
	if(res < LLONG_MAX/4)
		cout << res << endl;
	else 
		cout << "-1" << endl;
	
	
  return 0;
}
