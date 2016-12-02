#include <bits/stdc++.h>

using namespace std;

int N, c1, c2, c3;
int b[102], prefix[103];
bool dp[301][301][301];

bool check(int i, int j, int k, int cur_len) {
    if(i < 0 || j < 0 || k < 0) return false;
    else if(!dp[i][j][k]) return false;
    auto it_b = lower_bound(prefix,prefix+N+1,cur_len);
    if(it_b == prefix+N+1) return false;
    else if(it_b == prefix + N) return true;
    else if(*it_b == cur_len) return false;
    else return true;
}

int main() {
    
    cin >> N >> c1 >> c2 >> c3;
    for(int i = 0; i < N; ++i) {
        cin >> b[i];
        prefix[i+1] = prefix[i] + b[i];
    }
    
    for(int i = 0; i <= c1; ++i) 
        for(int j = 0; j <= c2; ++j) 
            for(int k = 0; k <= c3; ++k)
                dp[i][j][k] = false;
            
    dp[0][0][0] = true;
    for(int i = 0; i <= c1; ++i) {
        for(int j = 0; j <= c2; ++j) {
            for(int k = 0; k <= c3; ++k) {
                int cur_len = i + 2*j + 3*k;
                if(check(i-1,j,k,cur_len)) dp[i][j][k] = true;
                else if(check(i,j-1,k,cur_len)) dp[i][j][k] = true;
                else if(check(i,j,k-1,cur_len)) dp[i][j][k] = true;
                if(dp[i][j][k] && cur_len == prefix[N]) {
                    cout << "YES" << endl;
                    return 0;
                }
            }
        }
    }
    
    cout << "NO" << endl;
                
    
	return 0;
}
