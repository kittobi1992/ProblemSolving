#include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <climits>

using namespace std;

int word_count(map<char,int>& count, string& word) {
	map<char,int> count_w;
	for(int i = 0; i < word.size(); i++) {
		count_w[word[i]]++;
	}
	int min = INT_MAX;
	for(int i = 0; i < 30; i++) {
		char c = ((char) (i + 'a'));
		if(count_w[c] != 0) {
			int max = count[c] / count_w[c];
			if(max < min)
				min = max;
		}
	}
	return min;
}

void addWord(int n, string& k, string& word, map<char,int>& count) {
	for(int i = 0; i < n; i++) {
		k += word;
	}
	for(int i = 0; i < word.size(); i++) {
		count[word[i]] -= n;
	}
}

int main() {

	string a, b, c;
	cin >> a >> b >> c;
	map<char,int> count_a;
	for(int i = 0; i < a.size(); i++) {
		count_a[a[i]]++;
	}

	string k;
	int b_count = word_count(count_a,b);
	int c_count = word_count(count_a,c);
	if(b_count >= c_count) {
		addWord(b_count,k,b,count_a);
		c_count = word_count(count_a,c);
		addWord(c_count,k,c,count_a);
	}
	else {
		addWord(c_count,k,c,count_a);
		b_count = word_count(count_a,b);
		addWord(b_count,k,b,count_a);
	}

	
	for(int i = 0; i < 30; i++) {
		char c = ((char) (i + 'a'));
		if(count_a[c] > 0) {
			for(int j = 0; j < count_a[c]; j++) {
				k.push_back(c);
			}
		}
	}

	cout << k << endl;

	return 0;
}
