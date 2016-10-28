#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

#define INF INT_MAX
#define MAXV 1000

typedef vector<vector<int>> graph;

int res[MAXV][MAXV];
int N, M, s, t;
graph g;
vector<int> parent;

void initalize() {
    memset(res,0,sizeof res);
    g.assign(N,vector<int>());
    parent.assign(N,-1);
    iota(parent.begin(),parent.end(),0);
}

bool bfs() {
    vector<bool> vis(N,false);
    queue<int> q;
    q.push(s); vis[s] = true; parent[s] = s;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        if(u == t) return true;
        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if(res[u][v] && !vis[v]) {
                q.push(v); vis[v] = true; parent[v] = u;
            }
        }
    }
    return false;
}

int augment(int v, int minFlow) {
    if(v == s) return minFlow;
    else {
        int f = augment(parent[v],min(minFlow,res[parent[v]][v]));
        res[parent[v]][v] -= f;
        res[v][parent[v]] += f;
        return f;
    }
}

int maxFlow() {
    int mf = 0;
    while(bfs()) {
        int f = augment(t,INF);
        mf += f;
    }
    return mf;
}


int main() {

	cin >> N >> M;
    initalize();
	for(int i = 0; i < M; i++) {
		int u, v, capacity;
		cin >> u >> v >> capacity;
        g[u].push_back(v);
        g[v].push_back(u);
        res[u][v] = capacity;
	}
	cin >> s >> t;

    cout << maxFlow() << endl;

	return 0;
}
