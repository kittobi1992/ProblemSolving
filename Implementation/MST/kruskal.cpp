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

typedef pair<int,int> ii;
typedef vector<pair<int,ii>> graph;

//Takes a Graph g (EdgeList!!!) with N nodes and computes the MST and Cost of it. Time Complexity: O(M*log(M))
//Requires UnionFind-Datastructure!!!
pair<graph,int> buildMST(int N, graph& g) {
  UnionFind uf(N);
  graph mst; int mst_cost = 0; int M = g.size();
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
  
  return 0;
}
