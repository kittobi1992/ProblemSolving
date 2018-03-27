#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> graph;

int n, m; 

int bfs(graph& g) {
  int dist = -1;
  int s = 0, t = n-1;
  vector<bool> vis(n,false);
  queue<int> q, nq;
  q.push(s); vis[s] = true;
  int cur_dist = 0;
  while(!q.empty()) {
    int u = q.front(); q.pop();
    if(u == t) {
      dist = cur_dist;
      break;
    }
    for(int i = 0; i < g[u].size(); i++) {
      int v = g[u][i];
      if(!vis[v]) {
	vis[v] = true; nq.push(v);
      }
    }
    if(q.empty()) {
      cur_dist++;
      swap(q,nq);
    }
    
  }
  
  return dist;
}

int main() {

  graph rail, road;
  cin >> n >> m;
  rail.assign(n,vector<int>()); road.assign(n,vector<int>());
  for(int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    u--; v--;
    rail[u].push_back(v);
    rail[v].push_back(u);
  }
  
  for(int i = 0; i < n; i++) {
    sort(rail[i].begin(),rail[i].end());
  }
  
  for(int i = 0; i < n; i++) {
    for(int j = i+1; j < n; j++) {
      if(!binary_search(rail[i].begin(),rail[i].end(),j)) {
	road[i].push_back(j);
	road[j].push_back(i);
      }
    }
  }
  
  int dist_rail = bfs(rail);
  int dist_road = bfs(road);
  
  cout << (dist_rail != -1 && dist_road != -1 ? max(dist_road,dist_rail) : -1) << endl;
  
  return 0;
}