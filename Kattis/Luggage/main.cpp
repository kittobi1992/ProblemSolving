#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-10

typedef pair<double,double> dd;

int main() {
    int N; double L;
    cin >> N >> L;
    vector<double> x(N,0.0);    
    for(int i = 0; i < N; ++i) cin >> x[i];
    sort(x.begin(),x.end());
    
    if(N == 1) {
        cout << "10" << endl;
        return 0;
    }
    
    vector<dd> ival;
    for(int i = 0; i < N; ++i) {
        for(int j = i+1; j < N; ++j) {
            double dx = std::abs(x[i]-x[j]);
            ival.push_back(dd(dx,100.0));
            for(int n = 1; dx/(n*L-1.0) >= 0.1; ++n) {
                ival.push_back(dd(dx/(n*L+1.0),dx/(n*L-1)));
            }   
        }
    }
    
    sort(ival.begin(),ival.end());
    double last_y = 0.0;
    double max_v = 0.0;
    for(int i = 0; i < ival.size(); ++i) {
        double x0 = ival[i].first, x1 = ival[i].second;
        if(x0 >= 10.0+EPS) break;
        if(x0 > last_y-EPS) max_v = x0;
        last_y = std::max(last_y,x1);
    }

    if(max_v >= 0.1-EPS) cout << fixed << setprecision(10) << max_v << endl;
    else cout << "no fika" << endl;
    
	return 0;
}
