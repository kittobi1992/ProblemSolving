#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back

int main() {
    
    
        ll n;
        cin >> n;
        vector<ll> al(n);
        for(int i = 0; i < n; i++) cin >> al[i];
        for(int i = 0; i < n; i++) al.pb(al[i]);
        
    
        ll id = -1;
        for(int i = 1; i < 2*n-1; i++){
            if(al[i-1] < al[i] && al[i+1] < al[i]) id = i % n;
        }
        
        ll prev = id-1;
        if(prev < 0) prev += n;
        
        ll next = (id+1) % n;
    
        cout << prev+1 << " " << id+1 << " " << next+1 << endl;
        
	return 0;
}
