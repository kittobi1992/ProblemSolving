#include <bits/stdc++.h>

using namespace std;

#define EPS 10e-6

double a, b, v, f; 
vector<double> s, l;
int r;

double length(double w, double h) {
	return sqrt(w*w+h*h)/1000.0;	
}

double slope(double w, double h) {
	return h/w;	
}

double fuelConsumptionOnRoadSegment(double v, int i) {
	return max(0.0,a*v+b*s[i])*l[i];	
}

double calculateFuelConsumption(double v) {
	double fuelConsumption = 0.0;
	for(int i = 0; i < r; ++i) {
		fuelConsumption += fuelConsumptionOnRoadSegment(v,i);	
	}
	return fuelConsumption;
}

int main() {
  
    int test; cin >> test;
    while(test--) {
			cin >> a >> b >> v >> f;
			
			cin >> r;
			s.resize(r); l.resize(r);
			double total_length = 0.0;
			for(int i = 0; i < r; ++i) {
				double w, h; cin >> w >> h;
				s[i] = slope(w,h); l[i] = length(w,h);
				total_length += l[i];
			}
			
			bool valid = false;
			double vl = 0.0, vr = v;
			for(int i = 0; i < 100; ++i) {
				double vm = (vl+vr)/2.0;	
				double fm = calculateFuelConsumption(vm);
				if(fm <= f) { vl = vm; valid = true;}
				else vr = vm;
			}
			
			double total_time = 0.0;
			for(int i = 0; i < r; ++i) {
				double fuelConsumption = a*vl+b*s[i];
				if(fuelConsumption < 0.0) {
					double vm = min(-b*s[i]/a,v);
					total_time += l[i]/vm;
				}
				else total_time += l[i]/vl;
			}
    
    		if(valid) cout << fixed << setprecision(10) <<  total_time << endl;
			else cout << "IMPOSSIBLE" << endl;
    
    }
    
    return 0;
}
