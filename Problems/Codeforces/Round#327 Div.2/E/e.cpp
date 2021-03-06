#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef pair<int,int> point;

int n,m; 
vector<vector<char>> k;
vector<vector<int>> visited;
int threshold = 1;

void reset() {
	threshold++;
}

bool isVisited(int i, int j) {
	return visited[i][j] == threshold;
}

void setBit(int i, int j) {
	visited[i][j] = threshold;
}

bool isValidField(int i, int j) {
	return i >= 0 && i < n && j >= 0 && j < m;
}

vector<point> startPoints(char country, char search) {
	vector<point> sp;

	point start;
	bool found = false;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(k[i][j] == country) {
				start = make_pair(i,j);
				found = true;
				break;
			}
		}
		if(found)
			break;
	}

	queue<point> q;
	q.push(start);
	setBit(start.first,start.second);
	while(!q.empty()) {
		point p = q.front(); q.pop();
		
		int i = p.first; int j = p.second;

		
		if(isValidField(i-1,j) && k[i-1][j] == search && !isVisited(i-1,j)) {
			sp.push_back(make_pair(i-1,j));
			setBit(i-1,j);
		}
		if(isValidField(i-1,j) && k[i-1][j] == country && !isVisited(i-1,j)) {
			q.push(make_pair(i-1,j));
			setBit(i-1,j);
		}
		if(isValidField(i+1,j) && k[i+1][j] == search && !isVisited(i+1,j)) {
			sp.push_back(make_pair(i+1,j));
			setBit(i+1,j);
		}
		if(isValidField(i+1,j) && k[i+1][j] == country && !isVisited(i+1,j)) {
			q.push(make_pair(i+1,j));
			setBit(i+1,j);
		}
		if(isValidField(i,j-1) && k[i][j-1] == search && !isVisited(i,j-1)) {
			sp.push_back(make_pair(i,j-1));
			setBit(i,j-1);
		}
		if(isValidField(i,j-1) && k[i][j-1] == country && !isVisited(i,j-1)) {
			q.push(make_pair(i,j-1));
			setBit(i,j-1);
		}
		if(isValidField(i,j+1) && k[i][j+1] == search && !isVisited(i,j+1)) {
			sp.push_back(make_pair(i,j+1));
			setBit(i,j+1);
		}
		if(isValidField(i,j+1) && k[i][j+1] == country && !isVisited(i,j+1)) {
			q.push(make_pair(i,j+1));
			setBit(i,j+1);
		}
	}

	reset();
	return sp;
}

int bfs(char c1, char c2) {
	
	vector<point> b = startPoints(c1,c2);
	if(b.size() > 0)
		return 0;

	vector<point> sp = startPoints(c1,'.');
	queue<point> q, nq;
	for(point p : sp) {
		q.push(p);
		setBit(p.first,p.second);
	}

	int dist = 0;
	bool found = false;
	while(!q.empty()) {
		point p = q.front(); q.pop();
		int i = p.first; int j = p.second;

		if(isValidField(i-1,j) && k[i-1][j] == '.' && !isVisited(i-1,j)) {
			nq.push(make_pair(i-1,j));
			setBit(i-1,j);
		}
		if(isValidField(i+1,j) && k[i+1][j] == '.' && !isVisited(i+1,j)) {
			nq.push(make_pair(i+1,j));
			setBit(i+1,j);
		}
		if(isValidField(i,j-1) && k[i][j-1] == '.' && !isVisited(i,j-1)) {
			nq.push(make_pair(i,j-1));
			setBit(i,j-1);
		}
		if(isValidField(i,j+1) && k[i][j+1] == '.' && !isVisited(i,j+1)) {
			nq.push(make_pair(i,j+1));
			setBit(i,j+1);
		}

		if(isValidField(i-1,j) && k[i-1][j] == c2 && !isVisited(i-1,j)) {
			found = true; dist++; break;
		}
		if(isValidField(i+1,j) && k[i+1][j] == c2 && !isVisited(i+1,j)) {
			found = true; dist++; break;
		}
		if(isValidField(i,j-1) && k[i][j-1] == c2 && !isVisited(i,j-1)) {
			found = true; dist++; break;
		}
		if(isValidField(i,j+1) && k[i][j+1] == c2 && !isVisited(i,j+1)) {
			found = true; dist++; break;
		}

		if(q.empty()) {
			dist++;
			swap(q,nq);
		}
	}

	reset();

	if(!found)
		return -1;

	return dist;

}

int main() {

	ios::sync_with_stdio(false);
	
	cin >> n >> m;
	
	k.assign(n,vector<char>(m,'.'));
	visited.assign(n,vector<int>(m,0));
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cin >> k[i][j];
		}
	}

	int dist1 = bfs('1','2');
	int dist2 = bfs('1','3');
	int dist3 = bfs('2','3'); 

	if(dist1 != -1 && dist2 != -1 && dist3 != -1)
		cout << min(dist1+dist2,min(dist1+dist3,dist2+dist3)) << endl; 
	else if(dist1 == -1 && dist2 != -1 && dist3 != -1)
		cout << (dist2+dist3) << endl;
	else if(dist1 != -1 && dist2 == -1 && dist3 != -1)
		cout << (dist1+dist3) << endl;
	else if(dist1 != -1 && dist2 != -1 && dist3 == -1)
		cout << (dist1+dist2) << endl;
	else
		cout << "-1" << endl;
	
	return 0;

}
