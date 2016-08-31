#include <bits/stdc++.h>

using namespace std;

int main() {
  
  int x1, x2, y1, y2;
  x1 = 0;
  x2 = 20;
  y1 = 0;
  y2 = 20;
  int n = 10;
  cout << n << endl;
  for(int i = 0; i < n; ++i) {
    int x = x1 + (rand() % (x2-x1+1));
    int y = y1 + (rand() % (y2-y1+1));
    cout << x << " " << y << endl;;
  }
  
  return 0;
}
