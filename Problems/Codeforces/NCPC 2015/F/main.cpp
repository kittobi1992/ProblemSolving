#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

#define fst first
#define snd second


int main() {
//     freopen("f.in", "r",stdin);
//     freopen("f.out", "w",stdout);
    
        ll f;
        cin >> f;
        
        ll poss = 1;
        for(int i = 0; i < f; i++){
            ll t, n;
            cin >> t >> n;
            
            vi prev(t+1, 1);
            vi next(t+1, 0);
            
            vii seg(n);
            for(int j = 0; j < n; j++) cin >> seg[j].fst >> seg[j].snd;
            
     
            //cout << seg.size() << endl;
            
            for(int j = seg.size()-1; j >= 0; j--){
                for(int x = 0; x <= t; x++){
                        ll d = seg[j].snd-seg[j].fst;
                        ll dx = x-d;
                        
                        if(dx >= 0){
                            next[x] |= prev[dx];
                        }
                        
                        dx = x+d;
                        
                        if(dx <= t){
                            next[x] |= prev[dx];
                        }
                        //cout << i << " " << j << " " << x << " " << next[x] << endl;
                }
                prev = next;
                next = vi(t+1, 0);
            }
            
            ll tpos = 0;
            for(int j = 0; j <= t; j++){
                if(prev[j]) {
                    tpos = 1;
                    break;
                }
            }
            
            poss = poss && tpos;
        }
        
        if(poss) cout << "possible" << endl;
        else cout << "impossible" << endl;
    
	return 0;
}
