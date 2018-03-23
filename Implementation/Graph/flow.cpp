#include <queue>
#include <string.h>

#include "definitions.h"

#define MAXN 200

Weight res[MAXN][MAXN];
Node parent[MAXN];

/**
 * Simple fast reset flag array data structure
 * If visited[i] == thres, than visited[i] is true,
 * otherwise (visited[i] < thres) it is interpreted as false.
 * We can simply reset all entries to false by incrementing thres.
 */
int visited[MAXN];
int thres = 1;

/**
 * Initialize flow problem based on current graph g.
 * The edge weights of the graph are assigned to 
 * the residual capacity array res.
 */
void reset() {
    memset(res, 0, sizeof res);
    memset(parent, INVALID_NODE, sizeof parent);
    // Assign edge weights to capacity array
    NODES(u, n) {
        FOR(g, u) {
            Node v = g[u][i];
            res[u][v] = w[u][i];
        }
    }
}

/**
 * Breath-First-Search starting from source node s 
 * and searching for sink node t in the residual graph.
 * Returns true, if a path from s to t in the residual 
 * graph exists.
 */
bool bfs(Node s, Node t) {
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
Weight maximumFlow(Node s, Node t) {
    Weight mf = 0;
    while (bfs(s, t)) {
        mf += augment(t);
    }
    return mf;
}

/**
 * Returns a bipartition which corresponds to the
 * maximum flow between source node s and sink node t.
 * Precondition: Call maximumFlow(s,t) before calling minimumCut.
 */
vector<int> minimumCut(Node s, Node t) {
    vector<int> bipartition(n, 1);
    // All nodes touched by BFS in the residual graph
    // of a maximum flow are part of the first block and
    // all others are part of the second block.
    bfs(s, t);
    NODES(u, n) {
        if (visited[u] == thres)
            bipartition[u] = 0;
    }
    return bipartition;
}

int main() {
    // Read weighted directed graph (1-indexed)
    readGraph<true, false, true>();
    printGraph();

    // Preparing data structures for maximum flow computation
    reset();

    // Compute value of the maximum flow
    Weight mf = maximumFlow(0, 5);
    cout << "Maximum Flow: " << mf << endl;

    // Compute corresponding minimum bipartition
    vector<int> bipartition = minimumCut(0, 5);
    cout << "Minimum Cut: ";
    NODES(u, n) {
        cout << (u+1) << "(" << bipartition[u] << ") ";
    }
    cout << endl;
}