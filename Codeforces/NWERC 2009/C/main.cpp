#include <bits/stdc++.h>

using namespace std;

#define MAXN 50001

typedef long long ll;

ll d;
int n;
ll seq[MAXN];

int main() {
    
    int test; cin >> test;
    for(int t = 0; t < test; ++t) {
        cin >> d >> n;
        vector<ll> partial_sum(d,0);
        ll sum = 0;
        for(int i = 0; i < n; ++i) {
            cin >> seq[i];
            sum += seq[i];
            partial_sum[sum%d]++;
        }
        
        ll res = partial_sum[0];
        for(ll i = 0; i < d; ++i) {
            res += (partial_sum[i]*(partial_sum[i]-1))/2;
        }
        
        cout << res << endl;
        
    }
    
    return 0;
}
