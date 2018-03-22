#include <bits/stdc++.h>

using namespace std;


int main() {
	int n, m;
	cin >> n >> m;
	vector<int> x(n,0);
	vector<int> y(m,0);
	for(int i = 0; i < n; ++i) cin >> x[i];
	for(int i = 0; i < m; ++i) cin >> y[i];

	int i = 0, j = 0, sum_x = x[0], sum_y = y[0];
	int res = 0;
	while(i < n || j < m) {
		if(sum_x < sum_y) {
			sum_x += x[++i];
		} else if(sum_x > sum_y) {
			sum_y += y[++j];
		} else {
			res++; i++; j++;
			sum_x = 0; sum_y = 0;
			if(i < n) sum_x = x[i];
			if(j < m) sum_y = y[j];
		}
	}

	cout << res << endl;

	return 0;
}
