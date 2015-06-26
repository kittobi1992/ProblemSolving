#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;
typedef vector<vector<ll>> graph;
typedef vector<int> vi;

#define INVALID -1

int n;

vector<int> L, E, H; 
int idx = 0;

vector<vector<int>> rmq;

#define MAX_N 20000
#define LOG_TWO_N 100
class RMQ {
	private:
		vector<int> _A;
		vector<vector<int>> SpT;

	public:
	RMQ(int n, vector<int> A) {
		_A.resize(n);
		SpT.resize(n,vector<int>(ceil(log(n)+1),0));
		for (int i = 0; i < n; i++) {
			_A[i] = A[i];
			SpT[i][0] = i;
		}
		for (int j = 1; (1<<j) <= n; j++)
			for (int i = 0; i + (1<<j) - 1 < n; i++)
				if (_A[SpT[i][j-1]] < _A[SpT[i+(1<<(j-1))][j-1]])
					SpT[i][j] = SpT[i][j-1];
				else
					SpT[i][j] = SpT[i+(1<<(j-1))][j-1];
	}

	int query(int i, int j) {
		int k = (int)floor(log((double)j-i+1) / log(2.0));
		if (_A[SpT[i][k]] <= _A[SpT[j-(1<<k)+1][k]]) 
			return SpT[i][k];
		else
			return SpT[j-(1<<k)+1][k];
	} 
};


int lca(int l, int r, RMQ& rmq) {
	if(H[l] > H[r])
		swap(l,r);
	return E[rmq.query(H[l],H[r])];
}

void dfs(int start_node, int cur, ll distance, int depth, graph& g, graph& sp, vector<bool>& visited) {
	visited[cur] = true;
	sp[start_node][cur] = distance;
	H[cur] = idx;
	E[idx] = cur;
	L[idx++] = depth;
	for (int i = 0; i < g[cur].size(); i++) {
		if(!visited[g[cur][i]]) {
			dfs(start_node, g[cur][i], distance + sp[cur][g[cur][i]], depth+1, g, sp, visited);
			E[idx] = cur;
			L[idx++] = depth;
		}
	}
}

void buildLCAArrays(graph& g, graph& sp) {
	vector<bool> visited(n,false);
	rmq.assign(ceil(log2(2*n)) + 1, vector<int>(2*n));
	idx = 0;
	H.assign(2*n,-1);
	dfs(0, 0, 0, 0, g, sp, visited);
} 

int main() {

	while(cin >> n) {
		if(n == 0)
			break;

		rmq.clear();
		L.clear();
		L.resize(2*n);
		E.clear();
		E.resize(2*n);
		H.clear();
		H.resize(2*n);

		graph g(n,vector<ll>());
		graph sp(n,vector<ll>(n,0));
		for(int i = 1; i < n; i++) {
			ll a, l;
			cin >> a >> l;
			g[i].push_back(a);
			g[a].push_back(i);
			sp[i][a] = l;
			sp[a][i] = l;
		}		

		
		buildLCAArrays(g, sp);
		RMQ rmq(L.size(), L);
	
		int q;
		cin >> q;
		for(int i = 0; i < q-1; i++) {
			int s,t;
			cin >> s >> t;
			int a = lca(s,t,rmq);
			cout << (sp[0][s] + sp[0][t] - 2*sp[0][a]) << " ";
		}
		int s,t;
		cin >> s >> t;
		int a = lca(s,t,rmq);
		cout << (sp[0][s] + sp[0][t] - 2*sp[0][a]) << endl;

	}
	
	return 0;
}
