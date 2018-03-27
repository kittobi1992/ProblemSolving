#include <bits/stdc++.h>

using namespace std;

#define INF INT_MAX
#define NMAX 200002

double p[NMAX];
bool is_plus[NMAX];
int t[NMAX];
int num_sub[NMAX];


int main() {

    int N; cin >> N;
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
    
    p[2*N-1] = 0.0;
    for(int i = 2*N-2; i >= 0; --i) {
        if(is_plus[i]) {
            p[i] = p[i+1] + (t[i+1] - t[i]);
        }
        else {
            p[i] = (p[i+1] + (t[i+1] - t[i]))*(((double)num_sub[i] - 1.0)/((double)num_sub[i]));
        }
    }
    
    cout << setprecision(10) << fixed;
    for(int i = 0; i < 2*N; ++i) {
        if(is_plus[i] > 0) cout << p[i] << endl;
    }
    
    return 0;
}
