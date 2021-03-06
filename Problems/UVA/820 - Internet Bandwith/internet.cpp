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
		MaxFlow(int nodes) { 
			n = nodes; 
			e.assign(n,vector<edge>());
		}

		void addEdge(int u, int v, int capacity) {
			edge e1, e2;
			e1.v = v; e1.flow = 0; e1.capacity = capacity;
			e2.v = u; e2.flow = 0; e2.capacity = capacity;
			e1.bIndex = e[v].size();	
			e2.bIndex = e[u].size();
			e[u].push_back(e1);
			e[v].push_back(e2);
		}


		int maxFlow(int s, int t) {
			int mf = 0;
	
			while(true) {
				pair<vector<int>,vector<int>> bfs = findPath(s,t);
				vector<int> path = bfs.first;
				vector<int> eIndex = bfs.second;
				if(path[t] == -1) {
					break;
				}
				mf += increaseFlowAlongPath(t,path,eIndex);
			}
				
			
			return mf;
		}

		int edgesCount() {
			int count = 0;
			for(int i = 0; i < n; i++) count += e[i].size();
			return count;
		}


	private:

		int increaseFlowAlongPath(int t, vector<int>& path, vector<int>& eIndex) {
			int flow = flowAlongPath(t,path,eIndex);
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
			vector<bool> visited(n,false);
			queue<int> q;
			q.push(s);
			visited[s] = true;
			while(!q.empty()) {
				int cur = q.front(); q.pop();
				if(cur == t)
					break;
				for(int i = 0; i < e[cur].size(); i++) {
					int v = e[cur][i].v;
					int rc = e[cur][i].residualCapacity();
					if(rc > 0 && !visited[v]) {
						parent[v] = cur;
						eIndex[v] = i;
						q.push(v);
						visited[v] = true;
					}
				}
			}
			return make_pair(parent,eIndex);
		}

		int n;
		vector<vector<edge>> e;

};


int main() {
	
	int network = 1;
	while(true) {
		int n;
		cin >> n;
		if(n == 0)
			break;

		MaxFlow mf(n);
		int s, t, c;
		cin >> s >> t >> c;

		for(int i = 0; i < c; i++) {
			int u,v,f;
			cin >> u >> v >> f;
			mf.addEdge(--u,--v,f);
		}


		int max_flow = mf.maxFlow(--s,--t);
		cout << "Network " << network << endl;
		cout << "The bandwidth is " << max_flow << ".\n" << endl;
		network++;

	}

	return 0;
}
