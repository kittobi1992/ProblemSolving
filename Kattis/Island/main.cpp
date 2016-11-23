#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> graph;

vector<string> input;
vector<string> m;
vector<vector<int>> m2;

int N, M, T;
bool vis[85][85];
vector<bool> visited;
graph g;

void initialize() {
  N = m.size(); M = m[0].size();
  memset(vis,0,sizeof(vis));
  m2.assign(N,vector<int>(M,-1));
}

void dfs_graph(int u) {
  visited[u] = true;
  for(int v : g[u])
    if(!visited[v]) dfs_graph(v);
}

void dfs(int x, int y, int num) {
  vis[x][y] = true;
  m2[x][y] = num;
  if(x < N-1 && (m[x+1][y] == '#' || m[x+1][y] == 'X') && !vis[x+1][y]) dfs(x+1,y,num);
  if(x > 0 && (m[x-1][y] == '#' || m[x-1][y] == 'X') && !vis[x-1][y]) dfs(x-1,y,num);
  if(y < M-1 && (m[x][y+1] == '#' || m[x][y+1] == 'X') && !vis[x][y+1]) dfs(x,y+1,num);
  if(y > 0 && (m[x][y-1] == '#' || m[x][y-1] == 'X') && !vis[x][y-1]) dfs(x,y-1,num);
}

void findBridges(int x, int y, int start, bool b) {
//     cout << x << " " << y << " " << m[x][y] << " "<<start <<" " << " " << m2[x][y]<< " " << vis[x][y] << endl;
  if(m[x][y] == 'X' && start != m2[x][y] && b) { g[start].push_back(m2[x][y]); return; }
  else if(m[x][y] == 'X' && !vis[x][y] && !b) return;
  vis[x][y] = true;
 
  if(x < N-1 && (m[x+1][y] == 'B' || m[x+1][y] == 'X') && !vis[x+1][y]) findBridges(x+1,y,start,b|(m[x+1][y] == 'B'));
  if(x > 0 && (m[x-1][y] == 'B' || m[x-1][y] == 'X') && !vis[x-1][y]) findBridges(x-1,y,start,b|(m[x-1][y] == 'B'));
  if(y < M-1 && (m[x][y+1] == 'B' || m[x][y+1] == 'X') && !vis[x][y+1]) findBridges(x,y+1,start,b|(m[x][y+1] == 'B'));
  if(y > 0 && (m[x][y-1] == 'B' || m[x][y-1] == 'X') && !vis[x][y-1]) findBridges(x,y-1,start,b|(m[x][y-1] == 'B'));
}

void solve() {
  initialize();
  
  int num = 0;
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < M; ++j) {
      if(!vis[i][j] && (m[i][j] == '#' || m[i][j] == 'X')) dfs(i,j,num++);
    }
  }
  
  g.assign(num,vector<int>());
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < M; ++j) {
      if(m[i][j] == 'X') {
        memset(vis,0,sizeof(vis));
        vis[i][j] = true;
        findBridges(i,j,m2[i][j],false);
      }
    }
  }
  
  visited.assign(num,false);
  int islands = num;
  int bridges = 0;
  int busses = 0;
  for(int i = 0; i < num; ++i) {
    if(!visited[i]) { dfs_graph(i); busses++; }
    bridges += g[i].size();
  }
  bridges /= 2;
  
  cout << "Map " << T << endl;
  cout << "islands: " << islands << endl;
  cout << "bridges: " << bridges << endl;
  cout << "buses needed: " << busses << endl;
  
  m.clear();
}

int main() {
   
  string s;
  while(getline(cin,s)) input.push_back(s);
  input.push_back("");
  
  T = 1;
  for(int i = 0; i < input.size(); ++i) {
    if(input[i] != "") m.push_back(input[i]);
    else { 
      if(T != 1) cout << endl;
      solve(); T++;
    }
  }
    
	return 0;
}
