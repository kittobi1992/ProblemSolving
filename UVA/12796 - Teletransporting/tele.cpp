#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define mod 10000

typedef vector<vector<int>> Graph;

Graph graph;

Graph matrixMul(const Graph& g1, const Graph& g2) {
	Graph g(g1.size(),vector<int>(g1.size(),0));
	for(int i = 0; i < g1.size(); i++) {
		for(int j = 0; j < g1.size(); j++) {
			for(int k = 0; k < g1.size(); k++) {
				g[i][j] = (g[i][j] + ((g1[i][k]*g2[k][j]) % mod)) % mod;
			}
		}
	}
	return g;
}

Graph matrixPow(const Graph& g, int l) {
	if(l == 1) {
		return g;
	}
	if(l % 2 == 0) {
		return matrixPow(matrixMul(g,g),l/2);
	}
	else {
		return matrixMul(matrixPow(matrixMul(g,g),(l-1)/2),g);
	}
}

void printGraph() {
	for(int i = 0; i < graph.size(); i++) {
		for(int j = 0; j < graph.size(); j++) {
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	
	int n, l;
	while(cin >> n >> l) {
		int s, t;
		cin >> s >> t;
		s--; t--;
		graph.assign(n,vector<int>(n,0));
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < 4; j++) {
				int tmp;
				cin >> tmp; tmp--;
				graph[i][tmp]++;
			}			
		}

		Graph l_graph;
		if(l == 0) {
			l_graph.assign(n,vector<int>(n,0));
			for(int i = 0; i < graph.size(); i++) {
				l_graph[i][i] = 1;
			}
		}
		else {
			l_graph = matrixPow(graph,l);
		}


		cout << (l_graph[s][t] % mod) << endl;

	}

	return 0;
}
