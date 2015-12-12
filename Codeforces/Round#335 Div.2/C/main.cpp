#include <bits/stdc++.h>

using namespace std;



int main() {
	int n; cin >> n;
	vector<int> p(n+1);
	vector<int> pos(n+1);
	for(int i = 1; i <= n; i++) {
	  cin >> p[i];
	  pos[p[i]] = i;
	}
	
	int max_pile = -1;
	int start = 1;
	for(int i = 2; i <= n; i++) {
	  if(pos[i-1] > pos[i]) {
	    max_pile = max(max_pile,i-start);
	    start = i;
	  }
	}
	max_pile = max(max_pile,(n+1)-start);
	
	cout << (n - max_pile) << endl;

	return 0;
}
