#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ii;
typedef pair<ii,int> iii;

int n, m, p; 
vector<vector<int>> dp;
vector<vector<int>> a;
vector<vector<int>> vis;

int threshold = 1;

vector<ii> neighbors(ii pos) {
  int x = pos.first, y = pos.second;
  vector<ii> neighbor;
  if(x-1 >= 0)
    neighbor.push_back(make_pair(x-1,y));
  if(y-1 >= 0)
    neighbor.push_back(make_pair(x,y-1));
  if(x+1 < n)
    neighbor.push_back(make_pair(x+1,y));
  if(y+1 < m)
    neighbor.push_back(make_pair(x,y+1));
  return neighbor;
}

void bfs(queue<iii>& q, int t) {
  if(t > p) 
    return;
  queue<iii> nq;
  while(!q.empty()) {
    iii cur = q.front(); q.pop();
    ii pos = cur.first;
    int x = pos.first, y = pos.second;
    int dis = cur.second;
    if(a[x][y] == t) {
      dp[x][y] = dis;
      nq.push(make_pair(pos,dis));
      vis[pos.first][pos.second]++;
    }
    for(ii next : neighbors(pos)) {
      if(vis[next.first][next.second] < threshold) {
	vis[next.first][next.second] = threshold;
	q.push(make_pair(next,dis+1));
      }
    }
  }
  threshold++;
  bfs(nq,t+1);
  
}


int main() {
  
  cin >> n >> m >> p;
  a.assign(n,vector<int>(m,0));
  dp.assign(n,vector<int>(m,0));
  vis.assign(n,vector<int>(m,0));
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < m; ++j)
      cin >> a[i][j];
    
  queue<iii> q; q.push(make_pair(make_pair(0,0),0));
  vis[0][0] = 1;
  bfs(q,1);
  
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      //if(a[i][j] == p)
	cout << dp[i][j] << " ";
    }
    cout << endl;
  }
    
  return 0;
}
