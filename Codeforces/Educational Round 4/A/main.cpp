#include <bits/stdc++.h>

using namespace std;

int main() {
  
  int n,p,q; cin >> n >> p >> q;
  string s; cin >> s;
  
  for(int i = 0; i*p <= n; i++) {
    for(int j = 0; i*p + j*q <= n; j++) {
	if(i*p + j*q == n) {
	  cout << i+j << endl;
	  for(int k = 0; k < i*p; k += p) {
	    cout << s.substr(k,p) << endl;
	  }  
	  for(int k = i*p; k < n; k += q) {
	    cout << s.substr(k,q) << endl;
	  } 	  
	  return 0;
	}
    }
  }
  
  cout << "-1" << endl;
  
  return 0;
}
