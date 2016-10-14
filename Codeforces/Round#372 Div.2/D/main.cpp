#include <bits/stdc++.h>

using namespace std;

#define MAXN 1002
#define MAXL 1e10
typedef long long ll;

ll w[MAXN][MAXN];
bool var[MAXN][MAXN];
int n,m,s, t;
ll L;

template<typename T>
using graph = vector<vector<T>>;

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
    pair<vector<int>,T> dijkstra() {
        initialize();
        dist[s] = static_cast<T>(0); pq.push(make_pair(static_cast<T>(0),s));
        bool found = false;
        while(!pq.empty()) {
            int cur_node = pq.top().second; T cur_dist = pq.top().first; pq.pop();
            //If the shortest path from s to cur_node is short than the current pq
            //entry cur_dist the node is already processed and we can continue
            //with the next node.
            if(cur_dist > dist[cur_node]) continue;
            if(cur_node == t) { found = true; break; }
            
            for(int i = 0; i < g[cur_node].size(); i++) {
                int u = g[cur_node][i]; T c = w[cur_node][u];
                if(dist[cur_node] + c < dist[u]) {
                    dist[u] = dist[cur_node] + c; pq.push(make_pair(dist[u],u));
                    parent[u] = cur_node;
                }
            }
        }
        //Backtrack shortest path from s to t
        vector<int> path; int cur_node = t;
        if(!found) return make_pair(path,MAXL+1);
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

bool adjustPath(vector<int>& path, ll distance) {
    ll cur_distance = 0;
    int first_zero_idx = -1;
    for(int i = 0; i < path.size()-1; ++i) {
        int u = path[i], v = path[i+1];
        if(var[u][v] && first_zero_idx == -1) {
            first_zero_idx = i;
        } 
        cur_distance += w[u][v];
    }
    
    if(first_zero_idx != -1) {
        int u = path[first_zero_idx], v = path[first_zero_idx+1];
        ll old_weight = w[u][v];
        w[u][v] = std::max(L - cur_distance+w[u][v],w[u][v]); w[v][u] = max(L - cur_distance+w[v][u],w[v][u]);
        cur_distance += (w[u][v]-old_weight);
    }
    return cur_distance >= L;
}

int main() {
    cin >> n >> m >> L >> s >> t;
    graph<ll> g(n,vector<ll>());
    for(int i = 0; i < m; ++i) {
        int u, v; ll weight; cin >> u >> v >> weight;
        g[u].push_back(v);
        g[v].push_back(u);
        w[u][v] = weight;
        w[v][u] = weight;
        if(w[u][v] == 0) { var[u][v] = true; var[v][u] = true; }
    }
    
    for(int u = 0; u < g.size(); ++u) {
        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if(w[u][v] == 0) {
                w[u][v] = 1; w[v][u] = 1;
            }
        }
    }
    
    
    
    Dijkstra<ll> dijkstra(g);
    bool found = false;
    while(true) {
        auto shortestPath = dijkstra.dijkstra();
        vector<int> path = shortestPath.first;
        ll distance = shortestPath.second;
        if(distance == L) { found = true; break; }
        else if(distance < L) {
            if(!adjustPath(path,distance)) break;
        }
        else {
            break;
        }
    }
    
    if(!found) { cout << "NO" << endl; return 0; }
    
    cout << "YES" << endl;
    for(int u = 0; u < g.size(); ++u) {
        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if(u < v) {
                cout << u << " " << v << " " << w[u][v] << endl;
            }
        }
    }
    
    return 0;
}