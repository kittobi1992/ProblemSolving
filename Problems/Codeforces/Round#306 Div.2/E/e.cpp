#include <bits/stdc++.h>
#include <iostream>

using namespace std;


int main() {

	int n; 
	cin >> n;
	vector<char> a(n,'0');
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}

	if(a[a.size()-1] != '0') {
		cout << "NO" << endl;
		return 0;
	}
	if(a.size() > 1) {
		if(a[a.size()-1] == '0' && a[a.size()-2] == '0') {
			bool only_one = true;
			for(int i = a.size()-3; i >= 0; i--) {
				only_one = only_one && (a[i] == '1');
			}
			if(only_one) {
				cout << "NO" << endl;
				return 0;
			}
		}
	}

	string b;
	b.push_back('0');
	
	queue<char> q;
	int c = 0;
	for(int i = a.size()-2; i >= 0; i--) {
		if(a[i] == '0' && c == 0 && i != 0) {
			q.push('>');
			q.push('-');
			q.push(')');
			q.push(')');
			q.push('0');
			c++;			
		}
		else if(a[i] == '0' && c == 1) {
			q.push('(');
			q.push('>');
			q.push('-');
			q.push('0');
			q.push('(');
			while(!q.empty()) {
				char z = q.front(); q.pop();
				b.push_back(z);
			}
			c = 0;
		} else if(a[i] == '0' && i == 0) {
			q.push('>');
			q.push('-');
			q.push('0');
		} else if(a[i] == '1' && i == 0) {
			q.push('>');
			q.push('-');
			q.push('1');
			if(c == 1) {
				q.push('(');
				q.push('(');
			}
		}else {
			q.push('>');
			q.push('-');
			q.push('1');
		}
	}

	while(!q.empty()) {
		char z = q.front(); q.pop();
		b.push_back(z);
	}

	reverse(b.begin(),b.end());
	cout << "YES" << endl;
	cout << b << endl;

	return 0;
}
