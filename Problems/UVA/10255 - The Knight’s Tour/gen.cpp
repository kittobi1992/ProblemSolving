#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;


int main() {
	
	for(int n = 1; n <= 50; n++) {
		for(int x = 1; x <= n; x++) {
			for(int y = 1; y <= n; y++) {
				cout << n << " " << x << " " << y << endl;
			}
		}
	}

	return 0;
}
