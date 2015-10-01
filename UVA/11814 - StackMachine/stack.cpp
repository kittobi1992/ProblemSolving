#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef vector<vector<int>> graph;

int main() {
	int test;
	cin >> test;

	while(test--) {
		int n, m, q;
		cin >> n >> m >> q;
		graph out(n,vector<int>());
		graph c(n,vector<int>());
		for(int i = 0; i < m; i++) {
			int a, b, z;
			cin >> a >> b >> z;
			--a; --b;
			out[a].push_back(b);
			c[a].push_back(z);
		}

		graph sol(n, vector<int>(n,INT_MAX));
		//Initialization with Path of length 2
		for(int from = 0; from < n; from++) {
			for(int i = 0; i < out[from].size(); i++) {
				int to = out[from][i];
				for(int j = 0; j < out[to].size(); j++) {
					int toto = out[to][j];
					if(c[from][to] > 0 && c[from][to] == -c[to][toto]) {
						sol[from][toto] = 2;
					}
				}
			}
		}
		bool converged = false;
		while(!converged) {

			//Path-Concatenation
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					for(int k = 0; k < n; k++) {
						if(sol[i][k] != INT_MAX && sol[k][j] != INT_MAX) {
							sol[i][j] = min(sol[i][k] + sol[k][j], sol[i][j]);
						}
					}
				}
			}

			//Path-Expansion
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					if(sol[i][j] )
				}
			}

		}

		for(int i = 0; i < q; i++) {
			int x, y;
			cin >> x >> y;
			--x; --y;
			if(sol[x][y] == INT_MAX) {
				cout << "impossible" << endl;
			}
			else {
				cout << sol[x][y] << endl;
			}
		}
		
	}
}
