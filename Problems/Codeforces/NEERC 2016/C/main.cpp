#include <bits/stdc++.h>

using namespace std;


typedef long long ll;

struct store {
    int c;
    ll k, p;
};

typedef vector<vector<int>> graph;
#define N 5000

graph g;
vector<store> stores;
int d[N];

void bfs(int c) {
    memset(d,-1,sizeof(int)*N);
    queue<int> q;
    q.push(c);
    d[c] = 0;
    ll cur_dist = 1;
    queue<int> new_q;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        
        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if(d[v] == -1) {
                d[v] = cur_dist;
                new_q.push(v);
            }
        }
        
        if(q.empty()) {
            swap(q,new_q);
            cur_dist++;
        }
    }
}

bool check(int dist, ll r, ll a) {
    ll sum_r = 0, sum_p = 0;
    for(int i = 0; i < stores.size(); ++i) {
        int c = stores[i].c;
        if(d[c] <= dist && d[c] != -1) {
            int shovels = min(r-sum_r,stores[i].k);
            sum_r += shovels;
            sum_p += shovels*stores[i].p;
            if(sum_r == r && sum_p <= a) return true;
        }
    }
    return sum_r == r && sum_p <= a;
}

ll search(ll p, ll a) {
    if(!check(N+1,p,a)) return -1;
    int l = 0; int r = N+1;
    while(l < r) {
        int m = (l+r)/2;
        if(check(m,p,a)) r = m;
        else l = m+1;
    }
    return l;
}

int main() {
  
    int n,m; cin >> n >> m;
    g.assign(n, vector<int>());
    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    int w; cin >> w;
    for(int i = 0; i < w; ++i) {
        int c; store st; cin >> st.c >> st.k >> st.p;
        st.c--;
        stores.push_back(st);
    }
    sort(stores.begin(),stores.end(),[&](const store& s1, const store& s2) {
        return s1.p < s2.p;
    });
    
    int q; cin >> q;
    for(int i = 0; i < q; ++i) {
        int c; ll r, a; cin >> c >> r >> a;
        c--;
        bfs(c);
        ll min_dist = search(r,a);
        cout << min_dist << endl;
    }
    
    return 0;
}
