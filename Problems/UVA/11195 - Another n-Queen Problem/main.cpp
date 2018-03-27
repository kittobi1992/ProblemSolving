#include <bits/stdc++.h>

using namespace std;

int n, res;
vector<string> f;




void count(int i, int h, int ud, int ld) {
	if(i == n) { res++; return; }
	
	int free =  ((1 << n) - 1) & ~(h | ud | ld);
	for(int j = 0; j < n; ++j) {
		if(1 & (free >> j) && f[j][i] == '.') {
			count(i+1,h | (1 << j), (ud | (1 << j)) >> 1, (ld | 1 << j) << 1);
		}
	}
	
}

int main() {
  
	int t = 1;
	while(cin >> n) {
		if(n == 0) break;
		res = 0;
		
		f.resize(n);
		
		for(int i = 0; i < n; ++i) cin >> f[i];
		
		count(0,0,0,0);
		
		cout << "Case " << t++ << ": " << res << endl; 
	}
	
  	return 0;
}
