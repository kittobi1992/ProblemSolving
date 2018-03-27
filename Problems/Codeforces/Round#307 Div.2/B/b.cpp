#include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <climits>

using namespace std;

int word_count(map<char,int>& count, map<char,int>& count_w) {
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
	map<char,int> count_b;
	for(int i = 0; i < b.size(); i++) {
		count_b[b[i]]++;
	}
	map<char,int> count_c;
	for(int i = 0; i < c.size(); i++) {
		count_c[c[i]]++;
	}

	
	int best = -1;
	int bw1 = -1;
	int bw2 = -1;
	int n = a.size();
	string tmp = "";
	map<char,int> tmp_count_a(count_a);
	for(int i = 0; i < n; i++) {
		int cb = word_count(tmp_count_a,count_b);
		if(cb + i > best) {
			best = cb + i;
			bw1 = cb;
			bw2 = i;
		}
		int cc = word_count(tmp_count_a,count_c);
		if(cc == 0)
			break;
		addWord(1,tmp,c,tmp_count_a);
	}


	string k;	
	addWord(bw1,k,b,count_a);
	addWord(bw2,k,c,count_a);
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
