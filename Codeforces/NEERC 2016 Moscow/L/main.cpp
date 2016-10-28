#include <bits/stdc++.h>

using namespace std;

#define INF INT_MAX

int main() {
    ios::sync_with_stdio(false);

    int N; cin >> N;
    vector<int> t(2*N), p_sub(2*N,0), p_ev(2*N,0);
    for(int i = 0; i < 2*N; ++i) {
        char c; int a; cin >> c >> a;
        t[i] = (c == '-' ? -a : a);
        if(i > 0) {
            p_sub[i] = p_sub[i-1] + (t[i] > 0);
            p_ev[i] = p_ev[i-1] + (t[i] < 0);
        }
        else {
            p_sub[0] = t[i] > 0;
            p_ev[0] = t[i] < 0;
        }
    }
    t.push_back(INF);
    
    vector<double> p0(2*N,1.0);
    vector<double> p(2*N,0.0);
    int l = 0, r = 1;
    double prob = 1.0;
    double p_sum = 0.0;
    double con_sum = 0.0;
    while(r <= 2*N) {
        if(t[r] > 0) {
            if(t[r-1] < 0) {
                for(int i = l; i < r; ++i) {
                    if(t[i] > 0) {
                        p[i] += p0[i]*con_sum-p0[i]*p_sum*static_cast<double>(t[i]);
                        p0[i] *= prob;
                    }
                }
                prob = 1.0;
                p_sum = 0.0;
                con_sum = 0.0;
            }
            if(p_ev[r-1]-p_sub[r-1] == 0) l = r;
            r++;
        }
        else {
            p_sum += prob*1.0/static_cast<double>(p_sub[r]-p_ev[r]+1);
            con_sum += prob*1.0/static_cast<double>(p_sub[r]-p_ev[r]+1)*abs(t[r]);
            prob = prob*(1.0-1.0/static_cast<double>(p_sub[r]-p_ev[r]+1));
            r++;
        }
    }
    
    for(int i = 0; i < 2*N; ++i) {
        if(t[i] > 0) cout << fixed << setprecision(10) << p[i] << endl;
    }
    
    return 0;
}
