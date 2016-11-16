#include <bits/stdc++.h>

using namespace std;


typedef long long ll;
typedef vector<ll> vi;
priority_queue<int, vector<int>, greater<int> > PQ;

map<ll, map<ll, ll> > gl;

int main() {
   ll g;
   cin >> g;
   
   for(int i = 0; i < g; i++){
        ll x, y;
        cin >> x >> y;
        gl[x][y]++;
   }
       
    ll m;
    cin >> m;

    ll sum = 0;
    for(int i = 0; i < m; i++){
        ll x, y, r;
        cin >> x >> y >> r;
        
        
        
        for(int cx = x-r; cx <= x+r; cx++){
            for(int cy = y-r; cy <= y+r; cy++){
                ll dx = abs(cx-x);
                ll dy = abs(cy-y);
                if(dx*dx+dy*dy > r*r) continue;
                
                if(gl.find(cx) != gl.end() && gl[cx].find(cy) != gl[cx].end()){
                        auto res = gl[cx][cy];
                        gl[cx].erase(cy);
                    
                        sum += res;
                }
            }
        }
        
        
        
        
    }
   
   cout << g-sum << endl;
    
    return 0;
}
