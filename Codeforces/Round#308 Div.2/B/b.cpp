#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;

int main() {
	ll n;
	cin >> n;
	ll digit = 0;
	for(int i = 1; i <= 30; i++) {
		ll b = pow(10,i)-pow(10,i-1);
		if(n - b >= 0) {
			digit += i*b;
		}
		else {
			digit += i*n;
		}

		n -= b;
		if(n < 0) 
			break;
	}
	cout << digit << endl;
}
