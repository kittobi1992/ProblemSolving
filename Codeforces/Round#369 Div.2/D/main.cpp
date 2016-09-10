#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MOD 1000000007
#define N 200002

ll p[N];
vector<int> g;
vector<ll> num, com;
vector<bool> vis;

void precalc() {
	p[0] = 1;
	for(int i = 1; i < N; ++i) p[i] = p[i-1]*2 % MOD;	
}

pair<ll,ll> dfs(int u, ll i, ll c) {
	int v = g[u];
	num[u] = i; com[u] = c; vis[u] = true;
	if(!vis[v]) return dfs(v,i+1,c);
	else {
		int cycle_length = num[u]-num[v]+1;
		if(com[u] == com[v]) return make_pair(i+1-cycle_length,cycle_length);
		else return make_pair(i+1,0);
	}
}

int main() {
	precalc();
	
	int n; cin >> n;
	g.assign(n,0); com.assign(n,0); num.assign(n,0); vis.assign(n,0);
	for(int i = 0; i < n; ++i) { cin >> g[i]; g[i]--;}
	
	ll c = 0;
	ll res = 1;
	for(int i = 0; i < n; ++i) {
		if(!vis[i])	{
			pair<ll,ll> d = dfs(i,0,c);
			//cout << d.first << " " << d.second << endl;
			res = (res * (p[d.first]*(p[d.second]-((d.second > 0) ? 2 : 0)) % MOD)) % MOD;
		}
		c++;
	}
	
	cout << res << endl;
	
  return 0;
}
