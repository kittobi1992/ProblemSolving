#include <bits/stdc++.h>

using namespace std;

#define SIGMA 2
#define OFFSET '0'
#define MAXLOG 18

struct node {
    node() : child(SIGMA,nullptr), eow(0), id() { }
    
    node * getChild(char c) {
        return child[c-OFFSET];
    }
    
    node * addChild(char c) {
        if(!child[c - OFFSET]) {
            child[c-OFFSET] = new node(); 
        }
        return child[c-OFFSET];
    }
    
    vector<node*> child;
    int eow;
    vector<int> id;
};

class Trie {
    
public:
    Trie() {
        root = new node();
    }
    
    int findPattern(string& q) {
        node *cur_node = root;
        for(int i = 0; i < q.size() && cur_node; i++) {
            cur_node = cur_node->getChild(q[i]);
            if(!cur_node) return 0;
        }
        return cur_node->eow;
    }
    
    void insert(string& s) {
        node *cur_node = root;
        for(int j = 0; j < s.size(); j++) {
            cur_node = cur_node->addChild(s[j]);
        }
        cur_node->eow++;
    }
    
    void remove(string& s) {
        node *cur_node = root;
        for(int i = 0; i < s.size(); i++) {
            cur_node = cur_node->getChild(s[i]);
            if(!cur_node) return; 
        }
        cur_node->eow--;
    }
    
    
private:
    node *root;
};


string getPattern(string& s) {
    string pattern(MAXLOG,'0');
    int n = s.size();
    int start_idx = MAXLOG-n;
    for(int i = start_idx; i < MAXLOG; ++i) {
        pattern[i] = ((char) (((s[i-start_idx]-OFFSET) % 2) + OFFSET));
    }
    return pattern;
}

int main() {
  
    int t; cin >> t;
    Trie trie;
    
    for(int i = 0; i < t; ++i) {
        char op; string s;
        cin >> op >> s;
        string pattern = getPattern(s);
        switch(op) {
            case '+': trie.insert(pattern);
                      break;
            case '-': trie.remove(pattern);
                      break;
            default:  cout << trie.findPattern(pattern) << endl;
        }
    }
    
	return 0;
}
