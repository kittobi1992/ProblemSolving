#include <bits/stdc++.h>
#include <iostream>
#include <map>

using namespace std;


int main() {

	vector<vector<int> > score(2000);
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		score[a-1].push_back(i);
	}

	int c = 1;
	vector<int> place(n,0);
	for(int i = 1999; i >= 0;i--) {
		if(score[i].size() != 0) {
			for(int j = 0; j < score[i].size(); j++) {
				place[score[i][j]] = c;
			} 
			c += score[i].size();
		}
	}

	for(int i = 0; i < place.size()-1; i++) {
		cout << place[i] << " ";
	}
	cout << place[place.size()-1] << endl;

	return 0;
}
