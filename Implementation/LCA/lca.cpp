#include <bits/stdc++.h>

using namespace std;

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
    
  graph g;
  int N, idx;
  /*
   * H = First occurence of node i during dfs
   * E = In dfs step i node E[i] is visited
   * L = In dfs step i node E[i] has depth/height L[i]
   */
  vector<int> H,E,L;
  RMQ<int> *rmq;
};

//Lowest Common Ancestor implementation with O(n*log(n)) preproccesing
//and O(log(n)) query time
//Idea: For every node store all 2^i ancestors of this node
class LCA2 {
public:
  LCA2(graph& g) : g(g) {
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
