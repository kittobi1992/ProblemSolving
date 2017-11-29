#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-8

int n;
vector<double> r;
double dp[15][4100];

double p(int k, int i) {
    if(k == 1) {
        if(i % 2 == 0) return r[i]/(r[i] + r[i+1]);
        else return r[i]/(r[i] + r[i-1]);
    }
    if(dp[k][i] >= EPS) return dp[k][i];
    double prob = 0.0;
    int cnt = i/pow(2,k-1);
    int s = (cnt % 2 ? pow(2,k-1)*(cnt-1) : pow(2,k-1)*(cnt+1));
    for(int j = s; j < s + pow(2,k-1); ++j) {
        if(r[j] == 0) continue;
        prob += p(k-1,j)*(r[i]/(r[i] + r[j]));
    }
    dp[k][i] = p(k-1,i)*prob;
    return dp[k][i];
}

int main() {

    int tmp_n;
    cin >> tmp_n;
    vector<double> tmp_r(tmp_n,0.0);
    cin >> tmp_r[0];
    for(int i = 1; i < tmp_n; ++i) cin >> tmp_r[i];
    sort(tmp_r.begin()+1,tmp_r.end());

    int k = ceil(log2(tmp_n));
    n = pow(2,k);
    r.assign(n,0.0);
    int i = 0, j = 0;
    while(i < n) {
        r[i] = tmp_r[j];
        if(tmp_n < n) {
            ++tmp_n; ++i;
        }
        ++j; ++i;
    }

    cout << fixed << setprecision(10) << p(k,0) << endl;
    

    return 0;
}