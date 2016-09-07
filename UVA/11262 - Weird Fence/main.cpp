#include <bits/stdc++.h>

using namespace std;

struct edge {
	int v, flow, capacity;
	int bIndex; //backwardEdgeIndex
	
	int residualCapacity() {
		return capacity - flow;
	}
	
};

typedef pair<int,int> point;

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
			if(path[t] == -1) break;
			mf += increaseFlowAlongPath(t,path,eIndex);
		}
		
		
		return mf;
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
	vector<vector<edge>> e;
	
};


int distance(point& p1, point& p2) {
	return (p2.first-p1.first)*(p2.first-p1.first) + (p2.second-p1.second)*(p2.second-p1.second);	
}

int main() {
	
	int test; cin >> test;
	while(test--) {
		int P, k; cin >> P >> k;	
		vector<point> red, blue;
		for(int i = 0; i < P; ++i) {
			int x, y; string col;
			cin >> x >> y >> col;
			if(col == "red") red.push_back(make_pair(x,y));
			else blue.push_back(make_pair(x,y));
		}
		int nr = red.size(), nb = blue.size();
		
		int l = 0, r = 3000;
		int res = INT_MAX;
		while(l < r) {
			int m = (l+r)/2;
			MaxFlow mf(nr+nb+2);	
			for(int i = 0; i < nr; ++i) {
				for(int j = 0; j < nb; ++j) {
					if(distance(red[i],blue[j]) <= m*m) mf.addEdge(i+1,nr+j+1,1);
				}
			}
			for(int i = 1; i <= nr; ++i) mf.addEdge(0,i,1);
			for(int i = 1; i <= nb; ++i) mf.addEdge(nr+i,nr+nb+1,1);
			int flow = mf.maxFlow(0,nr+nb+1);
			if(flow >= k) r = m, res = min(res,m);
			else l = m+1;
		}
		
		if(res != INT_MAX)
			cout << res << endl;
		else cout << "Impossible" << endl;
		
	}
  
  return 0;
}
