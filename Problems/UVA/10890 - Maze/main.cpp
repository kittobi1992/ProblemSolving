#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define INVALID INT_MAX
using point = pair<int,int>;

int N, T, S;
vector<point> b;
int res;
point start {0,0}, e {N-1,N-1};

int distance(point& p1, point& p2) {
	return abs(p2.x-p1.x) + abs(p2.y-p1.y);	
}

void dfs(int pos, int cost, int s, vector<bool>& vis) {
	if(s == 0) {
		res = min(res,cost+distance(b[pos],e)); return;
	} else if(cost + distance(b[pos],e) > res) return;
	
	for(int i = 0; i < T; ++i) {
		if(!vis[i]) {
			vis[i] = true;
			dfs(i,cost+distance(b[pos],b[i]),s-1,vis);
			vis[i] = false;
		}
	}
}

int main() {
  
	int test = 1;
	while(cin >> N >> T >> S) {
		if(N == 0) break;
		e = make_pair(N-1,N-1);
		res = INVALID;
		b.assign(T,make_pair(0,0));
		for(int i = 0; i < T; ++i) cin >> b[i].x >> b[i].y;
		
		vector<bool> vis(T,false);
		for(int i = 0; i < T; ++i) {
			vis[i] = true;
			dfs(i,distance(start,b[i]),S-1,vis);
			vis[i] = false;
		}
		
		cout << "Case " << test++ << ": " << res << endl; 
		
	}
	
  return 0;
}
