#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;

int main() {

	int n; cin >> n;
	int min_x = 2000, max_x = -2000, min_y = 2000, max_y = -2000;
	for(int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		min_x = min(min_x,x);
		min_y = min(min_y,y);
		max_x = max(max_x,x);
		max_y = max(max_y,y);
	}

	if(max_x-min_x > 0 && max_y-min_y > 0)
		cout << (max_x-min_x)*(max_y-min_y) << endl;
	else
		cout << "-1" << endl;
	
	return 0;
	

}
