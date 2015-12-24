#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;
typedef pair<int,ll> il;
typedef vector<vector<il>> graph;
typedef vector<int> vi;

#define INVALID -1

int n;
vector<ll> sp;

class LCA {

public:
  LCA(graph& g) : g(g) {
    N = g.size(); MAX_LOG = max((int)ceil(log2(N)),1);
    h.assign(N,0); parent.assign(N,vector<int>(MAX_LOG,-1));
    buildLCA(0);
  }
  
  int lca(int u, int v) {
    if(h[v] < h[u])
      swap(u,v);
    for(int i = MAX_LOG-1; i >= 0; i--)
      if(parent[v][i]+1 && h[parent[v][i]] >= h[u])
	v = parent[v][i];
    if(v == u)
      return v;
    for(int i = MAX_LOG-1; i >= 0; i--) {
      if(parent[v][i] - parent[u][i]) {
	v = parent[v][i]; u = parent[u][i];
      }
    }
    return parent[v][0];
  }
  
private:
  void buildLCA(int v, int p = -1) {
    parent[v][0] = p;
    if(p + 1)
      h[v] = h[p] + 1;
    for(int i = 1; i < MAX_LOG; i++)
      if(parent[v][i-1] + 1)
	parent[v][i] = parent[parent[v][i-1]][i-1];
    for(il node : g[v]) {
      int u = node.first;
      if(p - u)
	buildLCA(u,v);
    }
  }
  
  graph g;
  int N, MAX_LOG;
  vector<int> h;
  vector<vector<int>> parent;
};


void dfs(int cur_node, int parent, ll distance, graph& g) {
	sp[cur_node] = distance;
	for (int i = 0; i < g[cur_node].size(); i++) {
		int u = g[cur_node][i].first;
		ll c = g[cur_node][i].second;
		if(u - parent) {
			dfs(u, cur_node, distance + c, g);
		}
	}
}

int main() {

	while(cin >> n) {
		if(n == 0)
			break;

		graph g(n,vector<il>()); 
		sp.assign(n,0);
		for(int i = 1; i < n; i++) {
			ll a, l;
			cin >> a >> l;
			g[i].push_back(make_pair(a,l));
			g[a].push_back(make_pair(i,l));
		}		

		
		LCA l(g);
		dfs(0,-1,0,g);
	
		int q;
		cin >> q;
		for(int i = 0; i < q; i++) {
			int s,t;
			cin >> s >> t;
			int a = l.lca(s,t);
			cout << (sp[s] + sp[t] - 2*sp[a]) << (i != q-1 ? " " : "\n");
		}

	}
	
	return 0;
}
