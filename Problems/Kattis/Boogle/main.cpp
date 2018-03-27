#include <bits/stdc++.h>

using namespace std;

#define SIGMA 28
#define OFFSET 'A'

struct node {
    node() : child(SIGMA,nullptr), eow(false), child_set() { }
    
    node * getChild(char c) {
        return child[c-OFFSET];
    }
    
    node * addChild(char c) {
        if(!child[c - OFFSET]) {
            child[c-OFFSET] = new node(); 
            child_set.insert(c);
        }
        return child[c-OFFSET];
    }
    
    vector<node*> child;
    bool eow;
    set<char> child_set;
};

class Trie {
    
public:
    Trie() {
        root = new node();
    }
    
    bool findPattern(string& q) {
        node *cur_node = root;
        for(int i = 0; i < q.size() && cur_node; i++) {
            cur_node = cur_node->getChild(q[i]);
        }
        if(cur_node && cur_node->eow)
            return true;
        return false;
    }
    
    void buildTrie(vector<string>& dict) {
        for(int i = 0; i < dict.size(); i++) {
            node *cur_node = root;
            for(int j = 0; j < dict[i].size(); j++) {
                cur_node = cur_node->addChild(dict[i][j]);
            }
            cur_node->eow = true;
        }
    }
    node *root;
};


int N,M;
vector<string> boogle, dict;
Trie trie;
bool vis[4][4];
set<string> result;

void play(int i, int j, string q) {
    if(i < 0 || j < 0 || i > 3 || j > 3 || vis[i][j]) return;
    q += boogle[i][j];
    if(q.size() > 8) return;
    vis[i][j] = true;
    if(trie.findPattern(q)) result.insert(q);
    
    play(i-1,j,q); play(i-1,j-1,q); play(i,j-1,q); play(i+1,j-1,q);
    play(i+1,j,q); play(i+1,j+1,q); play(i,j+1,q); play(i-1,j+1,q);
    vis[i][j] = false;
}

int main() {
    
    ios::sync_with_stdio(false);
    
    cin >> N;
    dict.resize(N);
    for(int i = 0; i < N; ++i) cin >> dict[i];
    trie.buildTrie(dict);
    
    cin >> M;
    boogle.resize(4);
    for(int i = 0; i < M; ++i) {
        result.clear();
        cin >> boogle[0] >> boogle[1] >> boogle[2] >> boogle[3];
        memset(vis,0,sizeof vis);
        for(int x = 0; x < 4; ++x) {
            for(int y = 0; y <= 4; ++y) {
                string q = "";
                play(x,y,q);
            }
        }
        string longest_boogle = "";
        long long score = 0;
        for(string b : result) {
            if(b.size() > longest_boogle.size()) longest_boogle = b;
            if(b.size() == 3 || b.size() == 4) score += 1;
            else if(b.size() == 5) score += 2;
            else if(b.size() == 6) score += 3;
            else if(b.size() == 7) score += 5;
            else if(b.size() == 8) score += 11;
        }
        cout << score << " " << longest_boogle << " " << result.size() << endl;
    }
    
	return 0;
}
