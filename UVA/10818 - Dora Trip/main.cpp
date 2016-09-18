#include <bits/stdc++.h>

using namespace std;

using point = pair<int,int>;
#define x first
#define y second

int r, c, n;
vector<string> m;
point start;
vector<point> v;

vector<char> dir {'E','N','S','W'};
vector<point> p_dir {make_pair(0,1),make_pair(-1,0),make_pair(1,0),make_pair(0,-1)};

vector<vector<string>> adj_matrix;
vector<vector<int>> vis; int t = 1;

int res = INT_MAX; string res_way = "";

point operator+(const point& p1, const point& p2) {
	return make_pair(p1.x+p2.x,p1.y+p2.y);	
}

point goDirection(const point& p, int d) {
	return p + p_dir[d];
}

string bfs(const point& p1, const point& p2) {
	string way = "-1";

	//cout << "Start: (" << p1.x << "," << p1.y << ") Ziel: ("<< p2.x << ","<<p2.y<<")" <<endl;
	
	queue<pair<point,string>> q;
	q.push(make_pair(p1,"")); vis[p1.x][p1.y] = t;
	while(!q.empty()) {
		point cur_p = q.front().first; string cur_way = q.front().second; q.pop();
		
		//cout << cur_p.x << " " << cur_p.y << " -> " << cur_way << endl;
		
		if(cur_p == p2) { t++; return cur_way; }
		
		for(int i = 0; i < 4; ++i) {
			point new_p = goDirection(cur_p,i);
			//cout << new_p.x << " " << new_p.y << " m = " << m[new_p.x][new_p.y] << ", v = " << vis[new_p.x][new_p.y] << ", t =" << t << endl; 
			if(vis[new_p.x][new_p.y] < t) {
				cur_way.push_back(dir[i]);
				if(m[new_p.x][new_p.y] == ' ' || m[new_p.x][new_p.y] == 'S' || m[new_p.x][new_p.y] == '*') {
					q.push(make_pair(new_p,cur_way));
				}
				vis[new_p.x][new_p.y] = t;
				cur_way.pop_back();
			}
		}	
	}
	t++;
	return way;	
}

string reverseWay(string& way) {
	string tmp(way); reverse(tmp.begin(),tmp.end());	
	for(int i = 0; i < tmp.size(); ++i) {
		if(tmp[i] == 'E') tmp[i] = 'W';
		else if(tmp[i] == 'W') tmp[i] = 'E';
		else if(tmp[i] == 'N') tmp[i] = 'S';
		else if(tmp[i] == 'S') tmp[i] = 'N';
	}
	if(tmp[0] == '1') reverse(tmp.begin(),tmp.end());	
	return tmp;
}

void dfs(int cur, int cost, string cur_way, int N, vector<bool>& visited) {
	if(N == 0) {
		if(cost + adj_matrix[cur][0].size() < res) { res = cost + adj_matrix[cur][0].size(); res_way = cur_way + adj_matrix[cur][0]; }
		else if(cost + adj_matrix[cur][0].size() == res) {
			string new_way = cur_way + adj_matrix[cur][0];
			if(res_way.compare(new_way) > 0)	{ res_way = new_way; res = cost + adj_matrix[cur][0].size(); }
		}
	} else if(cost + adj_matrix[cur][0].size() > res) return;
	
	for(int i = 1; i < n; ++i) {
		if(!visited[i] && adj_matrix[cur][i] != "-1") {
			visited[i] = true;
			dfs(i,cost+adj_matrix[cur][i].size(),cur_way+adj_matrix[cur][i],N-1,visited);
			visited[i] = false;
		}
	}
}

int main() {
  
	string line;
 	while(getline(cin,line)) {
		stringstream ss(line); ss >> r >> c;
		if(r+c == 0) break;
		
		res = INT_MAX; res_way = "";
		m.resize(r); v.clear(); adj_matrix.clear(); vis.assign(r,vector<int>(c,0));
		for(int i = 0; i < r; ++i) getline(cin,m[i]);
		
		for(int i = 0; i < r; ++i) {
			for(int j = 0; j < c; ++j) {
				if(m[i][j] == '*') v.emplace_back(i,j);	
				else if(m[i][j] == 'S') start = make_pair(i,j);
			}
		}
		
		n = v.size() + 1;
		adj_matrix.assign(n, vector<string>(n,"-1"));
		for(int i = 0; i < n-1; ++i) {
			//cout << start.x << " " << start.y << " -> " << v[i].x << " " << v[i].y << endl; 
			adj_matrix[0][i+1] = bfs(start,v[i]);	
			//cout << "adj_matrix[0]["<<(i+1)<<"] = "  <<adj_matrix[0][i+1] << endl;
			adj_matrix[i+1][0] = reverseWay(adj_matrix[0][i+1]);
		}
		for(int i = 0; i < n-1; ++i) { 
			for(int j = i+1; j < n-1; ++j) {
				adj_matrix[i+1][j+1] = bfs(v[i],v[j]);	
			   adj_matrix[j+1][i+1] = reverseWay(adj_matrix[i+1][j+1]);
			}
		}
		int rp = 0;
		for(int i = 1; i < n; ++i) if(adj_matrix[0][i] != "-1") rp++;
		if(rp > 0) {
			vector<bool> visited(n,false); visited[0] = true;
			for(int i = 1; i < n; ++i) {
				if(adj_matrix[0][i] != "-1") {
					visited[i] = true;
					dfs(i,adj_matrix[0][i].size(),adj_matrix[0][i],rp-1,visited);
					visited[i] = false;
				}
			}
			cout << res_way << endl;
		}
		else {
			cout << "Stay home!" << endl;	
		}
		
	}
	
  return 0;
}
