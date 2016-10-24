#include <bits/stdc++.h>

using namespace std;


typedef long long ll;

struct store {
    int idx;
    ll k, p;
};

typedef vector<vector<int>> graph;
typedef vector<vector<store>> stores;

ll thres = 1;
vector<ll> vis;
graph g; stores s;

using PQ = priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>>;

ll bfs(int c, ll r, ll a) {
    queue<int> q;
    q.push(c);
    vis[c] = thres;
    ll dist = -1;
    ll cur_dist = 0;
    queue<int> new_q;
    PQ pq;
    ll sum_r = 0, sum_p = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        
        for(int i = 0; i < s[u].size(); ++i) {
            pq.push(make_pair(s[u][i].p,s[u][i].k));
            if(sum_r < r) {
                int shovels = min(r-sum_r,s[u][i].k);
                sum_r += s[u][i].k;
                sum_p += shovels*s[u][i].p;
            }
        }
        
        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if(vis[v] < thres) {
                vis[v] = thres;
                new_q.push(v);
            }
        }
        
        if(q.empty()) {
            if(sum_r == r && sum_p <= a) {
                dist = cur_dist;
                break;
            }
            
            if(sum_r >= r) {
                PQ old_pq(pq);
                sum_r = 0;
                sum_p = 0;
                while(!pq.empty()) {
                    ll k = pq.top().second; ll p = pq.top().first; pq.pop();
                    ll shovels = min(r-sum_r,k);
                    sum_r += shovels;
                    sum_p += shovels*p;
                    if(sum_r >= r) break;
                }
                swap(pq,old_pq);
                if(sum_r >= r && sum_p <= a) dist = cur_dist;
                else swap(q,new_q);
            }
            else swap(q,new_q);
            cur_dist++;
        }
    }
        
    return dist;
}

int main() {
  
    int n,m; cin >> n >> m;
    g.assign(n, vector<int>());
    vis.assign(n,0);
    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    s.assign(n,vector<store>());
    int w; cin >> w;
    for(int i = 0; i < w; ++i) {
        int c; store st; cin >> c >> st.k >> st.p;
        st.idx = w;
        c--;
        s[c].push_back(st);
    }
    
    int q; cin >> q;
    for(int i = 0; i < q; ++i) {
        int c; ll r, a; cin >> c >> r >> a;
        c--;
        ll min_dist = bfs(c,r,a);
        cout << min_dist << endl;
        thres++;
    }
    
    return 0;
}
