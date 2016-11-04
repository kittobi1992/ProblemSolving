#include <bits/stdc++.h>

using namespace std;

#define EPS 10e-6

double h,w;

bool check(double m) {
    if(m > w || m > h) return false;
    double x = 0.0, y = 0.0;
    for(int i = 0; i < 3; ++i) {
        x += m;
        if(x > w) { y += m; x = m; }
        if(y + m > h) { return false; }
    }
    return true;
}

int main() {
  freopen("alex.in", "r",stdin);
  freopen("alex.out", "w",stdout);

  cin >> h >> w;
  
  double l = 0.0, r = 1000.0;
  while(abs(r-l) > EPS) {
    double m = (l+r)/2.0;
    if(check(m)) l = m;
    else r = m;
  }
  
  cout << fixed << setprecision(5) << l << endl;
  
  
  return 0;
}
