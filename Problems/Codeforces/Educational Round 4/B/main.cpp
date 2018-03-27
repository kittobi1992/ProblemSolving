#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
  
  int n; cin >> n;
  vector<ll> f(n);
  vector<ll> pos(n);
  for(int i = 0; i < n; i++) {
    cin >> f[i];
    pos[--f[i]] = i;
  }
  
  ll t = 0; 
  for(int i = 1; i < n; i++)
    t += abs(pos[i-1]-pos[i]);
  
  cout << t << endl;
  
  return 0;
}
