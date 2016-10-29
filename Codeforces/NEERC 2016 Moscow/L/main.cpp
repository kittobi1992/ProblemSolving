#include <bits/stdc++.h>

using namespace std;

#define INF INT_MAX

int main() {
    ios::sync_with_stdio(false);

    int N; cin >> N;
    vector<int> t(2*N), num_sub(2*N,0);
    vector<bool> is_plus(2*N,false);
    int cur_num_sub = 0;
    for(int i = 0; i < 2*N; ++i) {
        char c; cin >> c >> t[i];
        num_sub[i] = cur_num_sub;
        if(c == '+') {
            is_plus[i] = true; 
            cur_num_sub++;
        }
        else {
            is_plus[i] = false;
            cur_num_sub--;
        }
    }
    
    vector<double> p(2*N,0.0);
    for(int i = 2*N-2; i >= 0; --i) {
        if(is_plus[i]) {
            p[i] = p[i+1] + (t[i+1] - t[i]);
        }
        else {
            p[i] = (p[i+1] + (t[i+1] - t[i]))*(((double)num_sub[i] - 1.0)/((double)num_sub[i]));
        }
    }
    
    
    for(int i = 0; i < 2*N; ++i) {
        if(is_plus[i] > 0) cout << fixed << setprecision(10) << p[i] << endl;
    }
    
    return 0;
}
