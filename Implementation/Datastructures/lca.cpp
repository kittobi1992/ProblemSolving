#include <iostream>
#include <string.h>
#include <climits>
#include <cmath>
#include <vector>
#include <stack>

using namespace std;

typedef vector<vector<int>> graph;
typedef int Node;
typedef pair<Node, int> ii;

#define NUM_NODES 100
#define LOG_SIZE 10
#define mp(X, Y) make_pair(X, Y)

graph g;

// Stores first occurence of node u in E
// E[H[u]] = u
int H[NUM_NODES];
// Stores nodes visited during euler tour
int E[3*NUM_NODES];
// Stores depths of nodes visited during euler tour
// Depth of node E[i] is L[i]
int L[3*NUM_NODES];

int rmq[LOG_SIZE][NUM_NODES];

/**
 * Build RMQ data structure.
 * rmq[i][j] stores index of the minimum value in 
 * interval [j..j+2^i) of array a.
 * => Preprocessing time and space consumption in O(n*log(n))
 */
void buildRMQ(int n) {
  memset(rmq, 0, sizeof(rmq[0][0]) * NUM_NODES * LOG_SIZE);

  for (int i = 0; i < n; ++i)
    rmq[0][i] = i;

  int l = log2(n) + 1;
  for (int i = 1; i < l; ++i) {
    int size = 1 << i;
    for (int j = 0; j+size < n; ++j) {
      rmq[i][j] = (L[rmq[i-1][j]] <= L[rmq[i-1][j+size/2]]) ? rmq[i-1][j] : rmq[i-1][j+size/2];
    }
  }
}

/**
 * Return index with minimum value of array a in interval [l,r].
 * Time Complexity: O(1)
 */
int rmqQuery(int l, int r) {
  int k = log2(r-l+1);
  int size = 1 << k;
  return (L[rmq[k][l]] <= L[rmq[k][r-size+1]]) ? rmq[k][l] : rmq[k][r-size+1];
}

/**
 * Build LCA data structure
 * Nodes are visited in an eulerian tour.
 */
void buildLCA() {
  memset(H, 0, sizeof(H));
  memset(E, 0, sizeof(E));
  memset(L, 0, sizeof(L));

  int size = 0;
  Node root = 0;
  vector<bool> visited(NUM_NODES, false);
  // Stores next child of a node to visit during the traversal
  vector<int> next_child(NUM_NODES, 0);
  stack<ii> S;
  S.push(mp(root, 0));

  // Simple DFS with preorder traversal
  while (!S.empty()) {
    Node u = S.top().first;
    int depth = S.top().second;
    if (!visited[u]) {
      H[u] = size;
      visited[u] = true;
    }
    E[size] = u;
    L[size++] = depth;

    if (next_child[u] < g[u].size()) {
      Node v = g[u][next_child[u]++];
      S.push(mp(v, depth + 1));
    } else {
      S.pop();
    }
  }

  // RMQ data structure is build over array L,
  // which stores the depth of the nodes visited
  // during the eulerian tour.
  buildRMQ(size);
}

/**
 * Returns the lowest common ancestor of node u and v.
 */
Node lca(Node u, Node v) {
  if (H[u] > H[v]) swap(u, v);
  return E[rmqQuery(H[u], H[v])];
}

int main() {
  // Read Tree
  int n, q;
  cin >> n >> q;
  g.assign(n, vector<int>());
  for (int i = 0; i < n-1; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
  }

  // Build LCA data structure
  buildLCA();

  // Execute LCA queries
  for (int i = 0; i < q; i++) {
    Node u, v;
    cin >> u >> v;
    cout << "LCA of " << u << " and " << v << " is " << lca(u, v) << endl;
  }

  return 0;
}
