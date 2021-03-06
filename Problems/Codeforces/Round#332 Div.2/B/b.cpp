#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main() {

	int n, m; cin >> n >> m;
	vector<int> f(n), b(m);
	for(int i = 0; i < n; i++)
		cin >> f[i];	
	for(int i = 0; i < m; i++)
		cin >> b[i];

	map<int,vector<int>> pos;
	for(int i = 0; i < n; i++)
		pos[f[i]].push_back(i);

	vector<int> a(m);
	bool ambiguity = false;
	for(int i = 0; i < m; i++) {
		int size = pos[b[i]].size();
		if(size == 1)
			a[i] = (pos[b[i]][0]+1);
		else if(size > 1)
			ambiguity = true;
		else {
			cout << "Impossible" << endl;
			return 0;
		}
	}

	if(ambiguity)
		cout << "Ambiguity" << endl;
	else {
		cout << "Possible" << endl;
		cout << a[0];
		for(int i = 1; i < m; i++)
			cout << " " << a[i];
		cout << endl;
	}

	return 0;
}
