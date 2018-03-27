#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll calc_min(vector<ll> a, ll s, ll e) {
    for(ll i = 0; i < s; ++i) a[i]++;
    for(ll i = e; i < a.size(); ++i) a[i]++;
    ll max_val = max(a[0],max(a[1],a[2]));
    return (max_val-a[0])+(max_val-a[1])+(max_val-a[2]);
}

int main() {

    ll b, d, s; cin >> b >> d >> s;
    ll max_val = max(b,max(d,s));
    if(max_val <= 1) {
        cout << "0" << endl;
        return 0;
    }
    
    ll min_val = LLONG_MAX;
    vector<ll> a = {b,d,s};
    for(ll i = 0; i <= 3; ++i) {
        for(ll j = 0; j <= 3; ++j) {
            min_val = min(min_val,calc_min(a,i,j));
        }
    }
    
    cout << min_val << endl;
    
	return 0;
}
