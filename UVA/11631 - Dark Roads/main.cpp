#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ii;

typedef vector<vector<ii>> graph;
priority_queue<pair<int,ii>,vector<pair<int,ii>>,greater<pair<int,ii>> > pq;

graph g;
int *vis = new int[200000];
int threshold = 1;

int mstCost() {
  int mst_cost = 0; int N = g.size(); graph mst(N,vector<ii>());
  
  vis[0] = threshold;
  for(int i = 0; i < g[0].size(); ++i) pq.push({g[0][i].second,{0,g[0][i].first}});
  
  while(!pq.empty()) {
    auto cur = pq.top(); pq.pop();
    int c = cur.first; int u = cur.second.first, v = cur.second.second;
    if(vis[u] == threshold && vis[v] == threshold)
      continue;
    mst[u].push_back({v,c}); mst[v].push_back({u,c}); mst_cost += c;
    vis[v] = threshold; 
    for(int i = 0; i < g[v].size(); ++i) pq.push({g[v][i].second,{v,g[v][i].first}});
  }
  
  return mst_cost;
}

int main() {
  int n, m;
  while(cin >> n >> m) {
    if(n == 0 && m == 0)
      break;
    g.clear(); g.assign(n,vector<ii>());
    int total_cost = 0;
    for(int i = 0; i < m; ++i) {
      int u,v,c; cin >> u >> v >> c;
      total_cost += c;
      g[u].emplace_back(v,c); g[v].emplace_back(u,c);
    }
    threshold++;
    cout << total_cost - mstCost() << endl;
    
  }
  
  return 0;
}
