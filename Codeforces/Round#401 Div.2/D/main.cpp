#include <bits/stdc++.h>

using namespace std;

int N;
vector<string> s;

int main() {
    ios::sync_with_stdio(false);
    
    cin >> N;
    s.resize(N);
    for(int i = 0; i < N; ++i) cin >> s[i];
    
    for(int i = N-2; i >= 0; --i) {
        int j = 1;
        bool smaller = false;
        for(; j < min(s[i].size(),s[i+1].size()); ++j) {
            if(s[i][j] > s[i+1][j]) break;
            else if(s[i][j] < s[i+1][j]) {
                smaller = true; break;
            }
        }
        if(smaller) continue;
        s[i].erase(j);
    }
    
    for(int i = 0; i < N; ++i)
        cout << s[i] << endl;
    
	return 0;
}
