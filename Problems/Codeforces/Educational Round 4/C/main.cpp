#include <bits/stdc++.h>

using namespace std;

map<char,bool> o;
map<char,char> m;

void initialize() {
  o['<'] = true; o['{'] = true; o['('] = true; o['['] = true;
  m['>'] = '<'; m['}'] = '{'; m[')'] = '('; m[']'] = '[';
}

int main() {
  initialize();
  string rbs; cin >> rbs;
  stack<char> s;
  int r = 0;
  for(int i = 0; i < rbs.size(); i++) {
    char b = rbs[i];
    if(s.empty() && !o[b]) {
      cout << "Impossible" << endl;
      return 0;
    } else if(s.empty() && o[b]) {
      s.push(b);
    } else {
      if(o[b]) s.push(b);
      else {
	if(s.top() != m[b]) r++;
	s.pop();
      }
    }
    
  }
  
  if(s.empty()) {
    cout << r << endl;
  }
  else {
    cout << "Impossible" << endl; 
  }
  
  
  return 0;
}
