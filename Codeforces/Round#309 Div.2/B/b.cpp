#include <bits/stdc++.h>
#include <iostream>
using namespace std;


int main() {
	
	int n;
	cin >> n;
	int max = -1;
	unordered_map<string,int> c;
	for(int i = 0; i < n; i++) {
		string s;
		cin >> s;
		c[s]++;
		if(c[s] > max)
			max = c[s];
	}

	cout << max << endl;

}
