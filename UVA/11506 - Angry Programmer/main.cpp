#include <bits/stdc++.h>

using namespace std;


#define INF INT_MAX
#define MAXV 102

typedef vector<vector<int>> graph;

int res[MAXV][MAXV];
int N, M, W, s, t;
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

    while(cin >> M >> W) {
        if(M == 0 && W == 0) break;
        
        N = 2*M-2;
        s = 0; t = 2*M-3;
        initalize();
        
        for(int i = 0; i < M-2; ++i) {
            int id, c; cin >> id >> c; id--;
            int u = 2*id-1, v = 2*id;
            g[u].push_back(v);
            g[v].push_back(u);
            res[u][v] = c;
        }
        
        for(int i = 0; i < W; ++i) {
            int u,v,c; cin >> u >> v >> c;
            u--; v--;
            int u1, v1, u2, v2;
            
            if(u == 0) { u1 = v2 = 0; }
            else if(u == M-1) { u1 = v2 = 2*M-3; }
            else { u1 = 2*u; v2 = 2*u-1; }
            
            if(v == 0) { v1 = u2 = 0;  }
            else if(v == M-1) { v1 = u2 = 2*M-3; }
            else { v1 = 2*v-1; u2 = 2*v; }
            
            g[u1].push_back(v1);
            g[v1].push_back(u1);
            g[u2].push_back(v2);
            g[v2].push_back(u2);
            res[u1][v1] = c;
            res[u2][v2] = c;
        }
        
        cout << maxFlow() << endl;
        
    }
    
	return 0;
}
