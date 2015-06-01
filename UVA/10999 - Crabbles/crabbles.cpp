#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

typedef pair<int,int> ii;
#define INVALID INT_MIN

struct node {
	node *(e) [26];
	int c = 0;
	node () { for(int i = 0; i < 26; i++) e[i] = NULL; }
};

void insert (node *root , string *txt , int s) {
	if(s >= txt -> length ()) 
		root ->c++;
	else {
		int idx = (int)((*txt).at(s)-'a');
		if(root->e[idx] == NULL) {
			root->e[idx] = new node();
		}
		insert (root->e[idx], txt , s+1);
	}
}

int getMaxTileIndex(int c, vector<ii>& tiles, vector<bool>& in_use) {
	int max = INVALID;
	int index = INVALID;
	for(int i = 0; i < tiles.size(); i++) {
		if(!in_use[i] && tiles[i].first == c && tiles[i].second > max) {
			max = tiles[i].second;
			index = i;
		} 
	}
	return index;
}

void findMaxScore(int& current_score, int& max_score, node *root, vector<ii>& tiles, vector<bool>& in_use) {
	if(root->c && current_score > max_score) {
		max_score = current_score;
	}	
	int possible_score = 0;
	for(int i = 0; i < tiles.size(); i++) {
		if(!in_use[i]) {
			possible_score += tiles[i].second;
		}
	}
	if(possible_score + current_score > max_score) {
		for(int i = 0; i < 26; i++) {
			if(root->e[i] != NULL) {
				int tile = getMaxTileIndex(i,tiles,in_use);
				if(tile != INVALID) {
					int score = tiles[tile].second;
					current_score += score;
					in_use[tile] = true;
					findMaxScore(current_score,max_score,root->e[i],tiles,in_use);
					in_use[tile] = false;
					current_score -= score;
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	
	int n;
	cin >> n;
	node *root = new node();
	for(int i = 0; i < n; i++) {
		string s;
		cin >> s;
		if(s.size() <= 10)
			insert(root,&s,0);
	}

	int m;
	cin >> m;
	for(int i = 0; i < m; i++) {
		int p; 
		cin >> p;
		vector<ii> tiles(p);
		vector<bool> in_use(p,false);
		for(int j = 0; j < p; j++) {
			char b; int v;
			cin >> b >> v;
			int idx = b - 'a';
			tiles[j] = ii(idx,v);
		}
		int max_score = 0;
		int current_score = 0;
		findMaxScore(current_score,max_score,root,tiles,in_use);
		cout << max_score << endl;
	}
	
 
	return 0;
}
