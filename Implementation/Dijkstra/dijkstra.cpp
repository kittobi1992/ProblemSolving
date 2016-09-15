#include <bits/stdc++.h>
#include <iostream>

using namespace std;


template<typename T>
using edge = pair<int,T>;

template<typename T>
using graph = vector<vector<edge<T>>>;

template<typename T>
class Dijkstra {
	using PQ = priority_queue<pair<T,int>,vector<pair<T,int>>,greater<pair<T,int>>>;
	#define INF numeric_limits<T>::max()/static_cast<T>(2)
	
public:
	Dijkstra(graph<T>& g) : g(g), N(g.size()) { }
	
	//Dijkstra-Algorithm for the single-source shortest path problem
	//Algorithm finds the shortest path and distance of this path from s to t
	//on a graph g.
	//Time Complexity: O((m+n)*log(m)) (normally it's O((m+n)*log(n)) but we insert
	//a relaxed node into the priority queue again and therefore a node can occur
	//several times into the pq)
	pair<vector<int>,T> dijkstra(int s, int t) {
		initialize();
		dist[s] = static_cast<T>(0); pq.push(make_pair(static_cast<T>(0),s));
		while(!pq.empty()) {
			int cur_node = pq.top().second; T cur_dist = pq.top().first; pq.pop();
			//If the shortest path from s to cur_node is short than the current pq
			//entry cur_dist the node is already processed and we can continue
			//with the next node.
			if(cur_dist > dist[cur_node]) continue;
			if(cur_node == t) break;
			
			for(int i = 0; i < g[cur_node].size(); i++) {
				int u = g[cur_node][i].first; T c = g[cur_node][i].second;
				if(dist[cur_node] + c < dist[u]) {
					dist[u] = dist[cur_node] + c; pq.push(make_pair(dist[u],u));
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
	
private:
	
	void initialize() {
		dist.assign(N,INF);
		parent.resize(N);
		PQ empty_pq; swap(pq,empty_pq);
	}
	
	int N;
	PQ pq;
	graph<T> g;
	vector<T> dist;
	vector<int> parent;
	
};

template<typename T>
graph<T> readGraph(ifstream& fin) {
	int n, m; fin >> n >> m;
	graph<T> g(n, vector<edge<T>>());	
	for(int i = 0; i < m; ++i) {
		int u,v; T c; fin >> u >> v >> c;
		u--; v--;
		g[u].emplace_back(make_pair(v,c));
		g[v].emplace_back(make_pair(u,c));
	}
	return g;
}

template<typename T>
void printResult(const pair<vector<int>,T>& result) {
	vector<int> path = result.first;
	T dist = result.second;
	cout << "Shortest Path Distance: " << dist << endl;
	cout << "Shortest Path: " << endl;
	for(int i = 0; i < path.size(); ++i)
		cout << (path[i]+1) << (((i+1) == path.size()) ? "\n" : " -> ");
	cout << "--------------------" << endl;
}

int main() {

	ifstream fin1("1.in");
	graph<int> g1 = readGraph<int>(fin1);
	Dijkstra<int> d1(g1);
	printResult(d1.dijkstra(0,5));
	
	ifstream fin2("2.in");
	graph<double> g2 = readGraph<double>(fin2);
	Dijkstra<double> d2(g2);
	printResult(d2.dijkstra(0,5));
	
	ifstream fin3("3.in");
	graph<long long> g3 = readGraph<long long>(fin3);
	Dijkstra<long long> d3(g3);
	printResult(d3.dijkstra(0,5));
	
	return 0;
}
