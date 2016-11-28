#include <bits/stdc++.h>

using namespace std;

#define EPSILON 1e-6
#define x real
#define y imag

typedef complex<double> pt;

int N,M;
vector<pt> polygon;


int pointInPolygon(pt a, pt b, pt c) { 
    if(y(a) == y(b) && y(b) == y(c)) {
        if((x(b) <= x(a) && x(a) <= x(c)) || (x(c) <= x(a) && x(a) <= x(b))) return 0;
        else return 1;
    }
    if(y(b) > y(c)) swap(b,c);
    if(y(a) == y(b) && x(a) == x(b)) return 0;
    if(y(a) <= y(b) || y(a) > y(c)) return 1;
    double delta = (x(b)-x(a))*(y(c)-y(a))-(y(b)-y(a))*(x(c)-x(a));
    if(delta > 0) return -1;
    else if(delta < 0) return 1;
    else return 0;
}

int main() {
    
    
    while(cin >> N) {
        if(N == 0) break;
        polygon.resize(N);
        for(int i = 0; i < N; ++i) {
            double x,y; cin >> x >> y;
            polygon[i] = pt(x,y);
        }
        
        cin >> M;
        for(int i = 0; i < M; ++i) {
            double x,y; cin >> x >> y;
            pt p(x,y);
            int t = -1;
            for(int j = 0; j < N; ++j) {
                t *= pointInPolygon(p,polygon[j],polygon[(j+1)%N]);
                if(t == 0) break;
            }
            if(t > 0) cout << "in" << endl;
            else if(t < 0) cout << "out" << endl;
            else cout << "on" << endl;
        }
        
    } 
    
 	return 0;
}
