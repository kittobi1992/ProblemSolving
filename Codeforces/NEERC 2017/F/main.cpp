#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ifstream fin("folding.in");
ofstream fout("folding.out");

ll tryF(ll W, ll H, ll w, ll h){
    if(w > W || h > H) return -1;
    
    ll f = 0;
    while(W != w){
        W = max(w, (W+1)/2);
        f++;        
    }

    while(H != h){
        H = max(h, (H+1)/2);
        f++;        
    }
 
    return f;
}


int main() {
  
        ll W, H;
        ll w, h;
        
        fin >> W >> H;
        fin >> w >> h;
        
        ll mini = tryF(W, H, w, h);
        ll mini2 = tryF(H, W, w, h);

        if(mini2 != -1 && mini != -1){
            mini = min(mini, mini2);
        } else if(mini2 != -1){
            mini = mini2;
        }
        
        fout << mini << endl;
        
	return 0;
}
