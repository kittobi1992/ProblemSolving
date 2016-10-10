#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAXN 5002


struct Edge {
    int u;
    int v;
    ll w;
};

using graph = vector<Edge>;
using il = pair<int,ll>;

graph g;
ll N,M,T;
vector<int> res;
int ans = 0;

int dp[MAXN][MAXN];
int parent[MAXN][MAXN];

void bellman_ford() {
    
    dp[0][0] = 0;
    
    for(int i = 0; i < N; ++i) {
        for(Edge e : g) {
            int u = e.u, v = e.v;
            ll t = e.w;
            
            if(dp[i+1][v] >= dp[i][u] + t) {
                dp[i+1][v] = dp[i][u]+t;
                parent[i+1][v] = u;
            }
        }
        if(dp[i+1][N-1] <= T) ans = i+1;
    }
    
}


int main() {
    
    cin >> N >> M >> T;
    g = vector<Edge>();
    res = vector<int>();
    
    for(int i = 0; i < M; ++i) {
        Edge e;
        cin >> e.u >> e.v >> e.w;
        e.u--; e.v--;
        g.push_back(e);
    }
    
    for(int i = 0; i <= N; ++i) {
        for(int j = 0; j < N; ++j) dp[i][j] = T + 1;
    }

    bellman_ford();
   
    int cur = N-1; int level = ans;
    while(cur != parent[ans][cur]) {
        res.push_back(cur);
        cur = parent[level--][cur];
    }
    res.push_back(0);
    reverse(res.begin(),res.end());
    
    cout << ans+1 << endl;
    for(int i = 0; i < res.size(); ++i) {
        cout << (res[i]+1) << (i == res.size()-1 ? "\n" : " ");
    }
    
	return 0;
}
