#include <bits/stdc++.h>

using namespace std;

#define INF INT_MAX/2

typedef pair<int,int> node;
typedef pair<int,node> in;
typedef vector<vector<int>> graph;

vector<node> dir {make_pair(1,0),make_pair(0,1),make_pair(-1,0),make_pair(0,-1)};
priority_queue<in,vector<in>,greater<in>> pq;
graph dist;
int n,m;

node operator+(const node& n1, const node& n2) {
  return make_pair(n1.first+n2.first,n1.second+n2.second);
}

bool isValidNode(const node& no) {
  int x = no.first, y = no.second;
  return x >= 0 && y >= 0 && x < n && y < m;
}

void initialize() {
  dist.assign(n,vector<int>(m,INF));
  priority_queue<in,vector<in>,greater<in>> empty_pq; swap(pq,empty_pq);
}

int dijkstra(graph& g, node s, node t) {
  initialize();
  dist[s.first][s.second] = g[s.first][s.second]; pq.push(make_pair(dist[s.first][s.second],s));
  while(!pq.empty()) {
    node cur_node = pq.top().second;
    int cur_dist = pq.top().first; pq.pop();
    if(cur_dist > dist[cur_node.first][cur_node.second]) continue;
    if(cur_node == t) break;
    
    for(int i = 0; i < 4; i++) {
      node u = cur_node + dir[i];
      if(isValidNode(u)) {
	int c = g[u.first][u.second];
	if(dist[cur_node.first][cur_node.second] + c < dist[u.first][u.second]) {
	  dist[u.first][u.second] = dist[cur_node.first][cur_node.second] + c; pq.push(make_pair(dist[u.first][u.second],u));
	}
      }
    }
  }

  return dist[t.first][t.second];
}


int main() {

  int test; cin >> test;
  while(test--) {
    cin >> n >> m;
    graph g(n,vector<int>(m,0));
    for(int i = 0; i < n; i++)
      for(int j = 0; j < m; j++)
	cin >> g[i][j];
    cout << dijkstra(g,make_pair(0,0),make_pair(n-1,m-1)) << endl;
  }
  
  return 0;
}
