#include <bits/stdc++.h>

using namespace std;

struct app  {
    int d,s,i;
};

int n, c;
vector<app> a;
int dp[10005][505];
bool used[10005][505];

int solve(int free, int i) {
    if(i >= n) return 0;
    if(dp[free][i] >= 0) return dp[free][i];
    int best = solve(free, i+1);
    if(free >= max(a[i].d,a[i].s)) {
        int installed = 1 + solve(free - a[i].s, i+1);
        if(installed > best) {
            best = installed;
            used[free][i] = true;
        }
    }
    dp[free][i] = best;
    return dp[free][i];
}

int main() {

    cin >> n >> c;
    a.assign(n,{0,0,0});
    for(int i = 0; i < n; ++i) {
        cin >> a[i].d >> a[i].s;
        a[i].i = i + 1;
    }

    sort(a.begin(), a.end(), [&](const app& a1, const app& a2) {
        return a1.s - a1.d < a2.s - a2.d;
    });

    for(int i = 0; i <= c; ++i)
        for(int j = 0; j <= n; ++j) dp[i][j] = -1;

    cout << solve(c,0) << endl;
    int i = 0, f = c;
    while(i < n) {
        if(used[f][i]) {
            cout << a[i].i << " ";
            f -= a[i].s;
        }
        ++i;
    }
    cout << endl;

    return 0;
}