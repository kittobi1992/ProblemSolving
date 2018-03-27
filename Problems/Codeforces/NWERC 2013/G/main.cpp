#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll AB, AC, BD;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    
    while(cin >> AB >> AC >> BD) {
        int g = gcd(AC*AB,BD-AC);
        cout << (AC*AB)/g << "/" << (BD-AC)/g << endl; 
    }
    
	return 0;
}
