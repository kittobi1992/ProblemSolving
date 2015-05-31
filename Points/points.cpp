#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

struct point {
	double x, y;
	point () {} point ( double x, double y) : x(x), y(y) {}
	bool operator <( const point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

double cross ( const point &O, const point &A, const point &B){
	double d = (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
	if (fabs(d) < 1e-9) 
		return 0.0;
	return d;
}

vector<point> convexHull(vector<point>& P){
	int n = P.size (), k = 0;
	vector<point> H(2*n);

	sort(P.begin(), P.end());

	for (int i = 0; i < n; i++) {
		while (k >= 2 && cross (H[k -2] , H[k -1] , P[i]) <= 0.0) k--;
		H[k++] = P[i];
	}

	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross (H[k -2] , H[k -1] , P[i]) <= 0.0) k--;
		H[k++] = P[i];
	}
	H.resize(k);
	return H;
}


double dist(point p1, point p2) {
	if(p1.x > p2.x)
		swap(p1,p2);
	if(p1.y > p2.y)
		p2.y += 2 * (p1.y - p2.y);

	double t = min(p2.x-p1.x,p2.y-p1.y);
	point p(p1.x + t, p1.y + t);
	double d = max(p2.y - p.y, p2.x-p.x);
	return t*sqrt(2.0) + d;
}

double perimeter(const vector<point> &P) {
  double result = 0.0;
  for (int i = 0; i < (int)P.size()-1; i++)
    result += dist(P[i], P[i+1]);
  return result; 
}

int main() {
	ios::sync_with_stdio(false);	
	int n;
	while(cin >> n) {
		vector<point> P;
		for(int i = 0; i < n; i++) {
			point p;
			cin >> p.x >> p.y;
			point p1(p.x+1,p.y), p2(p.x-1,p.y), p3(p.x,p.y+1), p4(p.x,p.y-1);
			P.push_back(p1);
			P.push_back(p2);
			P.push_back(p3);
			P.push_back(p4);
		}

		vector<point> cHull = convexHull(P);
		cout << fixed << setprecision(30) << perimeter(cHull) << endl;
	}
 
	return 0;
}
