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

template<typename T>
using graph = vector<pair<T,ii>>;

int N;

//Takes a Graph g (EdgeList!!!) with N nodes and computes the MST and Cost of it. Time Complexity: O(M*log(M))
//Requires UnionFind-Datastructure!!!
template<typename T>
pair<graph<T>,T> buildMST(graph<T>& g) {
  UnionFind uf(N);
  graph<T> mst; T mst_cost = 0; int M = g.size();
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

template<typename T>
graph<T> readGraph(ifstream& fin) {
	int m; fin >> N >> m;
	graph<T> g(m,make_pair(static_cast<T>(0),make_pair(0,0)));
	for(int i = 0; i < m; ++i) { 
		fin >> g[i].second.first >> g[i].second.second >> g[i].first;
		g[i].second.first--; g[i].second.second--;
	}
	return g;
}


template<typename T>
void printMST(pair<graph<T>,T>& result) {
	graph<T> mst = result.first;	
	T mst_cost = result.second;
	cout << "Costs of the MST: " << mst_cost << endl;
	cout << "Edges of the MST: " << endl;
	for(int i = 0; i < mst.size(); ++i) cout << "("<< (mst[i].second.first+1) << "," << (mst[i].second.second+1) << "), Cost: " << mst[i].first << endl;
	cout << "--------------------" << endl;
}

int main() {
  
	ifstream fin1("1.in");
	graph<int> g1 = readGraph<int>(fin1);
	auto res1 = buildMST<int>(g1);
	printMST<int>(res1);
	
	ifstream fin2("2.in");
	graph<double> g2 = readGraph<double>(fin2);
	auto res2 = buildMST<double>(g2);
	printMST<double>(res2);
	
	ifstream fin3("3.in");
	graph<long long> g3 = readGraph<long long>(fin3);
	auto res3 = buildMST<long long>(g3);
	printMST<long long>(res3);
	
	
  return 0;
}
