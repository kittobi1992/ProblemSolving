#include <bits/stdc++.h>

using namespace std;

using ll = unsigned long long;

ll N; 
ll res[100];

int solve(ll n) {
    if(n == 0) return 0;  
    
    if(n % 2 == 0) {
        int len = solve(n/2);
        for(int i = 0; i < len; ++i) res[i] *= 2;
        return len;
    }
    
    ll three = 1;
    while(n / 3 >= three)  three *= 3;
    int len = solve(n-three);
    res[len++] = three;
    return len;
    
}

int main() {
  
    freopen("distribution.in", "r",stdin);
    freopen("distribution.out", "w",stdout);
    
    int T; cin >> T;
    while(T--) {
        cin >> N;
        for(int i = 0; i < 100; ++i) res[i] = 0;
        int len = solve(N);
        cout << len << endl;
        for(int i = 0; i < len; ++i) cout << res[i] << (i == len-1 ? "\n" : " ");
    }
    
	return 0;
}
