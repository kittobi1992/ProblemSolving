#include <iostream>
#include <algorithm>
#include <iomanip>

#define EPSILON 1e-4


using namespace std;

int p, q, r, s, t, u;

double f(double x) {
	return exp(-x)*p + sin(x)*q + cos(x)*r+tan(x)*s+pow(x,2)*t + u;
}


int main() {

	while(cin >> p >> q >> r >> s >> t >> u) {
		double step = 0.00001;
		double x = 0.0;
		for(; x <= 1.0; x += step) {
			if(abs(f(x)) < EPSILON) {
				cout << fixed << setprecision(4) << x << endl;
				break;	
			}
		}
		if(x > 1.0) {
			cout << "No solution" << endl;
		}
	}

	return 0;
}
