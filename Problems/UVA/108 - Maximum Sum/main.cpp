#include <bits/stdc++.h>

using namespace std;

using matrix = vector<vector<int>>;
#define MAXN 101

int N;
int dp[MAXN][MAXN];
int tmp[MAXN], dp_1D[MAXN];

int kadane_algorithm() {
    dp_1D[0] = tmp[0]; int res = tmp[0];
    for(int i = 1; i < N; ++i) {
        dp_1D[i] = max(dp_1D[i-1] + tmp[i], tmp[i]);
        res = max(dp_1D[i],res);
    }
    return res;
}

int main() {
  
    cin >> N;
    matrix m(N,vector<int>(N,0));
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            cin >> m[i][j];
    
    int res = INT_MIN;
    for(int i = 0; i < N; ++i) {
        for(int k = 0; k < N; ++k) tmp[k] = 0;
        for(int j = i; j < N; ++j) {
            for(int k = 0; k < N; ++k) tmp[k] += m[k][j];
            res = max(kadane_algorithm(),res);
        }
    }
    
    cout << res << endl;
   
    
	return 0;
}
