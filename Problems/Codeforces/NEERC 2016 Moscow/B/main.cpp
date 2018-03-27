#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
      
        ll l, r, w;
        cin >> l >> r >> w;
        
        ll sw = w;

        ll d = sw;
        
        ll lo = l-w+1;
        ll hi = r-1;
        
        
        if(l < r+w && (w % r != 0 && (r % w != 0))){
            cout << "DEADLOCK" << endl;
                return 0;
        } else {
             cout << "OK" << endl;
             return 0;
            
        }
        
        if(hi < lo){
            cout << "OK" << endl;
            return 0;
        }
        
        
        while(d){
            //cout << d << " " <<  s << " " << e << endl;
            
            ll fac = max((r-d) / sw, 0LL);
            d += fac*sw;
            while(d < r) d += sw; 
            
            if(d > l) {
                cout << "DEADLOCK" << endl;
                return 0;
            }
            d %= r;
                
            //d = r % d;
        }
        
        cout << "OK" << endl;
    
	return 0;
}
