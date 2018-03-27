#include <bits/stdc++.h>
#include <iostream>

using namespace std;


int main() {

	string num;
	cin >> num;

	int n = num.size();

	bool found = false;
	int c = 0;
	for(int i = 0; i < n; i++) {
		for(int j = i+1; j < n; j++) {
			for(int k = j+1; k < n; k++) {
				c = (num[i]-'0')*100 + (num[j]-'0')*10 + (num[k]-'0');
				if(c % 8 == 0) {
					found = true;
					break;
				}
			}
			if(found)
				break;
		}
		if(found)
			break;
	}

	if(!found) {
		for(int i = 0; i < n; i++) {
			for(int j = i+1; j < n; j++) {
				c = (num[i]-'0')*10 + (num[j]-'0');
					if(c % 8 == 0) {
						found = true;
						break;
					}
			}
			if(found)
				break;
		}
	}

	if(!found) {
		for(int i = 0; i < n; i++) {
			c = (num[i]-'0');
			if(c % 8 == 0) {
				found = true;
				break;
			}
		}
	}

	if(found) {
		cout << "YES" << endl;
		cout << c << endl;
	}
	else
		cout << "NO" << endl;

	return 0;
}
