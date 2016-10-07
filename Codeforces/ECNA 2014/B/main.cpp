#include <bits/stdc++.h>

using namespace std;

#define MAXN 505
int N;
string s;

int dp[MAXN][MAXN];

void clear() {
    for(int i = 0; i < MAXN; ++i) {
        for(int j = 0; j < MAXN; ++j) {
            dp[i][j] = 1;
        }
    }
}

void calcMaximumRepeatedSubsequence() {
    for(int l = 1; l < N; l++) {
        for(int i = 0; i+l < N; ++i) {
            int j = i + l;
            if((j-i+1) % 2 == 0) {
                int m = (i+j+1)/2;
                if(dp[i][m-1] == dp[m][j]) {
                    int L = (j-i+1)/ 2 /dp[i][m-1];
                    bool match = true;
                    for(int k = 0; k < L; ++k) {
                        if(s[i+k] != s[m+k]) {
                            match = false;
                            break;
                        }
                    }
                    if(match) dp[i][j] = dp[i][m-1]+dp[m][j];
                }
            }
            else {
                int m = (i+j+1)/2;
                for(int m = i; m < j; ++m) {
                    int l1 = (m-i+1), l2 = (j-(m+1)+1);
                    if(l1/dp[i][m] == l2/dp[m+1][j]) {
                        bool match = true;
                        for(int k = 0; k < l1; ++k) {
                            if(s[i+k] != s[m+1+k]) {
                                match = false;
                                break;
                            }
                        }
                        if(match) dp[i][j] = max(dp[i][j],dp[i][m]+dp[m+1][j]);
                    }
                }
            }
            //cout << "dp["<<i<<"]["<<j<<"] = " << dp[i][j] << endl;
        }
    }
}

int findEncodedStringLength(int i, int j, int u) {
    int ub = (u > 1 ? ceil(log10(static_cast<double>(u+1)))+2 : 0);
    if(j-i < 0) return 0;
    else if(j-i == 0) return ub > 0 ? ub-1 : 1;
    
    int max_l = 1, max_i = -1, max_j = -1;
    int n = (j-i+1);
    for(int l = n-1; l > 0; l--) {
        for(int a = i; a+l <= j; ++a) { 
            int b = a+l;
            if(dp[a][b] > 1 && (b-a+1) >= (max_j-max_i+1)) {
                max_l = dp[a][b];
                max_i = a;
                max_j = b;
                int sub_length = (b-a+1)/max_l;
                int old_max_j = max_j;
                for(int k = 1; max_j + sub_length <= j; k++) {
                    if(dp[max_i+k*sub_length][max_j+sub_length] > 1) {
                        max_j += sub_length;
                        max_l++;
                    }
                    else break;
                }
                for(int k = 1; max_i - sub_length >= j; k++) {
                    if(dp[max_i-sub_length][old_max_j-k*sub_length] > 1) {
                        max_i -= sub_length;
                        max_l++;
                    }
                    else break;
                }
            }
        }
    }
    
    
    if(max_i == -1) {
        max_i = i; max_j = j;
    }
    
    if(max_l == 1) {
        if(j-i+1 == 2 && u == 2) return 4;
        return (j-i+1)+ub;
    }
    //cout << i << " " << j << endl;
    //cout << max_i << " " << max_j << " " << max_l << endl;
    int new_i = max_i, new_j = max_i + (max_j-max_i)/max_l;
    if(max_i == i && max_j == j) {
        return findEncodedStringLength(new_i,new_j,u*max_l);
    }
    else {
        int left = findEncodedStringLength(i,max_i-1,1);
        int middle = findEncodedStringLength(new_i,new_j,max_l);
        int right = findEncodedStringLength(max_j+1,j,1);
        return ub + left + middle + right;
    }
    
}

int main() {

    int t = 1;
    while(cin >> s) {
        if(s == "0") break;
        N = s.size();
        clear();
        calcMaximumRepeatedSubsequence();
        
        int res = findEncodedStringLength(0,N-1,1);

        cout << "Case " << t++ << ": " << res << endl;
    }
	
    return 0;
}
