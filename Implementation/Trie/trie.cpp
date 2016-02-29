#include <bits/stdc++.h>

using namespace std;

#define SIGMA 256
#define OFFSET 0

struct node {
  node() : child(SIGMA,nullptr), eow(false), id(), child_set() { }
  
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
  vector<int> id;
  set<char> child_set;
};

class Trie {

public:
  Trie(vector<string>& doc) : doc(doc) {
      root = new node();
      buildTrie();
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
  
  vector<int> getSortedRanks() {
    vector<int> ranks(doc.size());
    int cur_rank = 0;
    recursiveRank(root,ranks,cur_rank);
    return ranks;
  }
    
private:
  
  void recursiveRank(node *cur_node, vector<int>& ranks, int& cur_rank) {
    if(cur_node->eow) {
      for(int id : cur_node->id)
	ranks[id] = cur_rank;
      cur_rank++;
    }
    for(char next_node : cur_node->child_set)
      recursiveRank(cur_node->getChild(next_node),ranks,cur_rank);
  }
  
  void buildTrie() {
    for(int i = 0; i < doc.size(); i++) {
      node *cur_node = root;
      for(int j = 0; j < doc[i].size(); j++) {
	cur_node = cur_node->addChild(doc[i][j]);
      }
      cur_node->eow = true;
      cur_node->id.push_back(i);
    }
  }
  
  vector<string> doc;
  node *root;
};

/*int main() {
  vector<string> doc = {"aba", "abcba", "aba", "abb", "$"};
  Trie trie(doc);
  
  vector<int> ranks = trie.getSortedRanks();
  for(int i = 0; i < ranks.size(); i++)
    cout << ranks[i] << " ";
  cout << endl;
  
  return 0;
}*/
