#include <bits/stdc++.h>

using namespace std;


int main() {
	int l, r, a;
	cin >> l >> r >> a;

	int m = min(l,r);
	int d = abs(r-l);
	int res = 2*m;
	for(; d > 0; --d) {
		if(a > 0) res += 2;
		else break;
		a--;
	}
	res += 2*(a/2);

	cout << res << endl;

	return 0;
}
