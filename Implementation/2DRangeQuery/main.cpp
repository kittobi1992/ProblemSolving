#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef pair<int,int> point;

#define N 10

point data[N];
int n; 

struct node {
  int x;
  node *left, *right;
  vector<point> yRange;
  
  node(point &p) : x(p.first), left(nullptr), right(nullptr), yRange() { }
  
  void printNode() {
    cout << "Node: " << x << ", Left: " << (left ? left->x : -1) << ", Right: "
	 << (right ? right->x : -1) << endl;
    cout << "yRange: ";
    for(int i = 0; i < yRange.size(); ++i)
      cout << "(" << yRange[i].first << ","<<yRange[i].second<<")" << ((i == yRange.size()-1) ? "" : " ");
    cout << endl;
    cout << "-------------------" << endl;
  }
  
  bool isLeaf() {
    return !left && !right;
  }
  
};

node *root;

node * createNode(point &p, bool isLeaf = false) {
  node *no = new node(p);
  if(isLeaf)
    no->yRange.push_back({p.second,p.first});
  return no;
}


node * build2DRangeTreeRecursive(int i, int j) {
  if(j-i < 0) return nullptr;
  else if(j - i == 0) { node *cur = createNode(data[i],true); return cur; }

  int m = (i+j)/2;
  node *cur = createNode(data[m]);
  cur->left = build2DRangeTreeRecursive(i,m);
  cur->right = build2DRangeTreeRecursive(m+1,j);
  
  vector<point> dummy;
  if(cur->left && cur->right)
    merge(cur->left->yRange.begin(),cur->left->yRange.end(),cur->right->yRange.begin(),
	  cur->right->yRange.end(),back_inserter(cur->yRange));
  else if(cur->left && !cur->right)
    cur->yRange.insert(cur->yRange.end(),cur->left->yRange.begin(),cur->left->yRange.end());
  else if(!cur->left && cur->right)
    cur->yRange.insert(cur->yRange.end(),cur->right->yRange.begin(),cur->right->yRange.end());
  
  return cur;
}

void rangeSearch1D(vector<point> &res, vector<point> &y, int y1, int y2) {
  point search_point = make_pair(y1,0);
  auto cur = lower_bound(y.begin(),y.end(),search_point);
  while(cur->first <= y2 && cur != y.end()) {
    res.emplace_back(cur->second,cur->first);
    cur++;
  }
}

void rangeSearch2DRecursive(vector<point> &res, node *cur, int x1, int x2, int y1, int y2) {
    //cur is split node
    if(x1 <= cur->x && x2 > cur->x) {
      
	if(cur->isLeaf()) {
	  rangeSearch1D(res,cur->yRange,y1,y2);
	}
	else {
	  //Inspect left subtree
	  node *v = cur->left;
	  while(!v->isLeaf() && v) {
	    if(x1 <= v->x) {
	      rangeSearch1D(res,v->right->yRange,y1,y2);
	      v = v->left;
	    }
	    else v = v->right;
	  }
	  if(v && x1 <= v->x) rangeSearch1D(res,v->yRange,y1,y2);
	  
	  //Inspect right subtree
	  v = cur->right;
	  while(!v->isLeaf() && v) {
	    if(x2 >= v->x) {
	      rangeSearch1D(res,v->left->yRange,y1,y2);
	      v = v->right;
	    }
	    else v = v->left;
	  }
	  if(v && x2 >= v->x) rangeSearch1D(res,v->yRange,y1,y2);  
	}
	
    }
    else if(x2 <= cur->x) rangeSearch2DRecursive(res,cur->left,x1,x2,y1,y2);
    else if(x1 > cur->x) rangeSearch2DRecursive(res,cur->right,x1,x2,y1,y2);
      
}

vector<point> rangeSearch2D(int x1, int x2, int y1, int y2) {
  vector<point> res;
  rangeSearch2DRecursive(res,root,x1,x2,y1,y2);
  return res;
}


node * build2DRangeTree() {
   sort(data,data+n);
   return build2DRangeTreeRecursive(0,n-1);
}

void printTree(node *cur) {
  if(cur) {
    cur->printNode();
    printTree(cur->left);
    printTree(cur->right);
  }
}

int main() {
  
  memset(data,0,sizeof(point)*N);
  cin >> n;
  for(int i = 0; i < n; ++i)
    cin >> data[i].first >> data[i].second;
  
  root = build2DRangeTree();
  for(int i = 0; i < n; ++i)
    cout << i << " -> " << data[i].first << " " << data[i].second << endl;
  
  printTree(root);
  
  //TODO: Verification with naive algorithm on big data sets
  vector<point> res = rangeSearch2D(3,9,10,15);
  for(int i = 0; i < res.size(); ++i)
    cout << i << ": ("<< res[i].first << " " << res[i].second << ")"<< endl;
  cout << "-------------" << endl;
  res = rangeSearch2D(0,20,0,20);
  for(int i = 0; i < res.size(); ++i)
    cout << i << ": ("<< res[i].first << " " << res[i].second << ")"<< endl;
  cout << "-------------" << endl;
  res = rangeSearch2D(15,20,0,20);
  for(int i = 0; i < res.size(); ++i)
    cout << i << ": ("<< res[i].first << " " << res[i].second << ")"<< endl;
  
  //TODO: Memory access error for this test case
  /*cout << "-------------" << endl;
  res = rangeSearch2D(20,20,0,20);
  for(int i = 0; i < res.size(); ++i)
    cout << i << ": ("<< res[i].first << " " << res[i].second << ")"<< endl;*/
  
  return 0;
}
