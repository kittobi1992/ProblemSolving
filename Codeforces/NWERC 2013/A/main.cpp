#include <bits/stdc++.h>

using namespace std;


#define MAXN 2005
typedef pair<int,int> ii;
using graph = vector<vector<ii>>;

int N;
int adj_mat[MAXN][MAXN], mst[MAXN][MAXN];
graph mstList;


priority_queue<pair<int,ii>,vector<pair<int,ii>>,greater<pair<int,ii>> > pq;


void buildMST() {
	vector<bool> vis(N,false);
	bool take_first = false;
	
	vis[0] = true;
	for(int i = 1; i < N; ++i) pq.push({adj_mat[0][i],{0,i}});
	
	ii add_edge = make_pair(0,0);
	int add_cost = INT_MAX;
	
	while(!pq.empty()) {
		auto cur = pq.top(); pq.pop();
		int c = cur.first; int u = cur.second.first, v = cur.second.second;
		if(vis[u] == vis[v])
			continue;
		mstList[u].push_back(make_pair(v,c)); mstList[v].push_back(make_pair(u,c));
		vis[v] = true; 
		for(int i = 0; i < N; ++i) {
			if(v != i) pq.push({adj_mat[v][i],{v,i}});
		}
	}
}

void dfs(int root, int cur, int dist) {
	if(mst[root][cur] != INT_MAX) return;
	mst[root][cur] = dist;
	for(int i = 0; i < mstList[cur].size(); ++i) {
		int v = mstList[cur][i].first;
		dfs(root,v,dist + mstList[cur][i].second);	
	}
}


int main() {
  
	ios::sync_with_stdio(false);
	
	while(cin >> N) {
		mstList.assign(N,vector<ii>());
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) { cin >> adj_mat[i][j]; mst[i][j] = INT_MAX; }
		}
		
		buildMST();
		
		for(int i = 0; i < N; ++i) {
			for(int j = i+1; j < N; ++j) {
				if(mst[i][j] != INT_MAX) cout << (i+1) << " " << (j+1) << " " << mst[i][j] << endl; 
			}
		}
		
		for(int i = 0; i < N; ++i) dfs(i,i,0);
		
		/*for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				cout << mst[i][j] << "(" << adj_mat[i][j] << ") ";
			}
			cout << endl;
		}*/
		
		int cheapest = INT_MAX; int s = 0, t = N-1; bool found = false;
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				if(i != j && mst[i][j] > adj_mat[i][j] && adj_mat[i][j] < cheapest) {
					cheapest = adj_mat[i][j]; s = i; t = j;
				}
			}
		}
		if(cheapest == INT_MAX) cheapest = 1000000;
		
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < mstList[i].size(); ++j) {
				int u = i, v = mstList[i][j].first, c = mstList[i][j].second;
				if(mst[u][v] == c) {
					cout << (u+1) << " " << (v+1) << " " << c << endl;
					mst[u][v] = INT_MAX; mst[v][u] = INT_MAX;
				}
			}
		}
		
		cout << (s+1) << " " << (t+1) << " " << cheapest << endl;
		
		cout << endl;
		
	}
	
  	return 0;
}
