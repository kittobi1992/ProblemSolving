#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ii;

typedef vector<vector<ii>> graph;
priority_queue<pair<int,ii>,vector<pair<int,ii>>,greater<pair<int,ii>> > pq;

graph g;

graph buildMST() {
  int mst_cost = 0; int N = g.size(); graph mst(N,vector<ii>());
  vector<bool> vis(N,false);
  
  vis[0] = true;
  for(int i = 0; i < g[0].size(); ++i) pq.push({g[0][i].second,{0,g[0][i].first}});
  
  while(!pq.empty()) {
    auto cur = pq.top(); pq.pop();
    int c = cur.first; int u = cur.second.first, v = cur.second.second;
    if(vis[u] == vis[v])
      continue;
    mst[u].push_back({v,c}); mst[v].push_back({u,c}); mst_cost += c;
    vis[v] = true; 
    for(int i = 0; i < g[v].size(); ++i) pq.push({g[v][i].second,{v,g[v][i].first}});
  }
  
  return mst;
}

int main() {
  
  return 0;
}
