#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

typedef pair<int,int> ii;
typedef vector<vector<ii>> Graph;
#define INF INT_MAX 

vector<int> bfs(Graph adjlist, int s, int t) {
	int NUM_VERTICES = adjlist.size();
	vector<ii> parent(NUM_VERTICES,ii(-1,-1));
	
	queue<int> bfs;
	vector<bool> in_queue(NUM_VERTICES,false);
	bfs.push(s);
	in_queue[s] = true;
	while(!bfs.empty()) {
		int node = bfs.front(); bfs.pop();
		for(int i = 0; i < adjlist[node].size(); i++) {
			ii nextNode = adjlist[node][i];
			if(!in_queue[nextNode.first]) {
				parent[nextNode.first] = ii(node,nextNode.second);
				bfs.push(nextNode.first);
				in_queue[nextNode.first] = true;
			}
		}		
	}
	

	vector<int> weights;
	ii node = ii(t,0);
	while(parent[node.first].first != -1) {
		weights.push_back(parent[node.first].second);
		node = parent[node.first];
	}
	reverse(weights.begin(),weights.end());
	return weights;
}

int main() {
	
	int test;
	cin >> test;
	while(test--) {
		int n, m;
		cin >> n >> m;
		Graph adjlist(n,vector<ii>());
		for(int i = 0; i < m; i++) {
			int n1, n2, c;
			cin >> n1 >> n2 >> c;
			n1--; n2--;
			adjlist[n1].push_back(ii(n2,c));
			adjlist[n2].push_back(ii(n1,c));
		}
		int k;
		cin >> k;
		for(int i = 0; i < k; i++) {
			int s, t, c;
			cin >> s >> t >> c;
			s--; t--;
			vector<int> path = bfs(adjlist,s,t);
			int min_cost = 0;
			for(int i = 0; i < path.size(); i++) {
				min_cost += path[i];
			}
			vector<int> dp(c+1,INF);
			if(min_cost <= c) {
				dp[min_cost] = path.size();
				for(int j = min_cost + 1; j < c+1; j++) {
					for(int p = 0; p < max(0,((int)path.size()-1)); p++) {
						if(j - 2*path[p] >= 0 && dp[j - 2*path[p]] != INF) {
							dp[j] = min(dp[j], dp[j - 2*path[p]] + 2);
						}
					}
				}
			}
			
			if(dp[c] != INF) 
				cout << "Yes " << dp[c] << endl;
			else
				cout << "No" << endl;
		}

		if(test != 0)
			cout << endl;

	}

	return 0;
}
