#include <stack>
#include <set>

#include "definitions.h"

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

/** 
 * Simple Depth-First-Search extended with
 * SCC calculation
 */
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

/**
 * Computes all strongly connected components of the input
 * graph g. Afterwards, array scc_num contains the corresponding
 * SCC number foreach node.
 */
void tarjan() {
    initialize();
    NODES(u, n) {
        if (!visited[u]) {
            visit(u);
        }
    }
}

/**
 * Contracts the input graph by contracting all SCCs 
 * into a single node.
 * Precondition: Call tarjan() before calling contractSCC()
 */
Graph<Node> contractSCC() {
    // Using a temporary graph which contains a edge set
    // foreach node to prevent duplication check during
    // contraction
    vector<set<Node>> tmp_g(num_scc, set<Node>());
    scc_to_node.assign(num_scc, vector<Node>());

    NODES(u, n) {
        Node scc_u = scc_num[u];
        scc_to_node[scc_u].push_back(u);
        FOREACH(g, u, v) {
            Node scc_v = scc_num[v];
            // Ignore self loops
            if (scc_u != scc_v) tmp_g[scc_u].insert(scc_v);
        }
    }

    // Build graph data structure for contracted graph
    Graph<Node> contraction(num_scc, vector<Node>());
    NODES(u, num_scc) {
        FOREACH(tmp_g, u, v) {
            contraction[u].push_back(v);
        }
    }
    return contraction;
}

// Use Implementation/Graph/input/4.in for example input
int main() {
    // Read unweighted directed graph (1-indexed)
    readGraph<false, false, true>();
    printGraph<false, true>();

    // Compute strongly connected components with Tarjan's algorithm
    tarjan();

    // Print strongly connected components
    cout << "Number of strongly connected components: " << num_scc << endl;
    cout << "Nodes to SCC: ";
    NODES(u, n) {
        cout << u << "(" << scc_num[u] << ") ";
    }
    cout << endl;

    // Contract strongly connected components
    Graph<Node> contraction = contractSCC();
    cout << "Contracted Graph:" << endl;
    printGraph<false>(contraction);
    cout << "SCC to Nodes: " << endl;
    printGraph<true>(scc_to_node);
}