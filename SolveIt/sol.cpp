#include <iostream>
#include <algorithm>
#include <iomanip>

#define BS_EPSILON 1e-9
#define EPSILON 1e-5


using namespace std;

double f(double x, int p, int q, int r, int s, int t, int u) {
	return exp(-x)*p + sin(x)*q + cos(x)*r+tan(x)*s+pow(x,2)*t + u;
}


int main() {

	int p, q, r, s, t, u;

	while(cin >> p >> q >> r >> s >> t >> u) {
		double a = 0.0; double b = 1.0;
		while(abs(b-a) > BS_EPSILON) {
			double m = (a+b)/2;
			double vm = f(m,p,q,r,s,t,u);
			if(vm > 0)
				a = m;
			else
				b = m;
		}
		if(abs(f(a,p,q,r,s,t,u)) <= EPSILON) 
			cout << fixed << setprecision(4) << a << endl;
		else
			cout << "No solution" << endl;
	}

	return 0;
}
