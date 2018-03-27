#include <bits/stdc++.h>

using namespace std;
class UnionFind {
public:
  vector<int> parent, size;

  UnionFind(int n) {
    parent.assign(n,0); size.assign(n,1);
    for(int i = 0; i < n; ++i)
      parent[i] = i;
  }
  
  int findSet(int n) { // Pfadkompression
	  if (parent[n] != n) parent[n] = findSet(parent[n]);
	  return parent[n];
  }

  void linkSets(int a, int b) { // Union by rank.
	  if (size[a] < size[b]) parent[a] = b;
	  else if (size[b] < size[a]) parent[b] = a;
	  else {
		  parent[a] = b;
		  size[b]++;
	  }
  }

  void unionSets(int a, int b) { // Diese Funktion aufrufen.
	  if (findSet(a) != findSet(b)) linkSets(findSet(a), findSet(b));
  }
};

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<int,ll> il;
typedef vector<pair<ll,ii>> graph;

//Takes a Graph g (EdgeList!!!) with N nodes and computes the MST and Cost of it. Time Complexity: O(M*log(M))
//Requires UnionFind-Datastructure!!!
pair<graph,ll> buildMST(int N, graph& g) {
  UnionFind uf(N);
  graph mst; ll mst_cost = 0; int M = g.size();
  sort(g.begin(),g.end());
  for(int i = 0; i < M; i++) {
    int u = g[i].second.first, v = g[i].second.second;
    if(uf.findSet(u) != uf.findSet(v)) {
      mst.push_back(g[i]); mst_cost += g[i].first;
      uf.unionSets(u,v);
    }
  }
  return make_pair(mst,mst_cost);
}

int main() {
  
	int test; cin >> test;
	int testcase = 1;
	while(test--) {
	  int n,m; cin >> n >> m;
	  graph g(m);
	  for(int i = 0; i < m; i++) {
	    int u,v; ll c; cin >> u >> v >> c;
	    g[i] = make_pair(c,make_pair(--u,--v));
	  }
	  
	  graph mst = buildMST(n,g).first;
	  vector<vector<il>> adj(n);
	  for(int i = 0; i < mst.size(); i++) {
	    int u = mst[i].second.first, v = mst[i].second.second;
	    ll c = mst[i].first;
	    adj[u].push_back(make_pair(v,c));
	    adj[v].push_back(make_pair(u,c));
	  }
	  
	  int q; cin >> q;
	  cout << "Case " << testcase << endl;
	  for(int i = 0; i < q; i++) {
	    int u,v; cin >> u >> v; --u; --v;
	    if(u == v) {
	      cout << "0" << endl; continue;
	    }
	    vector<il> parent(n,make_pair(-1,LLONG_MIN));
	    vector<bool> vis(n,false);
	    queue<int> bfs;
	    bfs.push(u); vis[u] = true;
	    while(!bfs.empty()) {
	      int node = bfs.front(); bfs.pop();
	      if(node == v)
		break;
	      for(int j = 0; j < adj[node].size(); j++) {
		int adj_node = adj[node][j].first;
		if(!vis[adj_node]) {
		  vis[adj_node] = true;
		  parent[adj_node] = make_pair(node,adj[node][j].second);
		  bfs.push(adj_node);
		}
	      }
	    }
	    il cur = parent[v];
	    ll max_day_trip = cur.second;
	    while(cur.first != u) {
	      cur = parent[cur.first];
	      max_day_trip = max(max_day_trip,cur.second);
	    }
	    
	    cout << max_day_trip << endl;
	  }
	  cout << endl;
	  
	  testcase++;
	  
	}
	
	return 0;
}
