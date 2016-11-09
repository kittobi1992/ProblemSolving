#include <bits/stdc++.h>

using namespace std;

#define INF INT_MAX
#define MAXV 1005

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
    
    int T; cin >> T;
    while(T--) {
        int c, d, v; cin >> c >> d >> v;
        N = 2*v+2;
        vector<string> v1(v), v2(v);
        for(int i = 0; i < v; ++i) cin >> v1[i] >> v2[i]; 
        
        initalize();
        
        for(int i = 0; i < v; ++i) {
            for(int j = 0; j < v; ++j) {
                if(v1[i] == v2[j] || v2[i] == v1[j]) {
                    if(v1[i][0] == 'C') {
                        g[i+1].push_back((j+1) + v);
                        g[j+1+v].push_back(i+1);
                        res[i+1][(j+1)+v] = 1;
                    } else {
                        g[j+1].push_back(i+1+v);
                        g[i+1+v].push_back(j+1);
                        res[j+1][i+1+v] = 1;
                    }
                }
            }
        }
        
        for(int i = 1; i <= v; ++i) {
            g[0].push_back(i);
            g[i].push_back(0);
            g[i+v].push_back(N-1);
            g[N-1].push_back(i+v);
            res[0][i] = 1;
            res[i+v][N-1] = 1;
        }
        
        s = 0; t = N-1;
        
        cout << v-maxFlow() << endl;
        
    }
    
    
	return 0;
}
