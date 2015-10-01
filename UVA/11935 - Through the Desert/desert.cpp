#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;


struct car {
	double normal_csp, cur_csp, cur_ltr, max_ltr; 
	int leaks, last_km;

	void calculate_consumption_in_litre(int km) {
		cur_ltr += ((double) (km - last_km))*cur_csp;
		last_km = km;
	}

	void change_fuel_consumption(double csp) {
		normal_csp = csp/100.0;
		cur_csp = csp/100.0 + ((double) leaks);
	}

	void add_leak() {
		leaks++;
		cur_csp += 1.0;
	}

	void gas_station() {
		max_ltr = max(max_ltr,cur_ltr);
		cur_ltr = 0.0;
	}

	void mechanic() {
		leaks = 0;
		cur_csp = normal_csp;
	}

	void goal() {
		max_ltr = max(max_ltr,cur_ltr);
	}

	void to_string(int km) {
		cout << "Kilometer " << km << ": " << endl;
		cout << "Normal Consumption = " << normal_csp << endl;
		cout << "Current Consumption = " << cur_csp << endl;
		cout << "Consumption since last tank (in litre) = " << cur_ltr << endl;
		cout << "Leaks = " << leaks << endl;
		cout << "Last event was at kilometer " << last_km << endl;
		cout << "----------------------" << endl;
	}
};

void init_car(car& c, double csp) {
	c.normal_csp = csp/100.0;
	c.cur_csp = csp/100.0;
	c.cur_ltr = 0.0;
	c.max_ltr = 0.0;
	c.leaks = 0;
	c.last_km = 0;
}

int main() {
	
	while(true) {
		double tank = 0.0;
		double consumption; string fuel;
		cin >> consumption >> fuel >> fuel >> consumption;
		if(consumption == 0)
    			break;

		car c; init_car(c,consumption);

		string event(fuel); int km;
		while(event.compare("Goal") != 0) {
			cin >> km >> event;
			c.calculate_consumption_in_litre(km);

			if(event.compare("Fuel") == 0) {
				double csp; cin >> event >> csp;
				c.change_fuel_consumption(csp);
			} else if(event.compare("Leak") == 0) {
				c.add_leak();
			} else if(event.compare("Gas") == 0) {
				cin >> event;
				c.gas_station();
			} else if(event.compare("Mechanic") == 0) {
				c.mechanic();
			} else if(event.compare("Goal") == 0) {
				c.goal();
			}

		}

		cout << fixed << setprecision(3) << c.max_ltr << endl;
				
	}

	return 0;
}
