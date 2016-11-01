#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ii;

int main() {
  
    int N; cin >> N;
    int L = 0, R = 0;
    vector<ii> m(N,make_pair(0,0));
    for(int i = 0; i < N; ++i) {
        cin >> m[i].first >> m[i].second;
        L += m[i].first; R += m[i].second;
    }
    
    int idx = 0;
    int b = abs(L-R);
    for(int i = 0; i < N; ++i) {
        L -= m[i].first; R -= m[i].second;
        L += m[i].second; R += m[i].first;
        
        int cur_b = abs(L-R);
        if(cur_b > b) {
            b = cur_b;
            idx = i+1;
        }
        
        L -= m[i].second; R -= m[i].first;
        L += m[i].first; R += m[i].second;
    }
    
    cout << idx << endl;
    
    
	return 0;
}
