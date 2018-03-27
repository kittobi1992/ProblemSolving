#include <bits/stdc++.h>

using namespace std;

int main() {

    int n;
    while(cin >> n) {
        if(n == 0) break;
        vector<int> a(n,0);
        for(int i = 0; i < n; ++i) cin >> a[i];
        
        int res = 0;
        vector<int> dp(n,0); dp[0] = a[0];
        for(int i = 1; i < n; ++i) {
            dp[i] = max(dp[i-1] + a[i], a[i]);
            res = max(dp[i],res);
        }
        
        if(res > 0) cout << "The maximum winning streak is " << res << "." << endl;
        else cout << "Losing streak." << endl;
        
    }
    
	return 0;
}
