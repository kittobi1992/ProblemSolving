#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

int x, y;

bool checkPaveFrame(int a) {
	return (2*(x + y - 2)) % a == 0;
}

int main() {

	while(cin >> x >> y) {
		int n;
		cin >> n;
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			if(checkPaveFrame(a))
				cout << "YES" << endl;
			else 
				cout << "NO" << endl;
		}

	}
	
 
	return 0;
}
