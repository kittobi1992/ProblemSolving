#include <bits/stdc++.h>

using namespace std;

int N;

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
using edge_list = vector<pair<T,ii>>;

//Takes a Graph g (EdgeList!!!) with N nodes and computes the MST and Cost of it. Time Complexity: O(M*log(M))
//Requires UnionFind-Datastructure!!!
template<typename T>
pair<edge_list<T>,pair<T,ii>> buildMST(edge_list<T>& g) {
  UnionFind uf(N);
  pair<T,ii> removedEdge;
  edge_list<T> mst; T mst_cost = 0; int M = g.size();
  sort(g.begin(),g.end());
  for(int i = 0; i < M; i++) {
    int u = g[i].second.first, v = g[i].second.second;
    if(uf.findSet(u) != uf.findSet(v)) {
      mst.push_back(g[i]); mst_cost += g[i].first;
      uf.unionSets(u,v);
    }
    else {
        removedEdge = g[i];
    }
  }
  return make_pair(mst,removedEdge);
}

typedef vector<vector<int>> graph;

template<typename T>
class RMQ {

	public:
		RMQ(vector<T> a) : rmq(), layer_idx(), a(a) {
			int n = a.size();
			int k = floor(log(n)/log(2));
			layer_idx.push_back(0);
			rmq.push_back(vector<int>());
			for(int i = 0; i < n; i++)
				rmq[0].push_back(i);

			for(int i = 1; i <= k; i++) {
				int s = pow(2,i); int m = (s-1)/2;
				layer_idx.push_back(rmq.size());
				for(int j = 0; j < s; j++) {
					rmq.push_back(vector<int>());
					for(int l = j; l+s-1 < n; l += s)
						rmq[layer_idx[i]+j].push_back((a[access(l,l+m)] < a[access(l+m+1,l+s-1)] ? access(l,l+m) : access(l+m+1,l+s-1)));		
				}
			}
		}

		int query(int i, int j) {
			int s = pow(2,floor(log(j-i+1)/log(2)));
			return (a[access(i,i+s-1)] < a[access(j-(s-1),j)] ? access(i,i+s-1) : access(j-(s-1),j));
		}

	private:
		int access(int i, int j) {
			//j-i+1 = 2^n n € N
			int k = j-i+1, layer = floor(log(k)/log(2)), off = i % max(k,1), idx = (i - off)/k;
			return rmq[layer_idx[layer]+off][idx];
		}


		vector<vector<int>> rmq;
		vector<int> layer_idx;
		vector<T> a;

};

//Lowest Common Ancestor implementation with O(n*log(n)) preproccesing
//and O(1) query time
class LCA1 {
public:
  LCA1(graph& g) : g(g) {
    N = g.size(); idx = 0;
    H.assign(N,-1); E.assign(2*N,-1); L.assign(2*N,-1);
    buildLCA(0,-1,0);
    rmq = new RMQ<int>(L);
  }
  
  //LCA-Query with O(1) time complexity
  //Idea: LCA of u and v is the node with the smallest depth/height
  //during dfs within the Interval [H[u],H[v]] in E.
  int lca(int u, int v) {
    if(H[u] > H[v])
      swap(u,v);
    return E[rmq->query(H[u],H[v])];
  }
  
private:

  //LCA preprocessing is simple dfs where H,E and L is build.
  //Time Complexity: O(N)
  void buildLCA(int v, int p, int depth) {
    H[v] = idx; E[idx] = v; L[idx++] = depth;
    for(int u : g[v]) {
      if(p - u) {
	buildLCA(u,v,depth+1);
	E[idx] = v; L[idx++] = depth;
      }
    }
  }
    
  graph& g;
  int N, idx;
  /*
   * H = First occurence of node i during dfs
   * E = In dfs step i node E[i] is visited
   * L = In dfs step i node E[i] has depth/height L[i]
   */
  vector<int> H,E,L;
  RMQ<int> *rmq;
};

vector<int> dist;

void dfs(int u, int d, graph& g, graph& gw) {
    dist[u] = d;
    for(int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i]; int w = gw[u][i];
        if(dist[v] == -1) dfs(v,d+w,g,gw);
    }
}

int distance(LCA1& lca, int s, int t) {
    int l = lca.lca(s,t);
    return dist[s] + dist[t] - 2*dist[l];
}

int main() {
    while(cin >> N) {
        if(N == 0) break;
        
        edge_list<int> tmp_g(N);
        for(int i = 0; i < N; ++i) {
            int u,v,w; cin >> u >> v >> w;
            tmp_g.push_back(make_pair(w,make_pair(u,v)));
        }
        
        auto calc_mst = buildMST<int>(tmp_g);
        edge_list<int> mst = calc_mst.first;
        int u = calc_mst.second.second.first, v = calc_mst.second.second.second;
        int w = calc_mst.second.first;
//         cout << u << " " << v << " " << w << endl;
        
        graph g(N,vector<int>());
        graph gw(N,vector<int>());
        for(int i = 0; i < mst.size(); ++i) {
            int a = mst[i].second.first, b = mst[i].second.second;
            int c = mst[i].first;
            g[a].push_back(b);
            g[b].push_back(a);
            gw[a].push_back(c);
            gw[b].push_back(c);
        }
        
        LCA1 lca(g); 
        dist.assign(N,-1); 
        dfs(0,0,g,gw);
        
        int Q; cin >> Q;
        for(int i = 0; i < Q; ++i) {
            int s, t; cin >> s >> t;
            int d1 = distance(lca,s,t);
            int d2 = distance(lca,s,u) + w + distance(lca,v,t);
            int d3 = distance(lca,s,v) + w + distance(lca,u,t);
            cout << min(d1,min(d2,d3)) << endl;
        }
        
        
        
        
    }
    return 0;
}
