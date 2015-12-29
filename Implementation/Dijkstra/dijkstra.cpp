#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define INF INT_MAX/2

typedef pair<int,int> ii;
typedef vector<vector<ii>> graph;

priority_queue<ii,vector<ii>,greater<ii>> pq;
vector<int> dist;
vector<ii> parent;

void initialize(int N) {
  dist.assign(N,INF);
  parent.resize(N);
  priority_queue<ii,vector<ii>,greater<ii>> empty_pq; swap(pq,empty_pq);
}


//Dijkstra-Algorithm for the single-source shortest path problem
//Algorithm finds the shortest path and distance of this path from s to t
//on a graph g.
//Time Complexity: O((m+n)*log(m)) (normally it's O((m+n)*log(n)) but we insert
//a relaxed node into the priority queue again and therefore a node can occur
//several times into the pq)
pair<vector<ii>,int> dijkstra(graph& g, int s, int t) {
  initialize(g.size());
  dist[s] = 0; pq.push(make_pair(0,s));
  while(!pq.empty()) {
    int cur_node = pq.top().second, cur_dist = pq.top().first; pq.pop();
    //If the shortest path from s to cur_node is short than the current pq
    //entry cur_dist the node is already processed and we can continue
    //with the next node.
    if(cur_dist > dist[cur_node]) continue;
    if(cur_node == t) break;
    
    for(int i = 0; i < g[cur_node].size(); i++) {
      int u = g[cur_node][i].first, c = g[cur_node][i].second;
      if(dist[cur_node] + c < dist[u]) {
	dist[u] = dist[cur_node] + c; pq.push(make_pair(dist[u],u));
	parent[u] = make_pair(cur_node,c);
      }
    }
  }
  //Backtrack shortest path from s to t
  vector<ii> path; int cur_node = t;
  while(cur_node != s) {
    path.push_back(make_pair(t,parent[t].second));
    cur_node = parent[t].first;
  }
  reverse(path.begin(),path.end());
  return make_pair(path,dist[t]);
}


int main() {

	return 0;
}
