#include <bits/stdc++.h>
#include <iostream>

#define EPSILON 1e-8

using namespace std;

struct point {
	long long x, y;
};

struct line {
	double a, b, c; //a*x+b*y+c, b=0 <=> vertical line , b=1 <=> otherwise
	point p1, p2;
};

line pointsToLine (point p1 , point p2) {
	line l;
	l.p1 = p1; l.p2 = p2;
	if (fabs(p1.x - p2.x) < EPSILON ) {
		l.a = 1; l.b = 0.0; l.c = -p1.x;
	} else {
		l.a = -( double )(p1.y - p2.y) / (p1.x - p2.x);
		l.b = 1.0;	
		l.c = -( double )(l.a * p1.x) - p1.y;
	}
	return l;
}

bool areParallel (line l1 , line l2) {
	return (fabs(l1.a - l2.a) < EPSILON ) && (fabs(l1.b - l2.b) < EPSILON );
}

bool areSame (line l1 , line l2) {
	return areParallel (l1 , l2) && (fabs(l1.c - l2.c) < EPSILON );
}

int main() {

	int n;
	int c = 1;
	while(cin >> n) {
		if(n == 0)
			break;

		vector<point> vp(n);
		for(int i = 0; i < n; i++) {
			point p;
			cin >> p.x >> p.y;
			vp[i] = p;
		}

		vector<line> vl;
		for(int i = 0; i < n; i++) {
			for(int j = i+1; j < n; j++) {
				line l = pointsToLine(vp[i],vp[j]);
				vl.push_back(l);
			}
		}

		sort(vl.begin(),vl.end(),[&](const line& l1, const line& l2) {
			return l1.b == l2.b ? l1.a < l2.a : l1.b < l2.b;
		});

		int trapzoids = 0;
		for(int i = 0; i < vl.size(); i++) {
			int j = i + 1;
			while(j < vl.size() && areParallel(vl[i], vl[j])) {
				if(areSame(vl[i],vl[j])) {
					j++;
					continue;
				}
				line l1 = pointsToLine(vl[i].p1,vl[j].p1);
				line l2 = pointsToLine(vl[i].p2,vl[j].p2);
				line l3 = pointsToLine(vl[i].p1,vl[j].p2);
				line l4 = pointsToLine(vl[i].p2,vl[j].p1);
				if(!(areParallel(l1,l2) || areParallel(l3,l4)))
					trapzoids++;
				j++;	
			}
		}

		cout << "Case " << c << ": " << trapzoids << endl;
		c++;
		
	}	

	return 0;
}
