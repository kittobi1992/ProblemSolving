#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

typedef pair<long long,long long> ll;

struct point {
	long long x, y, z;
};

long long gcd(long long a, long long b) {
	return b == 0 ? a : gcd (b, a % b);
}


int main() {
	ios::sync_with_stdio(false);
	int c = 1;	
	int n;
	while(cin >> n) {
		if(n == 0)
			break;
		map<ll, vector<point>> dir_map;
		set<ll> dirs;
		for(int i = 0; i < n; i++) {
			point p;
			cin >> p.x >> p.y >> p.z;
			int d = gcd(abs(p.x),abs(p.y));
			ll hash(p.x/d,p.y/d);
			dirs.insert(hash);
			dir_map[hash].push_back(p);
		}

		vector<ll> invisible_lights;
		for(ll dir : dirs) {
			sort(dir_map[dir].begin(),dir_map[dir].end(),[&](const point& p1, const point& p2) {
				return p1.x*p1.x + p1.y*p1.y < p2.x*p2.x + p2.y*p2.y;
			});
			int max_height = INT_MIN; 
			for(point p : dir_map[dir]) {
				if(max_height >= p.z) {
					invisible_lights.push_back(ll(p.x,p.y));
				}
				else {
					max_height = p.z;
				}
			}
		}	
		
		cout << "Data set " << c << ":" << endl;
		if(invisible_lights.size() == 0) {
			cout << "All the lights are visible." << endl;
		}
		else {
			sort(invisible_lights.begin(),invisible_lights.end(),[&](const ll& i1, const ll& i2) {
				if (i1.first != i2.first) {
        				return i1.first < i2.first;
    				}
				return i1.second < i2.second;
			});
			cout << "Some lights are not visible:" << endl;
			for(int i = 0; i < invisible_lights.size()-1; i++) {
				cout << "x = " << invisible_lights[i].first << ", y = " << invisible_lights[i].second << ";" << endl;
			}
			cout << "x = " << invisible_lights[invisible_lights.size()-1].first << ", y = " 
					<< invisible_lights[invisible_lights.size()-1].second << "." << endl;
		}

		c++;

	}
	

	return 0;
}
