#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ii;
typedef vector<vector<ii>> graph;

//SCC
int counter, sccCounter;
vector<bool> vis, inStack;
vector<int> d, low, sccs;
stack<int> s;

unordered_map<int, int> max_dist;


int N, M;
graph g,b;

vector<int> dp;

void visit(int u) {
  vis[u] = true;
  d[u] = low[u] = counter++;
  s.push(u); inStack[u] = true;
  
  for(auto neigh : g[u]) {
    int v = neigh.first;
    if(!vis[v]) {
      visit(v);
      low[u] = min(low[v],low[u]);
    } else if(inStack[v]) {
      low[u] = min(low[v],low[u]); 
    }
  }
  
  if(d[u] == low[u]) {
    int v;
    do {
      v = s.top(); s.pop(); inStack[v] = false;
      sccs[v] = sccCounter;
    } while(u != v);
    sccCounter++;
  }
  
}

void scc() {
  vis.assign(N,false); inStack.assign(N,false);
  d.assign(N,-1); low.assign(N,-1); sccs.assign(N,-1);
  counter = sccCounter = 0;
  for(int i = 0; i < N; ++i) {
    if(!vis[i]) visit(i);
  }
}

void dfsLongestWaySCC(int u, int dist, int sccNum) {
  vis[u] = true;
  auto max_it = max_dist.find(u);
  if(max_it != max_dist.end()) {
    if(dist > max_it->second) max_dist[u] = dist;
  }
  else max_dist.insert(make_pair(u,dist));
  
  for(auto neigh : g[u]) {
    int v = neigh.first;
    if(sccs[v] == sccNum && !vis[v]) dfsLongestWaySCC(v,dist+1,sccNum);
    else if(sccs[v] != sccNum) b[u+N].push_back(make_pair(v,1));
  }
  vis[u] = false;
}

int findLongestPath(int u) {
  if(dp[u] != -1) return dp[u];
  if(b[u].size() == 0) return 0;
  
  for(auto neigh : b[u]) {
    int v = neigh.first, dist = neigh.second;
    int longest_dist = findLongestPath(v);
    if(longest_dist + dist > dp[u]) dp[u] = longest_dist + dist;
  }
  return dp[u];
}

int main() {

  
  ios::sync_with_stdio(false);
  
  scanf("%d %d",&N,&M);
  g.assign(N,vector<ii>());
  b.assign(2*N,vector<ii>());
  dp.assign(2*N,-1);
  for(int i = 0; i < M; ++i) {
    int u, v; scanf("%d %d",&u,&v); u--; v--;
    g[u].push_back(make_pair(v,1));
  }
  
  //Find SCCs
  scc();
  
  //Build bipartite graph
  vis.assign(N,false);
  for(int u = 0; u < N; ++u) {
    max_dist.clear();
    dfsLongestWaySCC(u,0,sccs[u]);
    for(auto neigh : max_dist) {
      int v = neigh.first, dist = neigh.second;
      if(u == v) b[u].push_back(make_pair(u+N,0));
      else b[u].push_back(make_pair(v+N,dist));
    }
  }

  //DP on acyclic bipartite graph for longest path
  int longest_path = 0;
  for(int u = 0; u < 2*N; ++u) {
    int dist = findLongestPath(u);
    if(dist > longest_path) longest_path = dist;
  }
  
  printf("%d\n",longest_path+1);
  
	return 0;
}
