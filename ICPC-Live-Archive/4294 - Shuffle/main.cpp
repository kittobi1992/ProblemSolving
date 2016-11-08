#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ii;

int main() {

    int T; cin >> T;
    while(T--) {
        int s, n; cin >> s >> n;
        vector<int> x(n); 
        for(int i = 0; i < n; ++i) cin >> x[i];
        
        set<int> pos;
        for(int i = 0; i < s; ++i) pos.insert(i);
        
        vector<int> cnt(s+1,0);
        int c = 0;
        int l = 0, r = 0;
        while(r < n) {
            if(cnt[x[r]] == 0) c++;
            cnt[x[r++]]++; 
            
            if(r-l == s) {
                if(cnt[x[r-1]] > 2) { pos.clear(); break; }
                if(s != c) { pos.erase(l % s); }
                cnt[x[l]]--;
                if(cnt[x[l++]] == 0) c--;
            }
        }
        
        if(pos.size() > 0) {
            cnt.assign(s+1,0);
            vector<int> cnt2(s+1,0);
            int c2 = 0;
            l = 0; r = 0;
            while(r < n) {
                cnt[x[r]]++;
                if(cnt[x[r]] == 2) {
                    while(cnt[x[r]] == 2) cnt[x[l++]]--;
                    c2++;
                    for(int i = l; i <= r; ++i) cnt2[i%s]++;
                }
                r++;
            }
            for(int i = 0; i < s; ++i) {
                if(cnt2[i] != c2) pos.erase(i);
            }
        }
        
        cout << pos.size() << endl;
        
        
    }
    
	return 0;
}
