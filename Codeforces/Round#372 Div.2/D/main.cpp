#include <bits/stdc++.h>

using namespace std;

#define MAXN 1002
#define MAXL 1e10
#define mp(X, Y) make_pair(X, Y)

typedef long long ll;

#define INVALID_NODE INT_MAX/2
#define INVALID_WEIGHT LLONG_MAX/2
#define FOREACH(G, u, v) for (Node v : G[u])
#define FOR(G, u) for (int i = 0; i < G[u].size(); ++i)

typedef int Node;
typedef ll Weight;

template<typename type = Node>
using Graph = vector<vector<type>>;
using Label = pair<Weight, Node>;
using PQ = priority_queue<Label, vector<Label>, greater<Label>>;

Graph<Node> g;
ll w[MAXN][MAXN];
bool var[MAXN][MAXN];
int n, m,s, t;
ll L;

vector<Weight> d;
vector<Node> parent;
PQ pq;

void initialize() {
    d.assign(n, INVALID_WEIGHT);
    parent.assign(n, INVALID_NODE);
    PQ empty_pq;
    swap(pq, empty_pq);
}

Weight dijkstra(Node s, Node t) {
    d[s] = 0;
    pq.push(mp(0, s));

    while (!pq.empty()) {
        Node u = pq.top().second;
        Node dist = pq.top().first;
        pq.pop();

        if (dist > d[u]) continue;
        if (u == t) break;

        FOR(g, u) {
            int v = g[u][i];
            int weight = w[u][v];
            if (d[u] + weight < d[v]) {
                d[v] = d[u] + weight;
                parent[v] = u;
                pq.push(mp(d[v], v));
            }
        }
    }

    return d[t];
}

vector<Node> shortestPath(Node s, Node t) {
    vector<Node> sp;
    Node cur = t;
    while (cur != s) {
        sp.push_back(cur);
        cur = parent[cur];
    }
    sp.push_back(s);
    reverse(sp.begin(), sp.end());
    return sp;
}


bool adjustPath(vector<int>& path, ll distance) {
    ll cur_distance = 0;
    int first_zero_idx = -1;
    for(int i = 0; i < path.size()-1; ++i) {
        int u = path[i], v = path[i+1];
        if(var[u][v] && first_zero_idx == -1) {
            first_zero_idx = i;
        } 
        cur_distance += w[u][v];
    }
    
    if(first_zero_idx != -1) {
        int u = path[first_zero_idx], v = path[first_zero_idx+1];
        ll old_weight = w[u][v];
        w[u][v] = std::max(L - cur_distance+w[u][v],w[u][v]); w[v][u] = max(L - cur_distance+w[v][u],w[v][u]);
        cur_distance += (w[u][v]-old_weight);
    }
    return cur_distance >= L;
}

int main() {
    cin >> n >> m >> L >> s >> t;
    g.assign(n, vector<Node>());
    for (int i = 0; i < m; ++i) {
        int u, v; ll weight; cin >> u >> v >> weight;
        g[u].push_back(v);
        g[v].push_back(u);
        w[u][v] = weight;
        w[v][u] = weight;
        if(w[u][v] == 0) { var[u][v] = true; var[v][u] = true; }
    }

    for (int u = 0; u < g.size(); ++u) {
        for (int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if (w[u][v] == 0) {
                w[u][v] = 1; w[v][u] = 1;
            }
        }
    }
    
    bool found = false;
    while(true) {
        initialize();
        Weight distance = dijkstra(s, t);
        if (distance == L) { found = true; break; }
        else if (distance < L) {
            vector<Node> path = shortestPath(s, t);
            if (!adjustPath(path,distance)) break;
        }
        else {
            break;
        }
    }
    
    if(!found) { cout << "NO" << endl; return 0; }
    
    cout << "YES" << endl;
    for(int u = 0; u < g.size(); ++u) {
        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if(u < v) {
                cout << u << " " << v << " " << w[u][v] << endl;
            }
        }
    }
    
    return 0;
}