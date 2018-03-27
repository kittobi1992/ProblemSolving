#include <bits/stdc++.h>

using namespace std;

#define INVALID_NODE INT_MAX/2
#define INVALID_WEIGHT INT_MAX/2
#define FOREACH(G, u, v) for (Node v : G[u])
#define FOR(G, u) for (int i = 0; i < G[u].size(); ++i)
#define NODES(u, N) for (Node u = 0; u < N; ++u)

typedef int Node;
typedef int Weight;

template<typename type = Node>
using Graph = vector<vector<type>>;

int n, m, h;
Graph<Node> g;
vector<int> a;

int cur_num, num_scc;
vector<bool> visited, inStack;
vector<int> num, low, scc_num;
stack<int> s;

// If SCCs are contracted, this data structure
// contains the mapping from each SCC to its
// corresponding nodes.
Graph<Node> scc_to_node;

void initialize() {
    cur_num = num_scc = 0;
    visited.assign(n, false);
    inStack.assign(n, false);
    num.assign(n, 0);
    low.assign(n, 0);
    scc_num.assign(n, 0);
}

void visit(Node u) {
    visited[u] = true;
    num[u] = low[u] = cur_num++;
    s.push(u);
    inStack[u] = true;

    FOREACH(g, u, v) {
        if (!visited[v]) {
            visit(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], low[v]);
        }
    }

    if (num[u] == low[u]) {
        Node v;
        do {
            v = s.top();
            s.pop();
            inStack[v] = false;
            scc_num[v] = num_scc;
        } while (u != v);
        num_scc++;
    }
}

void tarjan() {
    initialize();
    NODES(u, n) {
        if (!visited[u]) {
            visit(u);
        }
    }
}

Graph<Node> contractSCC() {
    vector<set<Node>> tmp_g(num_scc, set<Node>());
    scc_to_node.assign(num_scc, vector<Node>());

    NODES(u, n) {
        Node scc_u = scc_num[u];
        scc_to_node[scc_u].push_back(u);
        FOREACH(g, u, v) {
            Node scc_v = scc_num[v];
            if (scc_u != scc_v) tmp_g[scc_u].insert(scc_v);
        }
    }

    Graph<Node> contraction(num_scc, vector<Node>());
    NODES(u, num_scc) {
        FOREACH(tmp_g, u, v) {
            contraction[u].push_back(v);
        }
    }
    return contraction;
}

int main() {
    cin >> n >> m >> h;
    g.assign(n, vector<int>());
    a.assign(n, 0);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        if ( (a[x] + 1) % h == a[y] ) {
            g[x].push_back(y);
        }
        if ( (a[y] + 1) % h == a[x] ) {
            g[y].push_back(x);
        }
    }

    tarjan();

    Graph<Node> c = contractSCC();

    int min_scc = -1;
    int min_size = INT_MAX;
    NODES(u, num_scc) {
        if (c[u].size() == 0) {
            if (min_size > scc_to_node[u].size()) {
                min_scc = u;
                min_size = scc_to_node[u].size();
            }
        }
    }

    cout << min_size << endl;
    for (int i = 0; i < min_size; ++i) {
        cout << (scc_to_node[min_scc][i] + 1) << (i == min_size - 1 ? "\n" : " ");
    }

    return 0;
}
