#include <bits/stdc++.h>
#include <iostream>
using namespace std;


int main() {
	
	int n;
	cin >> n;
	vector<int> t(n,0);
	for(int i = 0; i < n; i++) {
		cin >> t[i];
	}

	int p = n - t[0];
	int c = 0;
	for(int i = 0; i < n; i++) {
		if(c == 0) {
			t[i] = (t[i] + p) % n;
			c = 1;
		} else {
			t[i] = (t[i] - p);
			if(t[i] < 0)
				t[i] += n;
			t[i] = t[i] % n;
			c = 0;
		}
	}

	for(int i = 0; i < n; i++) {
		if(i != t[i]) {
			cout << "NO" << endl;
			return 0;
		}
	}

	cout << "YES" << endl;
	return 0;
}
