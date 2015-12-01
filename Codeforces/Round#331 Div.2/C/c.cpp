#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef pair<int,int> point;

int main() {

	int n; cin >> n;
	vector<point> p(n);
	vector<int> w(n);
	
	for(int i = 0; i < n; i++) {
		cin >> p[i].first >> p[i].second;
	}	

	for(int i = 0; i < n; i++)
		cin >> w[i];

	unordered_map<int,int> c;
	unordered_map<int,vector<int>> wpos;
	unordered_map<int,vector<point>> wv;
	
	for(int i = 0; i < n; i++) {
		int s = p[i].second - p[i].first;
		c[w[i]]++;
		wv[s].push_back(p[i]);
		wpos[w[i]].push_back(i);
	}

	vector<point> ast(n);
	for(auto v : c) {
		int key = v.first, value = v.second;
		if(wv[key].size() != value) {
			std::cout << "NO" << endl;
			return 0;
		}
		sort(wv[key].begin(),wv[key].end(), [&](const point& p1, const point& p2) {
			if(p1.first < p2.first)
				return true;
			else if(p1.first == p2.first)
				return p1.second < p2.second;
			else
				return false;
		});
		for(int i = 0; i < value; i++) {
			ast[wpos[key][i]] = wv[key][i];
		}
	}

	for(int i = 0; i < n-1; i++) {
		if(ast[i].first >= ast[i+1].first && ast[i].second >= ast[i+1].second) {
			cout << "NO" << endl;
			return 0;
		}
	}

	cout << "YES" << endl;
	for(int i = 0; i < ast.size(); i++) {
		cout << ast[i].first << " " <<  ast[i].second << endl; 
	}

	
		

	return 0;

}
