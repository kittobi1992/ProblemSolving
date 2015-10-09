#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

typedef long long ll;

typedef pair<char,pair<int,int>> pos;
typedef vector<vector<char>> board;

vector<pos> p;
board b;
vector<bool> vis;
int c = 0;

void move_stone(int i, int x, int y) {
	char c = p[i].first;
	b[y][x] = c; b[y+1][x] = c; b[y][x+1] = c; b[y+1][x+1] = c;
	p[i] = make_pair(c,make_pair(y,x));
}

bool isValidPosition(int i, int x, int y) {
	return b[y][x] == '.' && b[y+1][x] == '.' && b[y][x+1] == '.' && b[y+1][x+1] == '.';
}

void gravity_north() {
	sort(p.begin(),p.end(), [&](const pos p1, const pos p2) {
		if(p1.second.first < p2.second.first)
			return true;
		else if(p1.second.first == p2.second.first) 
			return p1.first < p2.first;
		else
			return false;
	});

	for(int i = 0; i < 4; i++) {
		int x = p[i].second.second; int ny = p[i].second.first;
		b[ny][x] = '.'; b[ny+1][x] = '.'; b[ny][x+1] = '.'; b[ny+1][x+1] = '.';
		for(int y = ny; y >= 0; y--) {
			if(isValidPosition(i,x,y))
				ny = y;
			else
				break;
		}
		move_stone(i,x,ny);
	}

}

void gravity_south() {
	sort(p.begin(),p.end(), [&](const pos p1, const pos p2) {
		if(p1.second.first > p2.second.first)
			return true;
		else if(p1.second.first == p2.second.first) 
			return p1.first < p2.first;
		else
			return false;
	});

	for(int i = 0; i < 4; i++) {
		int x = p[i].second.second; int ny = p[i].second.first;
		b[ny][x] = '.'; b[ny+1][x] = '.'; b[ny][x+1] = '.'; b[ny+1][x+1] = '.';
		for(int y = ny; y < 7; y++) {
			if(isValidPosition(i,x,y))
				ny = y;
			else
				break;
		}
		move_stone(i,x,ny);
	}

}

void gravity_east() {
	sort(p.begin(),p.end(), [&](const pos p1, const pos p2) {
		if(p1.second.second > p2.second.second)
			return true;
		else if(p1.second.second == p2.second.second) 
			return p1.first < p2.first;
		else
			return false;
	});

	for(int i = 0; i < 4; i++) {
		int nx = p[i].second.second; int y = p[i].second.first;
		b[y][nx] = '.'; b[y+1][nx] = '.'; b[y][nx+1] = '.'; b[y+1][nx+1] = '.';
		for(int x = nx; x < 7; x++) {
			if(isValidPosition(i,x,y))
				nx = x;
			else
				break;
		}
		move_stone(i,nx,y);
	}

}

void gravity_west() {
	sort(p.begin(),p.end(), [&](const pos p1, const pos p2) {
		if(p1.second.second < p2.second.second)
			return true;
		else if(p1.second.second == p2.second.second) 
			return p1.first < p2.first;
		else
			return false;
	});
	

	for(int i = 0; i < 4; i++) {
		int nx = p[i].second.second; int y = p[i].second.first;
		b[y][nx] = '.'; b[y+1][nx] = '.'; b[y][nx+1] = '.'; b[y+1][nx+1] = '.';
		for(int x = nx; x >= 0; x--) {
			if(isValidPosition(i,x,y))
				nx = x;
			else
				break;
		}
		move_stone(i,nx,y);
	}

}

ll get_state() { 
	ll state = 0;
	for(int i = 0; i < 4; i++) {
		int x = p[i].second.second, y = p[i].second.first;
		state += (y*8+x)*pow(64,i);
	}
	return state;
}

void dfs() {
	sort(p.begin(),p.end(), [&](const pos p1, const pos p2) {
		return p1.first < p2.first;
	});
	int state = get_state();
	if(vis[state])
		return;
	vis[state] = true;
	c++;

	board save_b(b);
	vector<pos> save_p(p);
	gravity_north(); dfs(); b = save_b; p = save_p;
	gravity_south(); dfs(); b = save_b; p = save_p;
	gravity_west(); dfs(); b = save_b; p = save_p;
	gravity_east(); dfs(); b = save_b; p = save_p;

}

int main() {

		
	int test; cin >> test;
	int t = 1;
	while(test--) {
		
		b.assign(8,vector<char>(8));		
		p.assign(4,make_pair('X',make_pair(-1,-1)));
		vis.assign(pow(64,4),false);

		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				cin >> b[i][j];
				if(b[i][j] >= 'A' && b[i][j] <= 'D') {
					int idx = b[i][j] - 'A';
					if(p[idx].first == 'X') p[idx] = make_pair(b[i][j],make_pair(i,j));
				}
			}
		}
		
		c = 0;

		board save_b(b);
		vector<pos> save_p(p);
		gravity_north(); dfs(); b = save_b; p = save_p;
		gravity_south(); dfs(); b = save_b; p = save_p;
		gravity_west(); dfs(); b = save_b; p = save_p;
		gravity_east(); dfs(); b = save_b; p = save_p;

		cout << "Case "<< t << ": " <<c << endl;
		t++;

	}

	return 0;
}
