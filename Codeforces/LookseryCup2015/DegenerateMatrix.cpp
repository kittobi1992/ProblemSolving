#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>

using namespace std;
typedef long long ll;
#define EPSILON 10e-10

double a, b, c, d;

bool test(double m) {
		double a1 = a + m;
		double a2 = a - m;
		double d1 = d + m;
		double d2 = d - m;
		double b1 = b + m;
		double b2 = b - m;
		double c1 = c + m;	
		double c2 = c - m;
		double ad_max = max(a1*d1,max(a1*d2,max(a2*d1,a2*d2)));
		double ad_min = min(a1*d1,min(a1*d2,min(a2*d1,a2*d2)));
		double bc_max = max(b1*c1,max(b1*c2,max(b2*c1,b2*c2)));
		double bc_min = min(b1*c1,min(b1*c2,min(b2*c1,b2*c2)));
		if(ad_max - bc_min >= 0 && ad_min - bc_max <= 0)
			return true;
	return false;
	 
}

int main() {

	double l = 0.0, r = 10e9;
	cin >> a >> b >> c >> d;

	if((a == b && b == c && c == d) || test(0.0)) {
		cout << "0.000000" << endl;
		return 0; 
	}
	
	
	int iterations = 0;
	while(abs(r-l) > EPSILON && iterations < 1000) {
		double m = (l+r)/2.0;

		if(test(m))
			r = m;
		else
			l = m;
		iterations++;
	}
	
        printf("%.10lf\n",r);

	return 0;
}
