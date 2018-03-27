#include <bits/stdc++.h>
#include <iostream>
#include <map>

using namespace std;

#define PI acos(-1)

int main() {

	double r, m, c;
	while(cin >> r >> m >> c) {
		if(r+m+c == 0)
			break;

		double A = PI*r*r;
		double est = (4*c*r*r)/m;
	
		cout << fixed << setprecision(8) << A << " " << est << endl;

	}

	return 0;
}
