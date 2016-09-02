#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
  int x1, x2, y1, y2;
  x1 = 0;
  x2 = 10000;
  y1 = 0;
  y2 = 10000;
  int n = 2000000;
  cout << n << endl;
  for(int i = 0; i < n; ++i) {
    int x = x1 + (rand() % (x2-x1+1));
    int y = y1 + (rand() % (y2-y1+1));
    if((x < 2500 || x > 7500) || (y < 2500 || y > 7500))
      cout << x << " " << y << endl;
    else
     i--;
  }
  
  return 0;
}
