#include <bits/stdc++.h>
#include <iostream>
using namespace std;


int control(string& s1, string& s2) {
	int dif = 0;
	for(int i = 0; i < s1.size(); i++) {
		if(s1[i] != s2[i])
			dif++;
	}
	return dif;
}

int main() {

	int n, t; cin >> n >> t;
	string s1, s2; cin >> s1 >> s2;
	string s3(n,'.');

	int cur1 = 0;
	int cur2 = 0;
	int mode = 0;
	int dif = 0;
	for(int i = 0; i < n; i++) {
		if(s1[i] != s2[i]) {
			dif++;
		}
	}

	int same = n - dif;
	int a = 0;
	for(int i = 0; i < n; i++) {
		if(t == 0 || (dif <= t && a % 2 == 0))
			break;
		if(s1[i] != s2[i]) {
			if(mode == 0) {
				s3[i] = s2[i]; cur1++; mode = 1; a++;
			} else {
				s3[i] = s1[i]; cur2++; mode = 0; t--; a++;
			}
			dif--;
		}
	}

	if(cur1 != cur2) {
		for(int i = n-1; i >= 0; i--) {
			if(s3[i] != '.') {
				if(s3[i] == s1[i])
					cur2--;
				else
					cur1--;
				s3[i] = '.'; dif++;
				break;
			}
		}
	}

	if(dif > t || dif + same < t) {
		cout << "-1" << endl;
		return 0;
	} 


		for(int i = 0; i < n; i++) {
			if(s3[i] == '.' && s1[i] != s2[i]) {
				char rc = ((char) (rand()%26 + 'a'));
				while(s1[i] == rc || s2[i] == rc)
					rc = ((char) (rand()%26 + 'a'));
				s3[i] = rc;
				t--;
			} 
		}

		for(int i = 0; i < n; i++) {
			if(s3[i] == '.' && s1[i] == s2[i]) {
				if(t == 0)
					s3[i] = s1[i];
				else {
					if(s1[i] == 'a')
						s3[i] = 'd';
					else
						s3[i] = 'a';
					t--;
				}
			}			
		}

	cout << s3 << endl;
		

	return 0;

}
