#include <bits/stdc++.h>
#include <iostream>

using namespace std;


int main() {

	int test; cin >> test;
	while(test--) {
		int x; cin >> x;
		int num = x;
		if(x < 0)
			num = -x;

		if(num % 2 == 0)
			cout << x << " is even" << endl;
		else
			cout << x << " is odd" << endl;

	}

	return 0;
}
