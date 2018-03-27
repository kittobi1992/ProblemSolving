#include <bits/stdc++.h>

using namespace std;

using ii = pair<int,int>;

#define MAXN 8
#define INVALID INT_MAX/2
#define f first
#define s second

int k,N,n;
vector<int> l,h;
vector<vector<int>> config(MAXN,vector<int>(MAXN,INVALID));
vector<ii> inc_order;


void printConfig() {
	for(int i = 0; i < k; ++i) {
		for(int j = 0; j < l[i]; ++j) {
			cout << config[i][j] << " ";	
		}
		cout << endl;
	}
	cout << endl;
}

bool createStartConfig() {
	config.assign(MAXN,vector<int>(MAXN,INVALID));	
	
	for(int i = 0; i < k; ++i) {
		for(int j = 0; j < l[i]; ++j) config[i][j] = i+1;	
	}

	int x = INVALID, y = INVALID;
	for(int i = MAXN-1; i >= 0; --i) {
		if(config[0][i] != INVALID) {
			y = i;
			for(int j = 0; j < MAXN; ++j) {
				if(config[j][y] == INVALID) { x = j-1; h[y] = x; break; }	
			}
		}
		if(x != INVALID) break;
	}
	
	while(true) {
		inc_order.push_back(make_pair(x,y));	
		x--;
		if(x < 0) {
			y--;
			if(y < 0) break;
			for(int i = 0; i < MAXN; ++i) if(config[i][y] == INVALID) { x = i-1; h[y] = x; break; }
		}
	}
	
	n = inc_order.size();
	
	return config[k-1][0] <= N;
	
}

bool increment() {
	for(int i = 0; i < n; ++i) {
		int x = inc_order[i].f, y = inc_order[i].s;
		config[x][y]++;
		if(config[x][y] <= N-(h[y]-x)) {
			for(int i = y+1; i < l[x]; ++i) config[x][i] = config[x][i-1];
			for(int j = x+1; j < h[y]; ++j) config[j][y] = config[j-1][y]+1;
			return true;
		}
		else {
			config[x][y] = (y-1 >= 0) ? config[x][y-1] : x+1;	
		}
	}
	return false;
}

int main() {
	
	while(cin >> k) {
		l.assign(k,0); inc_order.clear(); int max_f = 0;
		for(int i = 0; i < k; ++i) { cin >> l[i]; max_f = max(max_f,l[i]); }
		h.assign(max_f,INVALID);
		cin >> N;
		
		if(!createStartConfig()) { cout << "0" << endl; continue; }

		//printConfig();
		int num_config = 1;
		while(increment()) { /*printConfig();*/ num_config++; }
		
		cout << num_config << endl;
	}
	
	return 0;
}
