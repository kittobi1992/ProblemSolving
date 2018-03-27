#include <bits/stdc++.h>

using namespace std;

int n;
string s;

void swap(char& c) {
	if(c == '0')
		c = '1';
	else
		c = '0';
}

int size_longest_alternating_subsequence(char& c) {
	int length = 0;
	for(int i = 0; i < n; i++) {
		if(s[i] == c) {
			length++;
			swap(c);
		}
	}
	return length;
}

int main() {
	 cin >> n; cin >> s;

	char c = '0';
	int l1 = size_longest_alternating_subsequence(c);
	c = '1';
	int l2 = size_longest_alternating_subsequence(c);
	
	cout << min(n,max(l1,l2)+2) << endl;	

	return 0;
}
