#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef pair<int,int> point;

#define N 1000000
#define SEP "\n--------------------------------------"

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
    if(!cur)
      return;
  
    //cur is split node
    if(x1 <= cur->x && x2 >= cur->x) {
      
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

vector<point> naiveRangeSearch(int x1, int x2, int y1, int y2) {
  point search_point = make_pair(x1,INT_MIN);
  auto match = lower_bound(data,data+n,search_point);
  vector<point> res;
  while(match->first <= x2 && match != (data+n)) {
      if(match->first >= x1 && match->first <= x2 && match->second >= y1 && match->second <= y2)
	res.push_back(*match);
      match++;
  }
  return res;
}

double diffclock(clock_t clock1,clock_t clock2)
{
    double diffticks=clock2-clock1;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return diffms;
}

double rangeSearchTime = 0.0;
double naiveRangeSearchTime = 0.0;

bool verify(int x1, int x2, int y1, int y2) {
  cout << "Query: ("<<x1<<","<<x2<<") x ("<<y1<<","<<y2<<")"<<endl; 
  
  clock_t t0 = clock();
  vector<point> res = rangeSearch2D(x1,x2,y1,y2);
  double t1 = diffclock(t0,clock()); rangeSearchTime += t1;
  cout << "Range Search Time = " << t1 << " ms" << endl;
  
  t0 = clock();
  vector<point> naive_res = naiveRangeSearch(x1,x2,y1,y2);
  t1 = diffclock(t0,clock()); naiveRangeSearchTime += t1;
  cout << "Naive Range Search Time = " << t1 << " ms" << endl;
  
  cout << "Range Search 2D Result Size = " << res.size() << endl;
  cout << "Naive Range Search 2D Result Size = " << naive_res.size() << endl;
  if(naive_res.size() != res.size()) {
    cout << "Sizes of result vectors didn't match!" << SEP << endl; return false; }
  
  sort(res.begin(),res.end());
  auto cur_res = res.begin(); auto cur_n_res = naive_res.begin();
  while(cur_res != res.end()) {
    if(cur_res->first != cur_n_res->first || cur_res->second != cur_n_res->second) {
	cout << "Mismatch: ("<<cur_res->first << "," << cur_res->second << ") != (" 
	     << cur_n_res->first << "," << cur_n_res->second << ")" << SEP << endl;
	return false;
    }
    cur_res++; cur_n_res++;
  }
  cout << "Verify-State = OK" << SEP << endl;
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  memset(data,0,sizeof(point)*N);
  cin >> n;
  for(int i = 0; i < n; ++i)
    cin >> data[i].first >> data[i].second;
  
  clock_t t0 = clock();
  sort(data,data+n);
  cout << "Sorting Input Points = " << diffclock(t0,clock()) << " ms" << endl;
  
  t0 = clock();
  root = build2DRangeTree();
  cout << "Build 2D Range Datastructure = " << diffclock(t0,clock()) << " ms" << endl;
  
  /*for(int i = 0; i < n; ++i)
    cout << i << " -> " << data[i].first << " " << data[i].second << endl;*/
  
  //printTree(root);
  
  //TODO: Verification with naive algorithm on big data sets
  int x1 = 0, x2 = 10000, y1 = 0, y2 = 10000;
  int q = 2500;
  /*verify(2500,7500,2500,7500);
  verify(2500,7500,0,10);
  verify(0,2500,0,2500);*/
  for(int i = 0; i < q; ++i) {
    cout << "Query " << (i+1) << "/" << q << endl;
    int xs = x1 + (rand() % (x2-x1)), xe = xs + (rand() % (x2-x1-xs));
    int ys = y1 + (rand() % (y2-y1)), ye = ys + (rand() % (y2-y1-ys));
    if(!verify(xs,xe,ys,ye)) break;
  }
  
  cout << "Total Range Search Time = " << rangeSearchTime << " ms => " << (rangeSearchTime/q) << " ms per Query" << endl;
  cout << "Total Naive Range Search Time = " << naiveRangeSearchTime << " ms => " << (naiveRangeSearchTime/q) << " ms per Query" << endl;
  
  return 0;
}
