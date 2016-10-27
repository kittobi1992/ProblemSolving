#include <bits/stdc++.h>

using namespace std;



int M, W;

struct edge {
    int b, v, flow, capacity;
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
    
    void printGraph() {
        for(int i = 0; i < n; ++i) {
            cout << "Node " << i << ": ";
            for(int j = 0; j < e[i].size(); ++j) {
                if(e[i][j].capacity > 0) cout << e[i][j].v << " ";
            }
            cout << endl;
        }
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



int main() {

    while(cin >> M >> W) {
        if(M == 0 && W == 0) break;
        
        MaxFlow flow(2*M-2);
        int s = 0, t = 2*M-3;
        for(int i = 0; i < M-2; ++i) {
            int id, c; cin >> id >> c; id--;
            flow.addEdge(2*id-1,2*id,c);
        }
        
        for(int i = 0; i < W; ++i) {
            int u,v,c; cin >> u >> v >> c;
            u--; v--;
            int u1, v1, u2, v2;
            
            if(u == 0) { u1 = v2 = 0; }
            else if(u == M-1) { u1 = v2 = 2*M-3; }
            else { u1 = 2*u; v2 = 2*u-1; }
            
            if(v == 0) { v1 = u2 = 0;  }
            else if(v == M-1) { v1 = u2 = 2*M-3; }
            else { v1 = 2*v-1; u2 = 2*v; }
            
            flow.addEdge(u1,v1,c);
            flow.addEdge(u2,v2,c);
        }
        //flow.printGraph();
        cout << flow.maxFlow(s,t) << endl;
        
    }
    
	return 0;
}
