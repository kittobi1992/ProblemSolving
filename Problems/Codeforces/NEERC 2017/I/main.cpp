#include <bits/stdc++.h>

using namespace std;

ifstream fin("integral.in");
ofstream fout("integral.out");

using ll = long long;

ll x[200005], y[200005], f[200005];
ll n;

ll cross(int i) {
    int a = (i+n-1)%n, b = i;
    return x[a]*y[b]-y[a]*x[b];
}

int main()
{
    fin >> n;
    for(int i = 0; i < n; ++i) fin >> x[i] >> y[i];
    x[n] = x[0]; y[n] = y[0];
    
    ll A = 0;
    ll g[2][2][2];
    for(int xr = 0; xr < 2; ++xr)
        for(int yr = 0; yr < 2; ++yr)
            for(int fr = 0; fr < 2; ++fr)
                g[xr][yr][fr] = 0;
    
    for(int i = 0; i < n; ++i) {
        f[i] = ((i == 0 ? 0 : f[i-1]) + cross(i))&1;
        g[x[i]&1][y[i]&1][f[i]&1]++;
        A += cross(i);
    }
    
    if(A & 1) {
        fout << 0 << endl;
        return 0;
    }
    
    ll ans = 0;
    for(int i = 0; i < n; ++i) {
        g[x[i]&1][y[i]&1][f[i]&1]--;
        for(int xr = 0; xr < 2; ++xr) {
            for(int yr = 0; yr < 2; ++yr) {
                for(int fr = 0; fr < 2; ++fr) {
                    if(((x[i]*yr + y[i]*xr + fr + f[i])&1) == 0) {
                        ans += g[xr][yr][fr];
                    }
                }
            }
        }
    }
    
    fout << ans-n << endl;
    
    return 0;
}
