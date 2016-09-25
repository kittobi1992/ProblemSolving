#include <bits/stdc++.h>

using namespace std;

#define MAXN 105
using ll = long long;
using pll = pair<ll,ll>;

ll m[MAXN][MAXN];
ll N, M, K; 
ll tmp[MAXN];

void print(ll *a) {
    for(int i = 0; i <= N; ++i) cout << a[i] << " ";
    cout << endl;
}

pll sliding_window(ll L) {
    ll min_cost = INT_MAX, max_area = 0;
    ll cur_cost = 0, cur_area = 0;
    int i = 0, j = 0;
    while(j != N) {
        cur_cost += tmp[j++];
        cur_area += L;
        while(cur_cost > K && i < j) { cur_cost -= tmp[i++]; cur_area -= L; }
        if(cur_area > 0) {
            if(cur_area > max_area || (cur_area == max_area && cur_cost < min_cost)) {
                max_area = cur_area;
                min_cost = cur_cost;
            }
        }
    }
    return make_pair(min_cost,max_area);
}

int main() {
  
    int test; cin >> test;
    int t = 1;
    while(test--) {
        cin >> N >> M >> K;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < M; ++j) cin >> m[i][j];
        
        /*if(t == 63) {
            cout << N << " " << M << " " << K << endl;
            for(int i = 0; i < N; ++i) {
                for(int j = 0; j < M; ++j) cout << m[i][j] << " ";   
                cout << endl;
            }
        }*/
            
        pll ans = make_pair(INT_MAX,0);
        for(ll i = 0; i < M; ++i) {
            for(ll k = 0; k < N; ++k) tmp[k] = 0;
            for(ll j = i; j < M; ++j) {
                for(ll k = 0; k < N; ++k) tmp[k] += m[k][j];
                auto res = sliding_window(j-i+1);
                if(res.second > ans.second || (res.second == ans.second && res.first < ans.first)) ans = res;
            }
        }
        
        if(ans.first == INT_MAX) ans.first = 0;
        cout << "Case #" << t++ << ": " << ans.second << " " << ans.first << endl;
        
    }
    
	return 0;
}
