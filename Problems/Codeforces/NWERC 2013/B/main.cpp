#include <bits/stdc++.h>

using namespace std;

using graph = vector<vector<int>>;
vector<int> s;
vector<bool> vis;
graph g;
int n, m;

int res = 0;

int clique_cost(vector<int>& c) {
	int sum = 0;
	for(int i = 0; i < c.size(); ++i) sum += s[c[i]];
	return sum;
}

bool is_clique(vector<int>& c) {
	int nc = c.size();
	for(int i = 0; i < nc; ++i) {
		int cnt = 0;
		for(int j = 0; j < g[c[i]].size(); ++j) {
			for(int k = 0; k < nc; ++k) if(g[c[i]][j] == c[k]) cnt++;
		}
		if(cnt != nc-1) return false;
	}
	return true;
}

void dfs(int u, vector<int>& c, int max_c) {
	if(c.size() == max_c) {
		if(is_clique(c)) res = max(res,clique_cost(c));	return;
	}
	
	for(int i = 0; i < g[u].size(); ++i) {
		int v = g[u][i];
		if(!vis[v]) {
			vis[v] = true; c.push_back(v);	
			dfs(v,c,max_c);
			vis[v] = false; c.pop_back();
		}
	}
	
}

void find_clique(int max_c) {
	vector<int> c;
	for(int i = 0; i < n; ++i) {
		vis[i] = true; c.push_back(i);	
		dfs(i,c,max_c);
		vis[i] = false; c.pop_back();
	}
}

int main() {
  
	while(cin >> n >> m) {
		res = 0;
		s.assign(n,0); vis.assign(n,false);
		for(int i = 0; i < n; ++i) cin >> s[i];
		g.assign(n,vector<int>());
		for(int i = 0; i < m; ++i) {
			int u, v; cin >> u >> v; u--; v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		
		find_clique(2);
		find_clique(3);
		find_clique(4);
		
		cout << res << endl;
	}
	
  	return 0;
}
