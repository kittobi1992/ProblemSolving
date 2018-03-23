#include <queue>
#include <algorithm>

#include "definitions.h"

#define mp(X, Y) make_pair(X, Y)

using Label = pair<Weight, Node>;
using PQ = priority_queue<Label, vector<Label>, greater<Label>>;

vector<Weight> d;
vector<Node> parent;
PQ pq;

void initialize() {
    d.assign(n, INVALID_WEIGHT);
    parent.assign(n, INVALID_NODE);
    PQ empty_pq;
    swap(pq, empty_pq);
}

/**
 * Dijkstra's algorithm for the single-source shortest path problem.
 * Returns the length of the shortest path from s to t
 * Note: If you are interested in the shortest path you can call
 *       function shortestPath(s,t) after Dijkstra algorithm
 */
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
            int weight = w[u][i];
            if (d[u] + weight < d[v]) {
                d[v] = d[u] + weight;
                parent[v] = u;
                pq.push(mp(d[v], v));
            }
        }
    }

    return d[t];
}

/**
 * Returns the shortest path between node s and t.
 * Precondition: Call dijkstra(s,t) before calling this function.
 */
template<bool one_indexed = true>
vector<Node> shortestPath(Node s, Node t) {
    vector<Node> sp;
    Node cur = t;
    while (cur != s) {
        sp.push_back(one_indexed ? cur + 1 : cur);
        cur = parent[cur];
    }
    sp.push_back(one_indexed ? s + 1 : s);
    reverse(sp.begin(), sp.end());
    return sp;
}

int main() {
    readGraph<true, false, true>();
    printGraph();

    // Initialize Dijkstra data structures
    initialize();

    // Compute length of shortest path
    Weight length = dijkstra(0, 5);
    cout << "Shortest Path Length: " << length << endl;

    // Construct shortest path
    vector<Node> sp = shortestPath(0, 5);
    cout << "Shorthest Path: ";
    for (Node u : sp) {
        cout << u << " ";
    }
    cout << endl;
}