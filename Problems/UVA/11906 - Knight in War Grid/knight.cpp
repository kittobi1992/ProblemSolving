#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <climits>
using namespace std;

typedef vector<vector<int>> graph;
typedef pair<int,int> point;

int r, c, m, n, w;
graph g, visited;
int even, odd;

bool isEnableField(int x, int y) {
	if(x < 0 || x >= r || y < 0 || y >= c || g[x][y] == -1)
		return false;
	return true;
}

set<point> connectedFields(int x, int y) {
	set<point> fields;

	if(isEnableField(x+m,y+n))
		fields.insert(make_pair(x+m,y+n));
	if(isEnableField(x+m,y-n))
		fields.insert(make_pair(x+m,y-n));
	if(isEnableField(x-m,y+n))
		fields.insert(make_pair(x-m,y+n));
	if(isEnableField(x-m,y-n))
		fields.insert(make_pair(x-m,y-n));
	if(isEnableField(x+n,y+m))
		fields.insert(make_pair(x+n,y+m));
	if(isEnableField(x+n,y-m))
		fields.insert(make_pair(x+n,y-m));
	if(isEnableField(x-n,y+m))
		fields.insert(make_pair(x-n,y+m));
	if(isEnableField(x-n,y-m))
		fields.insert(make_pair(x-n,y-m));
		
	return fields;
}

void bfs() {

	queue<point> q;
	q.push(make_pair(0,0));
	visited[0][0] = 1;
	while(!q.empty()) {
		point p = q.front(); q.pop();
		if(g[p.first][p.second] % 2 == 0)
			even++;
		else
			odd++;
		set<point> neighbour = connectedFields(p.first,p.second);
		for(point n : neighbour) {
			if(!visited[n.first][n.second]) {
				q.push(n);
				visited[n.first][n.second] = 1;
			}
		}
	}

}

int main() {
	
	int test; cin >> test;
	int a = 1;
	while(test--) {
		cin >> r >> c >> m >> n >> w;
		g.assign(r, vector<int>(c,0));
		visited.assign(r, vector<int>(c,0));

		for(int i = 0; i < w; i++) {
			int x, y; cin >> x >> y;
			g[x][y] = -1;
		}

		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				if(g[i][j] != -1)
					g[i][j] = connectedFields(i,j).size();
			}
		}
		
		even = 0; odd = 0;
		bfs();
		cout << "Case " << a << ": " << even << " " << odd << endl;
		a++;

	}

}
