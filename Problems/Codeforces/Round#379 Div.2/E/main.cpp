#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> graph;

graph g;
vector<int> col;

int max_dist = 0;
int max_v = 0;

void dfs(int parent, int u, int d) {
  if(g[u].size() == 1 && g[u][0] == parent) {
    if(d > max_dist) {
      max_dist = d;
      max_v = u;
    }
    return;
  }
  for(int v : g[u]) {
    if(v == parent) continue;
    int col1 = col[u]; int col2 = col[v];
    if(col1 != col2) dfs(u,v,d+1);
    else dfs(u,v,d);
  }
}

int main() {
  
  int N; cin >> N;
  col.resize(N);
  g.assign(N,vector<int>());
  for(int i = 0; i < N; ++i) cin >> col[i];
  for(int i = 0; i < N-1; ++i) {
    int u,v; cin >> u >> v;
    u--; v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  
  dfs(-1,0,0);
  dfs(-1,max_v,1);
  
  cout << max_dist/2 << endl;
    
	return 0;
}
