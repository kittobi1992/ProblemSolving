#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void solve() {
    int k,m,n, s = 0; cin >> k >> m >> n;
    vector<int> apps = vector<int>(n);
    
    for(int i = 0; i < n; i++) {
        cin >> apps[i];
        s += apps[i];
    }
    
    sort(apps.begin(), apps.end());
    
    int cc = 0;
    while(s + m > k && cc < n) {
            cc++;
            s -= apps[n - cc];
    }
    
    cout << cc << "\n";
}


int main() {
    
    int N; cin >> N;
    
    while(N--) {
            solve();
    }
    
    return 0;
}
