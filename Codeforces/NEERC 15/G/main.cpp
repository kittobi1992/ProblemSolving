#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,int> ii;
typedef pair<ll,pair<int,int>> iii;
typedef priority_queue<iii,vector<iii>,greater<iii>> PQ;

struct lcg {
  ll x, a, b, c;  
};

int main() {
//     freopen("f.in", "r",stdin);
//     freopen("f.out", "w",stdout);
    
    ll n, k; cin >> n >> k;
    vector<lcg> l;
    for(int i = 0; i < n; ++i) {
        lcg lc;
        cin >> lc.x >> lc.a >> lc.b >> lc.c;
        l.push_back(lc);
    }
    
    PQ pq;
    vector<ll> t(n);
    vector<int> vis(1002, 0);
    vector<vector<ii>> generators(n);
    ll sum = 0;
    for(int i = 1; i <= n; ++i) {
        ll x = l[i-1].x, a = l[i-1].a, b = l[i-1].b, c = l[i-1].c;
        vis[x] = i;
        vector<ii> gen;
        ll ti = 0;
        gen.push_back(make_pair(x,ti));
        while(true) {
            x = (a*x + b) % c;
            if(vis[x] == i) break;
            vis[x] = i;
            ti++;
            gen.push_back(make_pair(x,ti));
        }
        sort(gen.begin(),gen.end());
        int N = gen.size();
        if(N > 1) {
            pq.push(make_pair(gen[N-1].first-gen[N-2].first,make_pair(gen[N-2].second,i-1)));   
        }  
        generators.push_back(gen);
        ii max_val = gen[N-1];
        sum += max_val.first;
        t[i-1] = max_val.second;
    }
    
    while(!pq.empty() && sum % k == 0) {
        ll diff = pq.top().first;
        int ti = pq.top().second.first, i = pq.top().second.second;
//         cout << diff << " " << ti << " " << i << " " << t[i] << endl;
        pq.pop();
        if((sum - diff) % k != 0) {
            sum -= diff;
            t[i] = ti;
        }
        generators[i].pop_back();
        int N = generators[i].size();
        if(N > 1) {
            pq.push(make_pair(generators[i][N-1].first-generators[i][N-2].first,make_pair(generators[i][N-2].second,i)));   
        } 
    }
    
    if(sum % k == 0) {
        cout << "-1" << endl;
    }
    else {
        cout << sum << endl;
        for(int i = 0; i < n; ++i) cout << t[i] << (i == n-1 ? "\n" : " ");
    }
    
    return 0;
}
