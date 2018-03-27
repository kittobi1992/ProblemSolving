#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;

#define EPS 10e-13

int main() {

	ll n;
	ll w;
	cin >> n >> w;
	vector<ll> tea(2*n);
	for(int i = 0; i < 2*n; i++) {
		cin >> tea[i];
	}
	
	sort(tea.begin(),tea.end());

	ll min_boy = min(tea[0]*2,tea[n]);
	double amount = ((double)(min_boy*n))/2.0 + n*min_boy;
	if(amount > w) {
		double l = 0.0;
		double r = ((double)min_boy)/2.0;
		while(abs(r-l) > EPS) {
			double m = (l+r)/2.0;
			ll v = m*n + m*n*2.0;
			if(v < w) 
				l = m;
			else
				r = m;
		}
		amount = r*n + r*n*2.0;
	}

	cout << amount << endl;
	
	

}
