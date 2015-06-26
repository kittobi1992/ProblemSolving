#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;

#define EPSILON 10e-9

struct point {
	int x,y;
};

int main() {
	
	ll n;
	cin >> n;
	vector<point> points;
	for(int i = 0; i < n; i++) {
		point p;
		cin >> p.x >> p.y;
		points.push_back(p);
	}

	
	ll sub_triangles = 0;
	for(int i = 0; i < points.size(); i++) {
		point p1 = points[i];
		map<double, vector<point>> slope;
		for(int j = i+1; j < points.size(); j++) {
			point p2 = points[j];
			double d = 0;
			if(p2.x - p1.x != 0)
				d = ((double) (p2.y - p1.y))/((double) (p2.x - p1.x));
			else
				d = DBL_MAX;
			auto key1 = slope.lower_bound(d);
			auto key2 = slope.lower_bound(d-6*EPSILON);
			if(abs(key1->first-d) < EPSILON)
				d = key1->first;
			if(abs(key2->first-d) < EPSILON)
				d = key2->first;
			slope[d].push_back(p2);
		}
		for(auto m : slope) {
			if(m.second.size() > 1) {
				if(m.second.size() > 1)
					sub_triangles += ((m.second.size())*(m.second.size()-1))/2;
				else
					sub_triangles += (m.second.size()-1);
			}
		}
	}
	ll triangles = (n*(n-1)*(n-2))/6;
	cout << triangles - sub_triangles << endl;

}
