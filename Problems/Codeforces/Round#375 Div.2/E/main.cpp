#include <bits/stdc++.h>

using namespace std;

#define MAXN 205

int N, M;
int g1[MAXN][MAXN], g2[MAXN][MAXN];
bool vis[MAXN];
int deg[MAXN];

void clear() {
    for(int i = 0; i < MAXN; ++i) {
        deg[i] = 0; vis[i] = false;
        for(int j = 0; j < MAXN; ++j) {
            g1[i][j] = 0; g2[i][j] = 0;
        }
    }
}

void prepareForEulerTour(int u) {
    queue<int> q; q.push(u);
    vis[u] = true;
    vector<int> odd;
    int size = 0;
    while(!q.empty()) {
        int v = q.front(); q.pop();
        size++;
        if(deg[v] % 2 == 1) odd.push_back(v);
        for(int i = 0; i < N; ++i) {
            if(g1[v][i] > 0 && !vis[i]) {
                vis[i] = true;
                q.push(i);
            }
        }
    }
    if(size > 2) {
        for(int i = 0; i < odd.size(); i += 2) {
            int u = odd[i], v = odd[i+1];
            if(g1[u][v]) { g1[u][v] = 3; g1[v][u] = 3; }
            else { g1[u][v] = 2; g1[v][u] = 2; }
        }
    }
}

void eulerTour(int u) {
    for(int v = 0; v < N; ++v) {
        if(g1[u][v] > 0) {
            if(g1[u][v] < 2) g2[u][v] = 1;
            if(g1[u][v] == 3) { g1[u][v] = 1; g1[v][u] = 1; }
            else { g1[u][v] = 0; g1[v][u] = 0; }
            eulerTour(v);
        }
    }
}


int main() {
    
    int T; cin >> T;
    while(T--) {
         cin >> N >> M;
         clear();
         for(int i = 0; i < M; ++i) {
             int u,v; cin >> u >> v;
             u--; v--;
             g1[u][v] = 1; g1[v][u] = 1;
             deg[u]++; deg[v]++;
         }
         
         for(int i = 0; i < N; ++i) {
            if(!vis[i]) {
                prepareForEulerTour(i);
                eulerTour(i);
            }
         }
         
         vector<int> in_deg(N,0), out_deg(N,0);
         for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(g2[i][j]) {
                    in_deg[j]++; out_deg[i]++;
                }
            }
         }
         
         int in_eq_out = 0;
         for(int i = 0; i < N; ++i) {
            if(in_deg[i] == out_deg[i]) in_eq_out++;    
         }
         
         cout << in_eq_out << endl;
         for(int i = 0; i < N; ++i) 
             for(int j = 0; j < N; ++j) 
                 if(g2[i][j]) cout << i+1 << " " << j+1 << endl;
         
    }
    
	return 0;
}
