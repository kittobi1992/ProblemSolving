#include <bits/stdc++.h>
#include <iostream>
using namespace std;


int main() {

	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}

	int pieces = 0;
	int dir = 0;
	vector<bool> col(n,false);
	while(pieces != n) {
		for(int i = 0; i < n; i++) {
			if(a[i] <= pieces && !col[i]) {
				col[i] = true; pieces++;
			}	
		}
		if(pieces == n)
			break;
		dir++;
		for(int i = n-1; i >= 0; i--) {
			if(a[i] <= pieces && !col[i]) {
				col[i] = true; pieces++;
			}	
		}
		if(pieces == n)
			break;
		dir++;
	}

	cout << dir << endl;

}
