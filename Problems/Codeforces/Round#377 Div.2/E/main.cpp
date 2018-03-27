#include <bits/stdc++.h>

using namespace std;


#define MAXN 200005
int p[MAXN], s[MAXN], a[MAXN], b[MAXN];
bool used1[MAXN], used2[MAXN];
bool isConnectedSocket[MAXN];
int N, M;

int main() {
  
    cin >> N >> M;
    for(int i = 0; i < N; ++i) cin >> p[i];
    for(int i = 0; i < M; ++i) cin >> s[i];
    p[N] = INT_MAX;
    vector<int> p_idx(N+1,0), s_idx(M,0);
    iota(p_idx.begin(),p_idx.end(),0);
    iota(s_idx.begin(),s_idx.end(),0);
    sort(p_idx.begin(),p_idx.end(),[&](const int i1, const int i2) {
        return p[i1] < p[i2];
    });
    sort(s_idx.begin(),s_idx.end(),[&](const int i1, const int i2) {
        return s[i1] < s[i2];
    });
    
    int c = 0, u = 0;
    int cur_adapter = 0;
    for(int k = 0; k < 32; ++k) {
        
        int j = 0;
        for(int i = 0; i < N; ++i) {
            if(used1[p_idx[i]]) continue;
            int cur_p = p[p_idx[i]];
            for(; j < M; ++j) {
                if(used2[s_idx[j]]) continue;
                int cur_s = s[s_idx[j]];
                if(cur_p < cur_s) break;
                else if(cur_p == cur_s) {
                    c++; u += a[s_idx[j]];
                    b[p_idx[i]] = s_idx[j]+1;
                    used1[p_idx[i]] = true;
                    used2[s_idx[j]] = true;
                    break;
                }
            }
        }
        
        for(int i = 0; i < M; ++i) {
            if(!used2[i]) {
                s[i] = (s[i] % 2) + s[i] / 2;
                a[i]++;
            }
        }
        
    }
    
    cout << c << " " << u << endl;
    for(int i = 0; i < M; ++i) cout << (used2[i] ? a[i] : 0) << (i == M-1 ? "\n" : " ");
    for(int i = 0; i < N; ++i) cout << b[i] << (i == N-1 ? "\n" : " ");
    
	return 0;
}
