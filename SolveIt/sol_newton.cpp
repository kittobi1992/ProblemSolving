#include <iostream>
#include <algorithm>
#include <iomanip>

#define EPSILON 1e-6
#define MAX_ITERATION 10

int p, q, r, s, t, u;

using namespace std;

double f(double x) {
	return exp(-x)*p + sin(x)*q + cos(x)*r+tan(x)*s+pow(x,2)*t + u;
}

double derivate_f(double x) {
	return exp(-x)*(-p) + cos(x)*q - sin(x)*r+(1.0/pow(cos(x),2))*s+2.0*x*t;
}

void printSolution(double x) {
	if(abs(f(x)) <= EPSILON && x >= 0 && x <= 1)
	     cout << fixed << setprecision(4) << x << endl;
	else
	     cout << "No solution" << endl;
}

int main() {

	while(cin >> p >> q >> r >> s >> t >> u) {
		double x = 0.5;

		if(f(0)*f(1) > 0) {
			printSolution(10); continue;
		} else if(f(0) == 0) {
			printSolution(0); continue;
		} else if(f(1) == 0) {
			printSolution(1); continue;
		}

		for(int i = 0; i < MAX_ITERATION; i++) {
			x = x - f(x)/derivate_f(x);
		}
		printSolution(x);
	}

	return 0;
}
