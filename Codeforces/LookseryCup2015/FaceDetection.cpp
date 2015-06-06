#include <bits/stdc++.h>
#include <iostream>
#include <map>

using namespace std;


int main() {

	int n, m;
	cin >> n >> m;
	vector<string> img;
	for(int i = 0; i < n; i++) {
		string line;
		cin >> line;
		img.push_back(line);
	}

	int count = 0;
	for(int i = 0; i < n-1; i++) {
		for(int j = 0; j < m-1; j++) {
			map<char,bool> ma;			
			ma[img[i][j]] = true;
			ma[img[i+1][j]] = true;
			ma[img[i][j+1]] = true;
			ma[img[i+1][j+1]] = true;
			if(ma['f'] && ma['a'] && ma['c'] && ma['e']) 
				count++; 
		}
	}

	cout << count << endl;

	return 0;
}
