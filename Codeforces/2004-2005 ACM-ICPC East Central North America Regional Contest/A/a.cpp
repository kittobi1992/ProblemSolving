#include <bits/stdc++.h>
#include <iostream>

using namespace std;

vector<int> solutions;

int main() {
  string s; cin >> s;
  while (s != "0") {
    solutions.clear();
    solutions = vector<int>(s.size(), 0);
    for (int i = 0; i < s.size(); i++) {
      char c = s[s.size()-1-i];
      if (c == '0') { solutions[i] = 0; }
      else if (i == 0) { solutions[i] = 1; }
      else if (c == '1' || (c == '2' && s[s.size()-i] <= '6')) {
	if (i == 1) {
	  solutions[i] = solutions[i-1]+1;
	} else if (i > 1) {
	  solutions[i] = solutions[i-1] + solutions[i-2];
	} else {
	  solutions[i] = 1;
	}
      } else { solutions[i] = solutions[i-1]; }
    }
    cout << solutions[s.size()-1] << endl;
    cin >> s;
  }
  return 0;
}
