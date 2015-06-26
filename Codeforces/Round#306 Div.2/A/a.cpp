#include <bits/stdc++.h>
#include <iostream>
using namespace std;


int main() {
	
	string s;
	cin >> s;
	
	vector<int> pos;
	for(int i = 0; i < s.size()-1; i++) {
		if(s[i] == 'A' && s[i+1] == 'B') {
			pos.push_back(i);
		}
	}

	int b = -1;
	for(int i = s.size()-1; i > 0; i--) {
		if(s[i] == 'A' && s[i-1] == 'B') {
			for(int p : pos) {
				int i1 = min(p,i-1);
				int i2 = max(p,i-1);
				if(i2-i1 >= 2) {
					cout << "YES" << endl;
					return 0;
				}
			}
		}
	}
	cout << "NO" << endl;
	return 0;


}
