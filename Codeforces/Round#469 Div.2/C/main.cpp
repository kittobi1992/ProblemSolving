#include <bits/stdc++.h>

using namespace std;


int main() {

	string s; cin >> s;
	vector<vector<int>> l;

	queue<int> q0, q1;
	for(int i = 0; i < s.size(); ++i) {
		if(s[i] == '0') {
			if(q1.size() != 0) {
				int idx = q1.front(); q1.pop();
				l[idx].push_back(i+1);
				q0.push(idx);
			} else {
				l.emplace_back();
				int idx = l.size() - 1;
				l[idx].push_back(i+1);
				q0.push(idx);
			}
		} else {
			if(q0.size() != 0) {
				int idx = q0.front(); q0.pop();
				l[idx].push_back(i+1);
				q1.push(idx);
			} else {
				cout << "-1" << endl;
				return 0;
			}
		}
	}

	if(q1.size() == 0) {
		cout << l.size() << endl;
		for(int i = 0; i < l.size(); ++i) {
			cout << l[i].size() << " ";
			for(int j = 0; j < l[i].size(); ++j) {
				cout << l[i][j] << (j == l[i].size() - 1 ? "\n" : " ");
			}
		}
	} else {
		cout << "-1" << endl;
	}
    
	return 0;
}
