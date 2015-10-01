#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

#define MAX_PLACE 15

vector<bool> visited;
set<int> numbers;
int L;

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
			e2.v = u; e2.flow = 0; e2.capacity = 0;
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


int access(int n, int i) {
	return (n & (1 << i)) >> i;
}

vector<int> next_numbers(int n) {
	vector<int> next;
	for(int i = 0; i < MAX_PLACE; i++) {
		int v = n + ((int) (1 << i));
		if(access(n,i) && v <= L) {
			next.push_back(v);
		}
	}
	return next;
}

void dfs(int u, MaxFlow& mf) {
	visited[u] = true;
	numbers.insert(u);
	vector<int> next = next_numbers(u);
	for(int v : next) {
		if(!visited[v])
			dfs(v,mf);
		mf.addEdge(u,v+L,1);
	}
}

int main() {

	int test;
	cin >> test;	
	int c = 1;
	while(test--) {
		int n;
		cin >> n >> L;
		visited.assign(L,false);		
		numbers.clear();
		
		MaxFlow mf(2*L + 2);
		int s = 0; int t = 2*L + 1;

		for(int i = 0; i < n; i++) {
			int s; cin >> s;
			dfs(s,mf);
		}

		for(int v : numbers) {
			mf.addEdge(s,v,1);
			mf.addEdge(v + L, t, 1);
		}

		int max_flow = mf.maxFlow(s,t);
		cout << "Case " << c << ": " << (numbers.size() - max_flow) << endl;
		cout << "Active Nodes: " << numbers.size() << endl;
		cout << "Edges: " << mf.edgesCount() << endl;
		c++;

	}

	return 0;
}
