#include <bits/stdc++.h>
#include <iostream>
using namespace std;

string insertPhoto(char a, string& s, int k) {
	string sn;
	for(int i = 0; i < s.size(); i++) {
		if(i == k) {
			sn.push_back(a);
		}
		sn.push_back(s[i]);
	}
	if(k == s.size())
		sn.push_back(a);
	return sn;
}

int main() {
	
	string s;
	cin >> s;
	set<string> photo;
	for(int i = 0; i < s.size()+1; i++) {
		for(int j = 0; j < 26; j++) {
			photo.insert(insertPhoto(((char)(j+'a')),s,i));
		}
	}
	
	cout << photo.size() << endl;

}
