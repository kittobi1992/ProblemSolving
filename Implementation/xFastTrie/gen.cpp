#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;



int main() {

	int n = 1000000;
	int u = 1100000;
	vector<bool> visited(u,false);

	cout << n << " "<< u << endl;
	for(int i = 0; i < n; i++) {
		int z = rand() % u;
		if(!visited[z]) {
			cout << z << " ";
			visited[z] = true;
		}
		else
			i--;
	}


	return 0;
}
