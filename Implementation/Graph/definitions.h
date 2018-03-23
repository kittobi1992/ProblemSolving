#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define INVALID_NODE INT_MAX/2
#define INVALID_WEIGHT INT_MAX/2
#define FOREACH(G, u, v) for (Node v : G[u])
#define FOR(G, u) for (int i = 0; i < G[u].size(); ++i)
#define NODES(u, N) for (Node u = 0; u < n; ++u)

typedef int Node;
typedef int Weight;

template<typename type = Node>
using Graph = vector<vector<type>>;

int n, m;
Graph<Node> g;
Graph<Weight> w;

template<bool undirected = false>
void addEdge(Node u, Node v, Weight weight) {
    g[u].push_back(v);
    if (weight != INVALID_WEIGHT) w[u].push_back(weight);
    if (undirected) {
        g[v].push_back(u);
        if (weight != INVALID_WEIGHT) w[v].push_back(weight);
    }
}

template<bool weighted = true,
         bool undirected = false,
         bool one_indexed = true>
void readGraph() {
    cin >> n >> m;
    g.assign(n, vector<Node>());
    if (weighted) w.assign(n, vector<Weight>());

    for (int i = 0; i < m; ++i) {
        Node u, v;
        Weight w = INVALID_WEIGHT;
        cin >> u >> v;
        if (one_indexed) {
            u--;
            v--;
        }
        if (weighted) cin >> w;
        addEdge<undirected>(u, v, w);
    }
}

template<bool weighted = true,
         bool one_indexed = true>
void printGraph() {
    cout << "N = " << n << ", M = " << m << endl;
    for (Node u = 0; u < n; ++u) {
        cout << "Node " << (one_indexed ? (u+1) : u) << ": ";
        FOR(g, u) {
            int v = g[u][i];
            cout << (one_indexed ? (v+1) : v);
            if (weighted) {
                cout << "(" << w[u][i] << ")";
            }
            cout << " ";
        }
        cout << endl;
    }
}