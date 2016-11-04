#include <bits/stdc++.h>

using namespace std;


int main() {
    freopen("hash.in", "r",stdin);
    freopen("hash.out", "w",stdout);
            
    int N; cin >> N;
    string cur(N,'c');
    
    vector<string> hash; hash.push_back(cur);
    cur[0]++;
    for(int i = 1; i < N; ++i) {
        cur[i] -= 31;
        hash.push_back(cur);
        cur[i-1]--;
        cur[i] += 32;
    }
    
    for(int i = 0; i < N; ++i) cout << hash[i] << endl;
    
    return 0;
}
