#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

ll score(ll a, ll b, ll c) {
    return a*a + b*b + c*c + 7*min(a,min(b,c));
}

ll calc_max(ll a, ll b, ll c, ll d) {
    return max(score(a+d,b,c), max(score(a,b+d,c),score(a,b,c+d)));
}

int main() {
    int n; cin >> n;
    for(int i = 0; i < n; ++i) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        ll ans = calc_max(a,b,c,d);
        if(a == 0 && d >= 1) {
            a++; d--;
            ans = max(ans, calc_max(a,b,c,d));
        }
        if(b == 0 && d >= 1) {
            b++; d--;
            ans = max(ans, calc_max(a,b,c,d));
        }
        if(c == 0 && d >= 1) {
            c++; d--;
            ans = max(ans, calc_max(a,b,c,d));
        }
        cout << ans << endl;
    }
}