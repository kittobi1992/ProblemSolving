#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;
typedef pair<int,ll> il;
typedef vector<vector<il>> graph;
typedef vector<int> vi;

#define INVALID -1
#define MAXN 100000

int N;
ll sp[MAXN];
int H[MAXN];
int E[2*MAXN];
int L[2*MAXN];

vector<vector<int>> rmq(floor(log2(2*MAXN)) + 1, vector<int>(2*MAXN));

void initRMQ () {
  for(int i = 0, s = 1, ss = 1; s <= 2*N ; ss=s, s*=2 , i++) {
    for(int l = 0; l + s <= 2*N ; l++) {
      if(i == 0) rmq [0][l] = l;
      else {
	int r = l + ss;
	rmq[i][l] = (L[rmq[i -1][l]] <= L[rmq[i -1][r]] ? rmq[i -1][l] : rmq[i -1][r]);
      }
    }
  }
}

// returns index of minimum ! [a, b)
int queryRMQ (int l, int r) {
  if(l >= r) return l;
  int s = floor (log2(r-l)); r = r - (1 << s);
  return (L[rmq[s][l]] <= L[rmq[s][r]] ? rmq[s][l] : rmq[s][r]);
}

class LCA {
public:
  LCA(graph& g) : g(g) {
    idx = 0;
    buildLCA(0,-1,0);
    initRMQ();
  }
  
  //LCA-Query with O(1) time complexity
  int lca(int u, int v) {
    if(H[u] > H[v])
      swap(u,v);
    return E[queryRMQ(H[u],H[v])];
  }
  
private:

  void buildLCA(int v, int p, int depth) {
    H[v] = idx; E[idx] = v; L[idx++] = depth;
    for(il node : g[v]) {
      int u = node.first;
      if(p - u) {
	buildLCA(u,v,depth+1);
	E[idx] = v; L[idx++] = depth;
      }
    }
  }
    
  graph g;
  int N, idx;
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

	memset(H,-1,sizeof(H)); memset(E,-1,sizeof(E));  memset(L,-1,sizeof(L));
	memset(sp,0,sizeof(sp));
  
	while(cin >> N) {
		if(N == 0)
			break;

		graph g(N,vector<il>()); 
		for(int i = 1; i < N; i++) {
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
