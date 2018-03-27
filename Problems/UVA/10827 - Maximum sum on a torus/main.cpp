#include <bits/stdc++.h>

using namespace std;

using matrix = vector<vector<int>>;
#define MAXN 101

int N;
int dp[MAXN][MAXN];
int tmp[MAXN], dp_1D[MAXN];



void shift() {
    int tmp_v = tmp[0];
    for(int i = 0; i < N-1; ++i) tmp[i] = tmp[i+1];
    tmp[N-1] = tmp_v;
}


int kadane_algorithm() {
    int res = INT_MIN;
    for(int i = 0; i < N; ++i) {
        dp_1D[0] = tmp[0]; res = max(res,tmp[0]);
        for(int i = 1; i < N; ++i) {
          dp_1D[i] = max(dp_1D[i-1] + tmp[i], tmp[i]);
          res = max(dp_1D[i],res);
        }
        shift();
    }
    return res;
}

int main() {
    int test; cin >> test;
    while(test--) {
        cin >> N;
        matrix m(N,vector<int>(N,0));
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                cin >> m[i][j];
    
        int res = INT_MIN;
        for(int i = 0; i < N; ++i) {
            for(int k = 0; k < N; ++k) tmp[k] = 0;
            for(int j = 0; j < N; ++j) {
                for(int k = 0; k < N; ++k) tmp[k] += m[k][(i+j) % N];
                res = max(kadane_algorithm(),res);
            }
        }
    
        cout << res << endl;
    }
   
    
	return 0;
}
