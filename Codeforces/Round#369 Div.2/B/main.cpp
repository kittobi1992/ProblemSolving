#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool isMagicSquare(vector<vector<ll>>& a, int n, ll sum) {
	for(int i = 0; i < n; ++i) {
		ll s = 0;
		for(int j = 0; j < n; ++j) s += a[i][j];	
		if(s != sum) return false;
	}
	for(int i = 0; i < n; ++i) {
		ll s = 0;
		for(int j = 0; j < n; ++j) s += a[j][i];	
		if(s != sum) return false;
	}
	
	ll s = 0;
	for(int i = 0; i < n; ++i) s += a[i][i];
	if(s != sum) return false;
	
	s = 0;
	for(int i = 0; i < n; ++i) s += a[i][n-i-1];
	if(s != sum) return false;
	
	return true;
}
int main() {
  
	int n; cin >> n;
	
	if(n == 1) { cout << "1" << endl; return 0; }
		
	
	vector<vector<ll>> a(n, vector<ll>(n,0));
	int x, y;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			cin >> a[i][j];
			if(a[i][j] == 0) { x = i; y = j; }
		}
	}
	
	ll num = -1;
	ll sum_x = 0, sum_y = 0;
	for(int i = 0; i < n; ++i) {
		sum_x += a[x][i]; sum_y += a[i][y];
	}
	
	if(sum_x != sum_y) { cout << num << endl; return 0; }
	
	int new_x = (x+1 == n) ? 0 : x+1;
	ll sum_new_x = 0;
	for(int i = 0; i < n; ++i) {
		sum_new_x += a[new_x][i];
	}
	num = sum_new_x - sum_x;
	
	if(num <= 0) { cout << "-1" << endl; return 0; }
	
	a[x][y] = num;
	
	if(isMagicSquare(a,n,sum_new_x)) cout << num << endl;
	else cout << "-1" << endl;
	
  return 0;
}
