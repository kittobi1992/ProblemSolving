#include <bits/stdc++.h>

using namespace std;

#define INVALID_NODE INT_MAX/2
#define INVALID_WEIGHT INT_MAX/2
#define FOREACH(G, u, v) for (Node v : G[u])
#define FOR(G, u) for (int i = 0; i < G[u].size(); ++i)
#define NODES(u, N) for (Node u = 0; u < n; ++u)
#define MAXN 102

typedef int Node;
typedef int Weight;

template<typename type = Node>
using Graph = vector<vector<type>>;

Weight res[MAXN][MAXN];
Node parent[MAXN];
int N, M, W, s, t;
Graph<Node> g;

/**
 * Simple fast reset flag array data structure
 * If visited[i] == thres, than visited[i] is true,
 * otherwise (visited[i] < thres) it is interpreted as false.
 * We can simply reset all entries to false by incrementing thres.
 */
int visited[MAXN];
int thres = 1;


void initalize() {
    memset(res, 0, sizeof res);
    memset(parent, INVALID_NODE, sizeof parent);
    g.assign(N, vector<int>());
}

/**
 * Breath-First-Search starting from source node s 
 * and searching for sink node t in the residual graph.
 * Returns true, if a path from s to t in the residual 
 * graph exists.
 */
bool bfs() {
    thres++;  // reset visited array
    queue<Node> q;
    q.push(s);
    visited[s] = thres;
    parent[s] = -1;

    while (!q.empty()) {
        Node u = q.front();
        q.pop();
        if (u == t) return true;

        FOREACH(g, u, v) {
            if (visited[v] < thres && res[u][v]) {
                q.push(v);
                visited[v] = thres;
                parent[v] = u;
            }
        }
    }

    return false;
}

/**
 * Increases the flow along the augmenting path found
 * by the BFS traversal of the residual graph.
 * Returns the amount of flow which is send over
 * the augmenting path.
 * NOTE: Function should be called with sink node t.
 */
Weight augment(Node u, Weight flow = INVALID_WEIGHT) {
    if (parent[u] == -1) return flow;
    Weight min_flow = augment(parent[u], min(flow, res[parent[u]][u]));
    res[parent[u]][u] -= min_flow;
    res[u][parent[u]] += min_flow;
    return min_flow;
}

/**
 * Edmond-Karps Maximum Flow Algorithm
 * Returns the value of the maximum flow.
 */
Weight maximumFlow() {
    Weight mf = 0;
    while (bfs()) {
        mf += augment(t);
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
        
        cout << maximumFlow() << endl;
        
    }
    
	return 0;
}
