#include <bits/stdc++.h>

using namespace std;

using graph = vector<vector<int>>;
using nd = pair<int,int>;

int smallest_circle, n, m;
graph g;
vector<int> depth;
vector<int> parent;


void bfs(int s) {
	depth.assign(n,INT_MAX);
	queue<int> q; q.push(s);  parent[s] = -1; depth[s] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int i = 0; i < g[u].size(); ++i) {
			int v = g[u][i];
			if(v != parent[u]) {
				if(depth[v] == INT_MAX) {
					parent[v] = u;
					depth[v] = depth[u]+1;
					q.push(v);
				}
				else {	
					int cycle_length = depth[v] + depth[u] + 1;
					smallest_circle = min(smallest_circle,cycle_length);
					if(smallest_circle == 3) return;
				}
			}
		}
	}
}



int main() {
  
	int test; cin >> test;
	int t = 1;
	while(test--) {
		cin >> n >> m;
		smallest_circle = INT_MAX;
		g.assign(n,vector<int>());
		for(int i = 0; i < m; ++i) {
			int u, v; cin >> u >> v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		
		parent.assign(n,-1);
		for(int i = 0; i < n && smallest_circle != 3; ++i) {
			bfs(i);
		}
		
		cout << "Case " << t++ << ": ";
		if(smallest_circle == INT_MAX) cout << "impossible" << endl;
		else cout << smallest_circle << endl;
	}
	
 	return 0;
}
