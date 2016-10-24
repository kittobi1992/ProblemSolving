#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ii;

int main() {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        
        if(n == 1) { cout << "! 1 1" << endl << flush; continue; }
        
        vector<ii> minmax; 
        for(int i = 0; i+1 < n; i += 2) {
            int a = i+1, b = i+2;
            cout << "? "<< a << " " << b << endl << flush;
            char comp; cin >> comp;
            if(comp == '>') minmax.push_back(make_pair(b,a));
            else minmax.push_back(make_pair(a,b));
        }
        if(n % 2 == 1) minmax.push_back(make_pair(n,n));
        
        while(minmax.size() > 1) {
            vector<ii> minmax2;
            for(int i = 0; i+1 < minmax.size(); i += 2) {
                int i1 = minmax[i].first, i2 = minmax[i].second;
                int j1 = minmax[i+1].first, j2 = minmax[i+1].second;
                int i_min = i1;
                cout << "? "<< i1 << " " << j1 << endl << flush ;
                char comp; cin >> comp;
                if(comp == '>') i_min = j1;
                
                int i_max = i2;
                cout << "? "<< i2 << " " << j2  << endl << flush ;
                cin >> comp;
                if(comp == '<') i_max = j2;
                
                minmax2.push_back(make_pair(i_min,i_max));
                
            }
            if(minmax.size() % 2 == 1) minmax2.push_back(minmax[minmax.size()-1]);
            minmax.clear(); minmax.resize(minmax2.size());
            for(int i = 0; i < minmax2.size(); ++i) minmax[i] = minmax2[i];
        }
        
        cout << "! " << minmax[0].first << " " << minmax[0].second <<  endl << flush ; 
        
    }
    
    return 0;
}
