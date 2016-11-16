#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

typedef pair<int,int> ii;


int main() {
    
    int N, K; cin >> N >> K;
    vector<ii> s(N,make_pair(0,0));
    for(int i = 0; i < N; ++i) cin >> s[i].x >> s[i].y;
    sort(s.begin(),s.end(),[&](const ii& i1, const ii& i2) {
        return i1.y < i2.y || (i1.y == i2.y && i1.x < i2.x);
    });
    
    multiset<int> q; int num = 0;
    for(int i = 0; i < K; ++i) q.insert(0);
    for(int i = 0; i < N; ++i) {
        ii cur = s[i];
        if(q.size() == K) {
            auto it = q.upper_bound(cur.x);
            
            if(it == q.begin()) {
                continue;
            }
            int ys = *(--it);
            if(ys <= cur.x) {
                num++; q.erase(it); q.insert(cur.y);
            }
        }
    }
    
    cout << num << endl;
    
    return 0;
}
