#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> graph;

//Lowest Common Ancestor implementation with O(n*log(n)) preproccesing
//and O(log(n)) query time
//Idea: For every node store all 2^i ancestors of this node
class LCA1 {
public:
  LCA1(graph& g) : g(g) {
    N = g.size(); MAX_LOG = max((int)ceil(log2(N)),1);
    h.assign(N,0); parent.assign(N,vector<int>(MAX_LOG,-1));
    buildLCA(0);
  }
  
  //LCA-Query with O(log(n)) time complexity
  int lca(int u, int v) {
    //Forall v \in V: h[v] denotes the depth of
    //that node measured from the root
    if(h[v] < h[u])
      swap(u,v);
    //Search ancestor a of v, such that h[a] == h[u]
    for(int i = MAX_LOG-1; i >= 0; i--)
      if(parent[v][i]+1 && h[parent[v][i]] >= h[u])
	v = parent[v][i];
    if(v == u)
      return v;
    for(int i = MAX_LOG-1; i >= 0; i--) {
      //Invariant: h[u] == h[v]
      //Search ancestor of u and v such that parent[v][i] == parent[u][i]
      if(parent[v][i] - parent[u][i]) {
	v = parent[v][i]; u = parent[u][i];
      }
    }
    return parent[v][0];
  }
  
private:
  //Build datastructure to calculate LCA in O(log(n)) (Simple dfs)
  //v = current visited tree node, p = parent of v
  //Time complexity: O(n*log(n))
  void buildLCA(int v, int p = -1) {
    //2^0th = 1th ancestor of v is p
    parent[v][0] = p;
    if(p + 1)
      h[v] = h[p] + 1;
    for(int i = 1; i < MAX_LOG; i++)
      //Calculates the 2^ith ancestor of v
      if(parent[v][i-1] + 1)
	parent[v][i] = parent[parent[v][i-1]][i-1];
    //Execute DFS on all childs of v
    for(int u : g[v]) 
      if(p - u)
	buildLCA(u,v);
  }
  
  graph g;
  int N, MAX_LOG;
  vector<int> h;
  vector<vector<int>> parent;
};

int main() {

	int n,q; cin >> n >> q;
	graph g(n);
	for(int i = 0; i < n-1; i++) {
	  int u,v;  cin >> u >> v;
	  g[u].push_back(v);
	  g[v].push_back(u);
	}
	
	LCA1 l(g);
	for(int i = 0; i < q; i++) {
	  int u,v; cin >> u >> v;
	  cout << "LCA of " << u << " and " << v << " is " << l.lca(u,v) << endl;
	}
	
  
	return 0;
}
