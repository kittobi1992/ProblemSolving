#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

struct edge {
	int v, flow, capacity;
	int bIndex; //backwardEdgeIndex

	int residualCapacity() {
		return capacity - flow;
	}

};

class MaxFlow {

	public:
		MaxFlow(int nodes, bool debug = false) { 
			n = nodes; 
			io = debug;
			e.assign(n,vector<edge>());
		}

		void addEdge(int u, int v, int capacity) {
			edge e1, e2;
			e1.v = v; e1.flow = 0; e1.capacity = capacity;
			e2.v = u; e2.flow = 0; e2.capacity = 0;
			e1.bIndex = e[v].size();	
			e2.bIndex = e[u].size();
			e[u].push_back(e1);
			e[v].push_back(e2);
		}


		int maxFlow(int s, int t) {
			int mf = 0;
	
			while(true) {
				if(io)
					cout << "Start searching shortest path from s = " << s << " to t = " << t << endl;
				pair<vector<int>,vector<int>> bfs = findPath(s,t);
				vector<int> path = bfs.first;
				vector<int> eIndex = bfs.second;
				if(path[t] == -1) {
					cout << "No path found! Terminating..." << endl;
					cout << "-------------------------------------" << endl;
					break;
				}
				if(io) {
					vector<int> p;
					int cur = t;
					while(cur != -1) {
						p.push_back(cur); cur = path[cur];	
					}					
					for(int i = p.size()-1; i > 0; i--)
						cout << p[i] << " -> ";
					cout << p[0] << endl;										
				}
				mf += increaseFlowAlongPath(t,path,eIndex);
				cout << "Current Max Flow mf = " << mf << endl;
				cout << "-------------------------------------" << endl;
			}
				
			
			return mf;
		}


	private:

		int increaseFlowAlongPath(int t, vector<int>& path, vector<int>& eIndex) {
			int flow = flowAlongPath(t,path,eIndex);
			cout << "Flow along path is f = " << flow << endl;
			int cur = t;
			while(path[cur] != -1) {
				e[path[cur]][eIndex[cur]].flow += flow;
				e[cur][e[path[cur]][eIndex[cur]].bIndex].flow -= flow;
				cur = path[cur];
			}
			return flow;
		}

		int flowAlongPath(int t, vector<int>& path, vector<int>& eIndex) {
			int flow = INT_MAX;
			int cur = t;
			while(path[cur] != -1) {
				int rc = e[path[cur]][eIndex[cur]].residualCapacity();
				flow = min(flow,rc);
				cur = path[cur];
			}
			return flow;
		}

		pair<vector<int>,vector<int>> findPath(int s, int t) {
			vector<int> parent(n,-1);
			vector<int> eIndex(n);
			vector<bool> in_queue(n,false);
			queue<int> q;
			q.push(s);
			in_queue[s] = true;
			while(!q.empty()) {
				int cur = q.front(); q.pop();
				if(cur == t)
					break;
				for(int i = 0; i < e[cur].size(); i++) {
					int v = e[cur][i].v;
					int rc = e[cur][i].residualCapacity();
					if(rc > 0 && !in_queue[v]) {
						parent[v] = cur;
						eIndex[v] = i;
						q.push(v);
						in_queue[v] = true;
					}
				}
			}
			return make_pair(parent,eIndex);
		}

		int n;
		bool io;
		vector<vector<edge>> e;

};

int main() {

	int n, m;
	cin >> n >> m;

	MaxFlow mf(n,true);
	for(int i = 0; i < m; i++) {
		int u, v, capacity;
		cin >> u >> v >> capacity;
		mf.addEdge(u,v,capacity);
	}
	
	int s, t;
	cin >> s >> t;
	cout << "-----------------------------------------------" << endl;
	cout << "Starting Edmond-Karps Max-Flow-Algorithm..." << endl;
	cout << "-----------------------------------------------" << endl;
	int max_flow = mf.maxFlow(s,t);
	cout << "MaxFlow = " << max_flow << endl;
	cout << "-----------------------------------------------" << endl;


	return 0;
}
