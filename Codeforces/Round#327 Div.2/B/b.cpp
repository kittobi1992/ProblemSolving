#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;

int main() {

	int n, m;
	cin >> n >> m;
	string s; cin >> s;
	
	map<char,char> c;
	for(int i = 0; i < 26; i++) {
		char t = ((char) (i + 'a'));
		c[t] = t;
	}

	for(int i = 0; i < m; i++) {
		char c1, c2;
		cin >> c1 >> c2;
		for(int j = 0; j < 26; j++) {
			char t = ((char) (j + 'a'));
			if(c[t] == c1) {
				c[t] = c2;
			} else if(c[t] == c2) {
				c[t] = c1;
			}
		}
	}

	for(int i = 0; i < n; i++) {
		cout << c[s[i]];
	}
	cout << endl;
	
	
	return 0;

}
