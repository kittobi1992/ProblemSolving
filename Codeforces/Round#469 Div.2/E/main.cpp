#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> graph;

int n, m, h;
graph g;
vector<int> a;

int counter, sccCounter;
vector<bool> visited, inStack;
vector<int> d, low, sccs;
stack<int> s;

void visit(int v) {
    visited[v] = true;
    d[v] = counter;
    low[v] = counter;
    counter++;
    inStack[v] = true;
    s.push(v);

    for(int i = 0; i < g[v].size(); ++i) {
        int u = g[v][i];
        if(!visited[u]) {
            visit(u);
            low[v] = min(low[v], low[u]);
        } else if(inStack[u]) {
            low[v] = min(low[v],low[u]);
        }
    }

    if(d[v] == low[v]) {
        int u;
        do {
            u = s.top();
            s.pop();
            inStack[u] = false;
            sccs[u] = sccCounter;
        } while( u != v );
        sccCounter++;
    }
}

int main() {
    cin >> n >> m >> h;
    g.assign(n, vector<int>());
    a.assign(n,0);
    for(int i = 0; i < n; ++i) cin >> a[i];
    for(int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y;
        x--; y--;
        if( (a[x] + 1) % h == a[y] ) {
            g[x].push_back(y);
        }
        if( (a[y] + 1) % h == a[x] ) {
            g[y].push_back(x);
        }
    }

    visited.assign(n,false);
    d.assign(n,0); 
    low.assign(n,0);
    inStack.assign(n,false);
    sccs.assign(n,0);

    counter = 0;
    sccCounter = 0;
    for(int i = 0; i < n; ++i) {
        if(!visited[i]) {
            visit(i);
        }
    }

    vector<vector<int>> scc_to_node(sccCounter,vector<int>());
    vector<set<int>> c(sccCounter, set<int>());
    for(int v = 0; v < n; ++v) {
        int scc = sccs[v];
        scc_to_node[scc].push_back(v);
        for(int i = 0; i < g[v].size(); ++i) {
            int u = g[v][i];
            int scc_u = sccs[u];
            if(scc != scc_u) {
                c[scc].insert(scc_u);
            }
        }
    }

    int min_scc = -1;
    int min_size = INT_MAX;
    for(int i = 0; i < sccCounter; ++i) {
        if(c[i].size() == 0) {
            if(min_size > scc_to_node[i].size()) {
                min_scc = i;
                min_size = scc_to_node[i].size();
            }
        }
    }

    cout << min_size << endl;
    for(int i = 0; i < min_size; ++i) {
        cout << (scc_to_node[min_scc][i] + 1) << (i == min_size - 1 ? "\n" : " ");
    }

	return 0;
}
