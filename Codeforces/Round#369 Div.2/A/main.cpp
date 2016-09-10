#include <bits/stdc++.h>

using namespace std;

int main() {
  
	int n; cin >> n;
	vector<string> b(n);
	for(int i = 0; i < n; ++i) cin >> b[i];
	
	bool found = false;
	for(int i = 0; i < n; ++i) {
		if(b[i][0] == 'O' && b[i][1] == 'O') { b[i][0] = '+'; b[i][1] = '+';	found = true; break; }
		if(b[i][3] == 'O' && b[i][4] == 'O') { b[i][3] = '+'; b[i][4] = '+';	found = true; break; }
	}
	
	if(found) {cout << "YES" << endl; 	for(int i = 0; i < n; ++i) cout << b[i] << endl; }
	else cout << "NO" << endl;

  return 0;
}
