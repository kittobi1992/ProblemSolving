#include <bits/stdc++.h>

using namespace std;

#define MOD 21092013
#define N 1000003

using ll = long long;

ll nextL[N], nextR[N], nextU[N], dp[N];
string S, T;

int main() {
    
    int test; int t = 1; cin >> test; 
    while(test--) {
        cin >> S >> T;
        
        int sS = S.size(), tS = T.size();
        
        int j = 0;
        for(int i = 0; i < S.size(); ++i) {
            if(S[i] == 'U') { if(j) j--; } else S[j++] = S[i];
        }
        S.resize(j);
        sS = j;
        
        nextL[tS] = nextR[tS] = nextU[tS] = tS;
        for(int i = tS-1; i >= 0; --i) {
            nextL[i] = nextL[i+1];
            nextR[i] = nextR[i+1];
            nextU[i] = nextU[i+1];
            
            if(T[i] == 'L') nextL[i] = i;
            else if(T[i] == 'R') nextR[i] = i;
            else if(T[i] == 'U') nextU[i] = i;
        }
        
        dp[tS] = 0;
        for(int i = tS-1; i >= 0; i--) dp[i] = (1 + dp[nextL[i+1]] + dp[nextR[i+1]]) % MOD;
        
        ll res = (1 + dp[nextL[0]] + dp[nextR[0]]) % MOD;
        
        int idx = nextU[0];
        for(int i = 1; i <= sS; ++i) {
            if(idx == tS) break;
            
            if(S[sS-i] == 'L') res = (res + 1 + dp[nextR[idx]]) % MOD;
            else res = (res + 1 + dp[nextL[idx]]) % MOD;
            
            idx = nextU[idx+1];
        }
        
        cout << "Case " << t++ << ": " << res << endl;
    }
    
	return 0;
}
