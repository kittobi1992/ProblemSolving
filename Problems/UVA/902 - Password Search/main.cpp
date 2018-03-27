#include <bits/stdc++.h>

using namespace std;


int main() {

  ios::sync_with_stdio(false);
  int n; string e;
  while(cin >> n >> e) {
    int max_occ = -1;
    string max = "";
    map<string,int> c;
    for(int i = 0; i <= e.size()-n; i++) {
      string p = e.substr(i,n);
      c[p]++;
      if(c[p] > max_occ) { max_occ = c[p]; max = p; }
    }
    cout << max << endl;
  }
  
  return 0;
}
