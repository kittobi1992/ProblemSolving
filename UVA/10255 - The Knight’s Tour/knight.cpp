#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

typedef pair<int,int> point;

vector<vector<int>> field;	
vector<vector<int>> w;
int n, r, c;

void printArray(vector<vector<int>>& array) {
	for(int i = 0; i < array.size(); i++) {
		for(int j = 0; j < array[i].size(); j++) {
			int count = 0, num = array[i][j];
			while(num > 0) {
				count++; num /= 10;
			}
			string space(5-count,' ');
			cout << space << array[i][j];
		}
		cout << endl;
	}
}

bool isValid(point& p) {
	if(p.first < 0 || p.first >= n || p.second < 0 || p.second >= n) 
		return false;
	return true;	
}

void decrement(point& p) {
	if(isValid(p))
		w[p.first][p.second]--;
}

void increment(point& p) {
	if(isValid(p))
		w[p.first][p.second]++;
}

int distanceToCenter(point p) {
	return (p.first+1 - n/2)*(p.first+1 - n/2) + (p.second - n/2)*(p.second+1 - n/2);
}

bool backtrack(int x, int y, int pos) {	


	point p(x,y);

	if(pos == n*n && isValid(p) && field[x][y] == -1)  {
		field[x][y] = pos;
		return true;
	}

	if(!isValid(p) || field[x][y] != -1 || w[x][y] == 0) 
		return false;

	field[x][y] = pos;
	vector<point> vpp = {make_pair(x+2,y-1),make_pair(x+2,y+1),make_pair(x-2,y-1),make_pair(x-2,y+1),
			    make_pair(x-1,y+2),make_pair(x-1,y-2),make_pair(x+1,y+2),make_pair(x+1,y-2)};
	vector<point> vp;

	for(int i = 0; i < 8; i++) {
		if(isValid(vpp[i]) && field[vpp[i].first][vpp[i].second] == -1)
			vp.push_back(vpp[i]);
	}
	

	for(int i = 0; i < vp.size(); i++) 
		decrement(vp[i]);

	sort(vp.begin(),vp.end(),[&](const point& p1, const point& p2) {
		int x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;
		if(w[x1][y1] < w[x2][y2])
			return true;
		else if(w[x1][y1] == w[x2][y2]) {
			return distanceToCenter(p1) > distanceToCenter(p2);
		}
		return false;
	});
	

	for(int i = 0; i < vp.size(); i++) {
		if(w[vp[i].first][vp[i].second] == 0 && pos < n*n - 1)
			continue;
		if(backtrack(vp[i].first,vp[i].second,pos+1))
			return true;
	}

	field[x][y] = -1;
	for(int i = 0; i < vp.size(); i++) 
		increment(vp[i]);
	return false;
}

int main() {
	bool first = true;
	while(cin >> n >> r >> c) {
		field.assign(n,vector<int>(n,-1));
		w.assign(n,vector<int>(n,0));

		if(!first)			
			cout << endl;

		first = false;

		for(int x = 0; x < n; x++) {
			for(int y = 0; y < n; y++) {
				vector<point> vp = {make_pair(x+2,y-1),make_pair(x+2,y+1),make_pair(x-2,y-1),make_pair(x-2,y+1),
					    make_pair(x-1,y+2),make_pair(x-1,y-2),make_pair(x+1,y+2),make_pair(x+1,y-2)};
				for(int k = 0; k < 8; k++) {
					if(isValid(vp[k]))
						w[x][y]++;
				}
			}
		}
		
		if(n % 2 == 1 || n == 2 || n == 4) {
			if(n == 1)
				cout << "    1" << endl;
			else
				cout << "No Circuit Tour." << endl;
			continue;
		}
		
		if(backtrack(r-1,c-1,1)) {
			printArray(field);
		}

	}

	return 0;
}
