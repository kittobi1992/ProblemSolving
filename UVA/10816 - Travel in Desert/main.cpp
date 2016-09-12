#include <bits/stdc++.h>

using namespace std;

#define INF DBL_MAX/4.0

using dd = pair<double,double>;
using di = pair<double,int>;
using ddi = pair<dd,int>;
using graph = vector<vector<ddi>>;

int n,m,s,t;

graph g;

priority_queue<di,vector<di>,greater<di>> pq;
vector<double> dist;
vector<int> parent;

void initialize() {
	dist.assign(n,INF);
	parent.resize(n);
	priority_queue<di,vector<di>,greater<di>> empty_pq; swap(pq,empty_pq);
}


//Dijkstra-Algorithm for the single-source shortest path problem
//Algorithm finds the shortest path and distance of this path from s to t
//on a graph g.
//Time Complexity: O((m+n)*log(m)) (normally it's O((m+n)*log(n)) but we insert
//a relaxed node into the priority queue again and therefore a node can occur
//several times into the pq)
double dijkstraTemp() {
	initialize();
	dist[s] = 0.0; pq.push(make_pair(0.0,s));
	while(!pq.empty()) {
		int cur_node = pq.top().second; double cur_temp = pq.top().first; pq.pop();
		//If the shortest path from s to cur_node is short than the current pq
		//entry cur_dist the node is already processed and we can continue
		//with the next node.
		if(cur_temp > dist[cur_node]) continue;
		if(cur_node == t) break;
		
		for(int i = 0; i < g[cur_node].size(); i++) {
			int u = g[cur_node][i].second; double c_temp = g[cur_node][i].first.first;
			if(max(c_temp,dist[cur_node]) < dist[u]) {
				dist[u] = max(c_temp,cur_temp); pq.push(make_pair(dist[u],u));
				parent[u] = cur_node;
			} 
		}
	}
	
	return dist[t];
}

pair<vector<int>,double> dijkstra(double max_temp) {
	initialize();
	dist[s] = 0.0; pq.push(make_pair(0.0,s));
	while(!pq.empty()) {
		int cur_node = pq.top().second; double cur_dist = pq.top().first; pq.pop();
		//If the shortest path from s to cur_node is short than the current pq
		//entry cur_dist the node is already processed and we can continue
		//with the next node.
		if(cur_dist > dist[cur_node]) continue;
		if(cur_node == t) break;
		
		for(int i = 0; i < g[cur_node].size(); i++) {
			int u = g[cur_node][i].second; double c_dist = g[cur_node][i].first.second, c_temp = g[cur_node][i].first.first;
			if(cur_dist + c_dist < dist[u] && c_temp <= max_temp) {
				dist[u] = cur_dist + c_dist; pq.push(make_pair(dist[u],u));
				parent[u] = cur_node;
			}
		}
	}
	//Backtrack shortest path from s to t
	vector<int> path; int cur_node = t;
	while(cur_node != s) {
		path.push_back(cur_node);
		cur_node = parent[cur_node];
	}
	path.push_back(s);
	reverse(path.begin(),path.end());
	return make_pair(path,dist[t]);
}

int main() {
  
	while(cin >> n >> m) {
		cin >> s >> t;
		s--; t--;
		g.clear();
		g.assign(n,vector<ddi>());
		for(int i = 0; i < m; ++i) {
			int u,v; double r,d;
			cin >> u >> v >> r >> d;
			u--; v--;
			g[u].push_back({{r,d},v});
			g[v].push_back({{r,d},u});
		}
		
		double max_temp = dijkstraTemp();
		auto res = dijkstra(max_temp);
		vector<int> path = res.first;
		for(int i = 0; i < path.size(); ++i) cout << (path[i]+1) << ((i+1 != path.size()) ? " " : "\n");
		
		cout << fixed << setprecision(1) << res.second<< " " << max_temp << endl;
	
		
	}
	
  	return 0;
}
