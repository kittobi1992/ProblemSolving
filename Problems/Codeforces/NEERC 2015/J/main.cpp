#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll,int>;

ll N, T;
ll p[50005], d[50005];
ll t[50005];

using PQ = priority_queue<pll,vector<pll>,greater<pll>>;

bool check(int r) {
    PQ pq;
    t[1] = 0; pq.push(make_pair(t[1],1));
    ll min_t = LLONG_MAX;
    for(int i = 2; i < N; ++i) {
        while(pq.top().second < i-r) pq.pop();
        t[i] = d[i] + pq.top().first;
        pq.push(make_pair(t[i],i));
        if(i+r >= N) min_t = min(min_t,t[i]+N-1);
    }
    return min_t <= T;
}

int main() {
    freopen("journey.in", "r",stdin);
    freopen("journey.out", "w",stdout);
    
    cin >> N >> T;
    for(int i = 1; i <= N-1; ++i) cin >> p[i];
    for(int i = 2; i <= N-1; ++i) cin >> d[i];
    
    int l = 1, r = N-1;
    while(r-l > 0) {
        int m = (l+r)/2;
        if(check(m)) r = m;
        else l = m+1;
    }
    
    ll min_price = LLONG_MAX;
    for(int i = l; i < N; ++i) min_price = min(min_price,p[i]);
    
    cout << min_price << endl;
    
	return 0;
}
