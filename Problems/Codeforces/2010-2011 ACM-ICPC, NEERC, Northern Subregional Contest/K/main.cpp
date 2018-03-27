#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
using point = pair<double,double>;

double w,l;
int n;
point r;

ifstream fin("kitchen.in");
ofstream fout("kitchen.out");

double distance(point p1, point p2) {
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

double distance2(point p1, point p2) {
    point a1{-p2.x,p2.y}, a2 {p2.x,-p2.y}, a3 {p2.x + 2*(w-p2.x),p2.y}, a4 {p2.x,p2.y+2*(l-p2.y)};
    return min(distance(p1,a1),min(distance(p1,a2),min(distance(p1,a3),distance(p1,a4))));
}

inline bool isBitSet(int a, int i) {
    return (a >> i) & 1;
}

inline int unsetBit(int a, int i) {
    return a & ~(1 << i);
}

vector<vector<double>> dist;
vector<point> b;

int main() {
    

    
    fin >> w >> l >> n;
    dist.assign(n,vector<double>(n,0.0));
    b.assign(n,{0.0,0.0});
    for(int i = 0; i < n; ++i) fin >> b[i].x >> b[i].y;
    fin >> r.x >> r.y;
    
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) dist[i][j] = distance2(b[i],b[j]);
    }
    
    vector<vector<double>> dp((1 << n),vector<double>(n,DBL_MAX/2.0));
    for(int i = 1; i < (1 << n); ++i) {
        for(int j = 0; j < n; ++j) {
            if(isBitSet(i,j)) {
                int c = unsetBit(i,j);
                if(c == 0) dp[i][j] = distance(r,b[j]);
                else {
                   for(int k = 0; k < n; ++k)
                        dp[i][j] = min(dp[i][j], dp[c][k]+dist[k][j]);
                }
            }
        }
    }
    
    double res = DBL_MAX;
    int k = (1 << n) - 1;
    for(int i = 0; i < n; ++i) {
        double dis = min(b[i].x, min(b[i].y, min(w-b[i].x, l-b[i].y)));
        res = min(res,dp[k][i]+dis);
    }
    
    fout << fixed << setprecision(16) << res << endl;
  
  return 0;
}
