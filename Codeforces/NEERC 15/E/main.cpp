#include <bits/stdc++.h>

using namespace std;


int main() {
    freopen("easy.in", "r",stdin);
    freopen("easy.out", "w",stdout);
    
    int n, k; cin >> n >> k;
    vector<vector<int>> p(n,vector<int>());
    for(int i = 0; i < n; ++i) {
        int pi; cin >> pi;
        p[i].resize(pi);
        for(int j = 0; j < pi; ++j) cin >> p[i][j];
        p[i].push_back(50);
    }
    
    vector<int> pos(n,0);
    int sum = 0, c = 0, cur = 0;
    while(c != k) {
        if(p[cur][pos[cur]] == 50) {
            c++; sum += p[cur][pos[cur]];
        } else if(p[cur][pos[cur]] >= sum) {
            c++; sum += p[cur][pos[cur]];
            pos[cur]++;
        } else {
            pos[cur]++;
        }
        cur = (cur+1) % n;
    }
    
    cout << sum << endl;
    
    return 0;
}
