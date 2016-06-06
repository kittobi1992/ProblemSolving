#include <bits/stdc++.h>

using namespace std;

int main() {
  
  int n, h; cin >> n >> h;
  vector<int> a(n);
  for(int i = 0; i < n; ++i) cin >> a[i];
  
  int res = 0;
  for(int i = 0; i < n; ++i) {
    if(a[i] <= h)
      res++;
    else
      res += 2;
  }
  
  cout << res << endl;
  
  return 0;
}
