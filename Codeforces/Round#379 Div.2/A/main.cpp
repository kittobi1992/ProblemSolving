#include <bits/stdc++.h>

using namespace std;


int main() {
  int N; string s;
  cin >> N >> s;
  int a = 0, d = 0;
  for(int i = 0; i < N; ++i) {
    if(s[i] == 'A') a++;
    else d++;
  }
  
  if(a > d) cout << "Anton" << endl;
  else if(a < d) cout << "Danik" << endl;
  else cout << "Friendship" << endl;
    
	return 0;
}
