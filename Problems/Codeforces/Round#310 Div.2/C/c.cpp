#include <bits/stdc++.h>
#include <iostream>
using namespace std;


int main() {
	
	int n, k;
	cin >> n >> k;
	vector<vector<int>> c(k,vector<int>());
	for(int i = 0; i < k; i++) {
		int m;
		cin >> m;
		for(int j = 0; j < m; j++) {
			int matri;
			cin >> matri;
			c[i].push_back(matri);
		}
	}

	vector<int> p(k,0);
	int time = 0;
	int one_chain = 0;
	for(int i = 0; i < k; i++) {
		if(c[i][0] == 1) {
			for(int j = 0; j < c[i].size()-1; j++) {
				if(c[i][j+1] - c[i][j] == 1)
					one_chain++;
				else
					break;
			}
			time += c[i].size() - 1 - one_chain; 
		}
		else
			time += c[i].size() - 1;
	}

	for(int i = 0; i < k; i++) {
		if(c[i][0] == 1) {
			time += c[i].size() - 1 - one_chain;
		}
		else
			time += c[i].size();
	}

	cout << time << endl;

}
