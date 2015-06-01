#include <iostream>
#include <algorithm>
#include <stdlib.h>   
#include <time.h> 

#define BS_EPSILON 1e-9
#define EPSILON 1e-5


using namespace std;

double f(double x, int p, int q, int r, int s, int t, int u) {
	return exp(-x)*p + sin(x)*q + cos(x)*r+tan(x)*s+pow(x,2)*t + u;
}


struct sol {
	int p, q, r,s,t,u;
	
	bool allZero() {
	    return (p || q || r || s || t || u) == 0;
	}
};
typedef struct sol sol;

double getSolution(int p, int q, int r, int s, int t, int u) {
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
			return a;
		else
			return 2.0;
}

void tryToCreateSolution(sol& so) {
	for(int u = -20; u < 20; u++) {
		double x = getSolution(so.p,so.q,so.r,so.s,so.t,u); 
		if(x != 2.0 && x != 0.0) {
			so.u = u;
			break;
		}
	}
}

vector<sol> getRandomTestCases(int n) {
	vector<sol> sv;

	for(int i = 0; i < 2*n/3; i++) {
		sol so = {rand()%21, -(rand()%21), rand()%21, -(rand()%21), -(rand()%21),((int)pow(-1,rand()%2))*(rand()%5)};
		tryToCreateSolution(so);
		sv.push_back(so);
	}

	for(int i = 0; i < n/3; i++) {
		sol so = {rand()%21, -(rand()%21), rand()%21, -(rand()%21), -(rand()%21),((int)pow(-1,rand()%2))*(rand()%5)};
		sv.push_back(so);
	}

	return sv;
}

vector<sol> getTestCaseForSpecificRoot(vector<double> root) {
	vector<sol> sv;

	for(int p = 0; p <= 20; p++) {
		for(int q = 0; q >= -20; q--) {
			for(int r = 0; r <= 20; r++) {
				for(int s = 0; s >= -20; s--) {
					for(int t = 0; t >= -20; t--) {
						for(int u = -1; u <= 1; u++) {
							for(int i = 0; i < root.size(); i++) {
								if(abs(f(root[i],p,q,r,s,t,u)) <= EPSILON) {
									sol so = {p,q,r,s,t,u};
									sv.push_back(so);					
								}
							}								
						}
					}
				}
			}
		}
	}

	return sv;
}

int main() {
	srand (time(NULL));
	vector<double> root {-0.1,-0.01,1.1,1.01,1.001};
	vector<sol> sv = getRandomTestCases(2100);

	random_shuffle(sv.begin(),sv.end());
	for(int i = 0; i < min(2100,((int)sv.size())); i++) {
		if(!sv[i].allZero())
			cout << sv[i].p << " " << sv[i].q << " " << sv[i].r << " " << sv[i].s << " " << sv[i].t << " " << sv[i].u << endl;
	}

	return 0;
}
