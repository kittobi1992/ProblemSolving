#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;


ll n;
void print(vi & x){
    
}

int main() {
//     freopen("f.in", "r",stdin);
//     freopen("f.out", "w",stdout);
    
    
    
    cin >> n;
    
    vi x(n);
    for(int i = 0; i < n; i++) x[i] = i;
    
    vi al(n);
     for(int i = 0; i < n; i++) al[i] = i;
     
    while(true){
    
        for(int i = 0; i < n; i++){
            if(i > 0) cout << " ";
            cout << al[i]+1;
        }
        cout << endl;
    
        vi y(n, -1);
        
        ll mov = -1;
        for(int i = 0; i < n; i++){
            ll par = 0;
            for(int j = 0; j < i; j++){
                for(int k = j + 1; k < i; k++)
                {
                    if(x[k] < x[j]) par++;
                }
            }
            
            if(par % 2 == 0) y[i] = x[i]-1;
            else y[i] = x[i]+1;
            
            if(y[i] >= 0 && y[i] < n && al[y[i]] < i){
                mov = i;
            }
            
            
        }
        
        if(mov == -1) break;
        
        //cout << mov << " " << x[mov] << " " << x[al[y[mov]]] << endl;
        
        ll p = x[mov];
        ll np = y[mov];
        swap(x[mov], x[al[np]]);
        swap(al[p], al[np]);
        
        //cout << mov << " " << al[x[mov]] << " " << al[y[mov]] << endl;
    }
        
	return 0;
}
