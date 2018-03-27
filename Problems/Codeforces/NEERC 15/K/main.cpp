#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> graph;

int S[100010];

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
        S[findSet(b)] += S[findSet(a)];
        parent[findSet(a)] = findSet(b);
  }

  void unionSets(int a, int b) { // Diese Funktion aufrufen.
        if (findSet(a) != findSet(b)) linkSets(findSet(a), findSet(b));
  }
};


int N, M;
graph g;
vector<bool> vis;
UnionFind comp(100010);

int degin[100010], degout[100010];
vector<int> path;

bool dfs(int u, int n) {
//       cout << u + 1 << " " << n << endl;
    
    vis[u] = true;
    path.push_back(u);
    
    if(g[u].size() == 0)
    {
        return false;
    }
    
    int nxt = g[u][0];
    
    if(degout[u] == 1 && degin[u] == 1 && degout[nxt] == 1 && degin[nxt] == 1 && u != 0 && nxt != 0)
    {
        //cout << u + 1 << " seek " << n + S[comp.findSet(u)] - 2 << endl;
        
        if(comp.findSet(u) == 0 && n + S[comp.findSet(u)] - 2 == N)
        {
            return true;
        } else if(comp.findSet(u) != 0) {
            //cout << u + 1 << " dfs " << comp.findSet(u) + 1 << " " << n + S[comp.findSet(u)] - 1<< endl;
            
            if(!vis[comp.findSet(u)] && dfs(comp.findSet(u), n + S[comp.findSet(u)] - 1))
            {
                return true;
            }
        }
    } else {
        for(int v : g[u]) {
//             if(v == 0) cout << u + 1 << " " << 1 << " " << n << endl;
            if(v == 0 && n == N) return true;
            else if(v == 0) continue;
//             cout << u + 1 << " dfs " << v + 1 << " " << n + 1 << endl;
            if(!vis[v] && dfs(v,n+1)) return true;
        }
    }
    path.pop_back();
    vis[u] = false;
    return false;
}


int main() {
//     freopen("king.in", "r",stdin);
//     freopen("king.out", "w",stdout);
    
    cin >> N >> M;
    g.assign(N,vector<int>());
    vis.assign(N,false);
    
    for(int i = 0; i < 100010; i++)
    {
        S[i] = 1;
    }
    
    for(int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        
        degout[u]++;
        degin[v]++;
    }
    
    for(int i = 0; i < N; ++i) {
        if(degin[0] == 0 || degout[i] == 0) {
            cout << "There is no route, Karl!" << endl;
            return 0;
        }
    }
    
    for(int i = 1; i < N; i++)
    {
        int nxt = g[i][0];
        
        if(degout[i] == 1 && degin[i] == 1 && degout[nxt] == 1 && degin[nxt] == 1 && i != 0  && nxt != 0)
        {
//             cout << "union " << i << " " << g[i][0] << endl;
            comp.unionSets(i, g[i][0]);
        }
    }
    
//     for(int i = 0; i < 5; i++)
//     {
//         cout << S[i] << " ";
//     }
//     
//     cout << endl;
    
    if(dfs(0,1)) {
        for(int i = 0; i < path.size(); ++i) {
            int c = path[i];
            int nxt = g[c][0];
            
            if(degin[path[i]] == 1 && degout[path[i]] == 1 && degout[nxt] == 1 && degin[nxt] == 1 && c != 0 && nxt != 0)
            {
                while(degout[c] == 1 && degin[c] == 1 && degout[nxt] == 1 && degin[nxt] == 1 && c != 0 && nxt != 0)
                {
                    cout << c + 1 << " ";
                    c = g[c][0];
                    
                    if(g[c].size() != 1)
                    {
                        break;
                    }
                    
                    nxt = g[c][0];
                }
            } else {
                cout << (path[i]+1) << " ";
            }
        }
        cout << "1" << endl;
    }
    else {
        cout << "There is no route, Karl!" << endl;
    }
    
    return 0;
}
