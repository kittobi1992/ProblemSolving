#include <bits/stdc++.h>

using namespace std;


#define MAXN 105
#define INF INT_MAX

int clean[MAXN][MAXN];
int A[MAXN], B[MAXN], S[MAXN];
int N, M;

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

int getRooms(int i) {
    return S[i]/M + (S[i] % M != 0 ? 1 : 0);
}

int maxFlowWithCapacity(int C) {
    MaxFlow mf(2*N+4); 
    mf.addEdge(2*N,2*N+1,C);
    for(int i = 0; i < N; ++i) {
        mf.addEdge(2*N+2,i,getRooms(i));
        mf.addEdge(i,2*N,INF);
        mf.addEdge(N + i, 2*N + 3, getRooms(i));
        mf.addEdge(2*N+1, N+i, INF);
    }
    
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(i != j) {
                if(B[i] + clean[i][j] < A[j]) mf.addEdge(i,N+j,INF);
            }
        }
    }
    
    return mf.maxFlow(2*N+2,2*N+3);
}

int main() {
  
    int test; cin >> test;
    for(int t = 1; t <= test; ++t) {
        cin >> N >> M;
        int max_cap = 0;
        for(int i = 0; i < N; ++i) cin >> A[i] >> B[i] >> S[i];
        for(int i = 0; i < N; ++i) {
            max_cap += getRooms(i);
            for(int j = 0; j < N; ++j) cin >> clean[i][j];
        }
       
        int l = 0, r = max_cap;
        while(l < r) {
            int m = (l+r)/2;
            int mf = maxFlowWithCapacity(m);
            if(mf < max_cap) l = m+1;
            else r = m;
        }
        
        cout << "Case " << t << ": " << l << endl;
        
    }
    
	return 0;
}
