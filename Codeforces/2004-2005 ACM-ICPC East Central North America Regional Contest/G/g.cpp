#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int main() {

  int n;
  while(cin >> n) {
      if(n == 0)
	 break;
      
      string s;
      cin >> s;
      int m = s.size() / n;
      for(int i = n; i < s.size(); i += 2*n) {
	 reverse(s.begin()+i, s.begin()+i+n);
      }
      for(int i = 0; i < n; i++) {
	 for(int j = 0; j < m; j++) {
	    cout << s[j*n + i];
	 }
      }
      cout << endl;
      
  }
  
  return 0;

}
