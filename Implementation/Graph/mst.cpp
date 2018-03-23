#include <queue>
#include <set>
#include <numeric>
#include <algorithm>

#include "definitions.h"

#define mp(X, Y) make_pair(X, Y)

using Edge = pair<Node, Node>;
using Label = pair<Weight, Edge>;
using PQ = priority_queue<Label, vector<Label>, greater<Label>>;

Graph<Node> mst;
Graph<Weight> mst_w;

/******************************************************
 *       KRUSKAL MINIMUM SPANNING TREE ALGORITHM      *
 ******************************************************/

// Union Find Data Structure
vector<Node> parent;
vector<int> tree_size;

void initialize() {
    parent.assign(n, 0);
    tree_size.assign(n, 1);
    iota(parent.begin(), parent.end(), 0);
}

/**
 * Returns the representive node of the set in which
 * node u is contained. Additionally, path compression
 * is performed.
 */
Node find(Node u) {
    if (parent[u] != u) parent[u] = find(parent[u]);
    return parent[u];
}

/**
 * Merging the two sets in which node u and v is contained.
 * Union by size is performed to improve running time.
 */
void link(Node u, Node v) {
    if (tree_size[u] < tree_size[v]) {
        parent[u] = v;
    } else if (tree_size[v] < tree_size[u]) {
        parent[v] = u;
    } else {
        parent[u] = v;
        tree_size[v]++;
    }
}

/**
 * Computes a minimum spanning tree with Kruskal's algorithm.
 * Returns the weight of the minimum spanning tree.
 */
Weight kruskal() {
    Weight mst_cost = 0;
    mst.assign(n, vector<Node>());
    mst_w.assign(n, vector<Weight>());

    // Convert graph into a sorted edge list
    set<Label> edges;
    NODES(u, n) {
        FOR(g, u) {
            Node v = g[u][i];
            Weight weight = w[u][i];
            // min(u,v) and max(u,v) ensures that each edge is only
            // inserted once into the edge list (undirected graph
            // contains (u,v) and (v,u))
            edges.insert(mp(weight, mp(min(u, v), max(u, v))));
        }
    }

    // Initialize Union-Find data structure
    initialize();
    // Traverse edge list in increasing weight order
    for (Label l : edges) {
        Weight weight = l.first;
        Node u = l.second.first;
        Node v = l.second.second;
        if (find(u) != find(v)) {
            mst_cost += weight;
            mst[u].push_back(v);
            mst[v].push_back(u);
            mst_w[u].push_back(weight);
            mst_w[v].push_back(weight);
            link(find(u), find(v));
        }
    }

    return mst_cost;
}

/******************************************************
 *   JARNIK-PRIM'S MINIMUM SPANNING TREE ALGORITHM    *
 ******************************************************/

/**
 * Computes a minimum spanning tree with Jarnik-Prims algorithm.
 * Returns the weight of the minimum spanning tree.
 */
Weight jarnikPrim() {
    Weight mst_cost = 0;
    mst.assign(n, vector<Node>());
    mst_w.assign(n, vector<Weight>());

    PQ pq;
    vector<bool> visited(n, false);
    visited[0] = true;
    FOR(g, 0) pq.push(mp(w[0][i], mp(0, g[0][i])));

    while (!pq.empty()) {
        Weight weight = pq.top().first;
        Node u = pq.top().second.first;
        Node v = pq.top().second.second;
        pq.pop();
        if (visited[v]) continue;

        mst_cost += weight;
        mst[u].push_back(v);
        mst[v].push_back(u);
        mst_w[u].push_back(weight);
        mst_w[v].push_back(weight);
        visited[v] = true;

        FOR(g, v) {
            pq.push(mp(w[v][i], mp(v, g[v][i])));
        }
    }

    return mst_cost;
}

// Use Implementation/Graph/input/1.in for example input
int main() {
    // Read weighted undirected graph (1-indexed)
    readGraph<true, true, true>();
    printGraph();

    // Compute MST with Jarnik-Prims MST algorithm
    cout << "Compute MST with Jarnik-Prims algorithm" << endl;
    Weight mst_cost = jarnikPrim();
    cout << "Minimum Spanning Tree Weight: " << mst_cost << endl;
    cout << "Minimum Spanning Tree: " << endl;
    printGraph(mst, &mst_w);

    // Compute MST with Kruskal's MST algorithm
    cout << "Compute MST with Krukal's algorithm" << endl;
    mst_cost = kruskal();
    cout << "Minimum Spanning Tree Weight: " << mst_cost << endl;
    cout << "Minimum Spanning Tree: " << endl;
    printGraph(mst, &mst_w);

}