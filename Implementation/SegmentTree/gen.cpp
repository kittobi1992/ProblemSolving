#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;



int main() {

	int n = 500;
	int m = 500;
	vector<bool> visited(m,false);

	cout << n << endl;
	for(int i = 0; i < n; i++) {
		int z = rand() % m;
		if(!visited[z]) {
			cout << z << " ";
			visited[z] = true;
		}
		else
			i--;
	}


	return 0;
}
