#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> point;

int n, m, k;
int c[1000][1000];
bool visited1[1000][1000], visited2[1000][1000];


bool isValidField(int i, int j) {
	if(i >= 0 && i < n && j >= 0 && j < m)
		return true;
	return false;
}


int bfs(int x, int y) {
	int sum = 0;
	point pi = make_pair(x,y);
	queue<point> q;
	visited1[x][y] = true;
	q.push(pi);

	while(!q.empty()) {
		point p = q.front(); q.pop();
		int i = p.first; int j = p.second;
		sum += c[i][j];		

		if(isValidField(i-1,j) && !visited1[i-1][j] && c[i-1][j] != -1) {
			visited1[i-1][j] = true;
			q.push(make_pair(i-1,j));
		}
		if(isValidField(i,j-1) && !visited1[i][j-1] && c[i][j-1] != -1) {
			visited1[i][j-1] = true;
			q.push(make_pair(i,j-1));
		}

		if(isValidField(i+1,j) && !visited1[i+1][j] && c[i+1][j] != -1) {
			visited1[i+1][j] = true;
			q.push(make_pair(i+1,j));
		}

		if(isValidField(i,j+1) && !visited1[i][j+1] && c[i][j+1] != -1) {
			visited1[i][j+1] = true;
			q.push(make_pair(i,j+1));
		}
	}

	return sum;
}

void bfsSetValue(int x, int y, int v) {
	point pi = make_pair(x,y);
	queue<point> q;
	visited2[x][y] = true;
	q.push(pi);

	while(!q.empty()) {
		point p = q.front(); q.pop();
		int i = p.first; int j = p.second;
		c[p.first][p.second] = v;		

		if(isValidField(i-1,j) && !visited2[i-1][j] && c[i-1][j] != -1) {
			visited2[i-1][j] = true;
			q.push(make_pair(i-1,j));
		}
		if(isValidField(i,j-1) && !visited2[i][j-1] && c[i][j-1] != -1) {
			visited2[i][j-1] = true;
			q.push(make_pair(i,j-1));
		}

		if(isValidField(i+1,j) && !visited2[i+1][j] && c[i+1][j] != -1) {
			visited2[i+1][j] = true;
			q.push(make_pair(i+1,j));
		}

		if(isValidField(i,j+1) && !visited2[i][j+1] && c[i][j+1] != -1) {
			visited2[i][j+1] = true;
			q.push(make_pair(i,j+1));
		}
	}
}

int main() {

	ios::sync_with_stdio(false);

	cin >> n >> m >> k;
	memset(c, -1, 1000*1000*sizeof(int));
	memset(visited1,false,1000*1000*sizeof(bool));
	memset(visited2,false,1000*1000*sizeof(bool));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			char p; cin >> p;
			if(p == '.')
				c[i][j] = 0;
		}
	}


	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(c[i][j] == 0) {
				if(isValidField(i-1,j) && c[i-1][j] == -1)
					c[i][j]++;
				if(isValidField(i,j-1) && c[i][j-1] == -1)
					c[i][j]++;
				if(isValidField(i+1,j) && c[i+1][j] == -1)
					c[i][j]++;
				if(isValidField(i,j+1) && c[i][j+1] == -1)
					c[i][j]++;
			}
		}
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(c[i][j] != -1 && !visited1[i][j]) {
				int sum = bfs(i,j);
				bfsSetValue(i,j,sum);
			}
		}
	}

	for(int i = 0; i < k; i++) {
		int x,y; cin >> x >> y;
		cout << c[--x][--y] << endl;
	}

}
