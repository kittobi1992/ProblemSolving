#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> point;

point operator+(const point& p1, const point& p2) {
	return make_pair(p1.first+p2.first,p1.second+p2.second);
}

point operator*(const int a, const point& p) {
	return make_pair(a*p.first,a*p.second);
}

vector<point> dir = {make_pair(0,0),make_pair(1,0),make_pair(0,1),make_pair(1,1)};
map<char,int> m;

void initialize() {
	m['0'] = 0; m['1'] = 1; m['2'] = 2; m['3'] = 3;
}

int main() {

	initialize();

	string s; cin >> s;
	point p = make_pair(0,0);
	for(int i = 0; i < s.size(); i++) {
		p = 2*p;
		p = p + dir[m[s[i]]];
	}

	cout << s.size() << " " << p.first << " " << p.second << endl;

	return 0;
}
