

#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> point;

ifstream fin("defense.in");
ofstream fout("defense.out");

int main() {
  
    int w, h, n; fin >> w >> h >> n;
    vector<int> x(n+2,0), y(n+2,0);
    for(int i = 0; i < n; i++) fin >> x[i] >> y[i];
    x[n] = 0; y[n] = 0; x[n+1] = w+1; y[n+1] = h+1;
    sort(x.begin(),x.end()); sort(y.begin(),y.end());
    int x_max = -1, y_max = -1;
    for(int i = 1; i < n+2; ++i) {
        x_max = max(x_max,x[i]-x[i-1]-1);
        y_max = max(y_max,y[i]-y[i-1]-1);
    }
    
    fout << x_max*y_max << endl;
    
  return 0;
}
