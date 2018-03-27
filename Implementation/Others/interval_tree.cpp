#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ival;

struct IntervalNode {
  int min_p, max_p, center_point;
  //Contains all intervals which intersect center_point
  //sorted_start: Sorted after first component, sorted_end: sorted after second component
  vector<ival> sorted_start, sorted_end;
  IntervalNode *left, *right;
};

class CenteredIntervalTree {
  
public:
  
  CenteredIntervalTree(vector<ival>& ivals) : root(nullptr), _ivals(ivals) {
    root = buildCenteredIntervalTree(root,ivals);
  }
  
  set<ival> findIntersectionWithPoint(int point) {
    set<ival> res;
    findIntersectionWithPointRecursive(root,point,res);
    return res;
  }
  
  set<ival> findIntersectionWithInterval(ival i) {
    set<ival> res;
    
    findEnclosingIntervalsRecursive(root,i,res);
    findIntersectionWithPointRecursive(root,i.first,res);
    findIntersectionWithPointRecursive(root,i.second,res);
    
    return res;
  }
  
  void printTree(IntervalNode *node) {
    if(node == NULL)
      return;
    cout << "Center Point: " << node->center_point << endl;
    cout << "Min: " << node->min_p << ", Max: " << node->max_p << endl;
    cout << "Sorted Start Center: " << endl;
    for(int i = 0; i < node->sorted_start.size(); ++i) {
      cout << "(" << node->sorted_start[i].first << "," << node->sorted_start[i].second << ")" << endl;
    }
    cout << "Sorted End Center: " << endl;
    for(int i = 0; i < node->sorted_end.size(); ++i) {
      cout << "(" << node->sorted_end[i].first << "," << node->sorted_end[i].second << ")" << endl;
    }
    cout << "-------------------------" << endl; 
    printTree(node->left); printTree(node->right);
  }
  
private:
  
  void findEnclosingIntervalsRecursive(IntervalNode *node, ival i, set<ival>& res) {
    if(!node)
      return;
    else if(node->center_point > i.second)
      findEnclosingIntervalsRecursive(node->left,i,res);
    else if(node->center_point < i.first)
      findEnclosingIntervalsRecursive(node->right,i,res);
    
    auto x_start = lower_bound(node->sorted_start.begin(),node->sorted_start.end(),make_pair(i.first,0));
    if(x_start != node->sorted_start.end()) {
      while(x_start->first <= i.second && x_start != node->sorted_start.end()) {
	if(x_start->second <= i.second)
	  res.insert(*x_start);
	x_start++;
      }
    }
    
    findEnclosingIntervalsRecursive(node->left,i,res);
    findEnclosingIntervalsRecursive(node->right,i,res);
    
  }
  
  void findIntersectionWithPointRecursive(IntervalNode *node, int point, set<ival>& res) {
    if(node == NULL)
      return;
    else if(node->max_p < point || point < node->min_p)
      return;
    
    if(point <= node->center_point) {
      for(int i = 0; i < node->sorted_start.size(); ++i) {
	if(node->sorted_start[i].first <= point)
	  res.insert(node->sorted_start[i]);
	else
	  break;
      }
      findIntersectionWithPointRecursive(node->left,point,res);
    }
    else {
      for(int i = 0; i < node->sorted_end.size(); ++i) {
	if(node->sorted_end[i].second >= point)
	  res.insert(node->sorted_end[i]);
	else
	  break;
      }
      findIntersectionWithPointRecursive(node->right,point,res);    
    }
    
  }
  
  IntervalNode * buildCenteredIntervalTree(IntervalNode *node, vector<ival>& ivals) {
    int n = ivals.size();
    if(n == 0)
      return NULL;
 
    int min_p = INT_MAX, max_p = -1; 
    for(int i = 0; i < n; ++i) {
      min_p = min(ivals[i].first,min_p), max_p = max(ivals[i].second,max_p);
    }
    int center_point = min_p + (max_p-min_p)/2;
    node = createNode(min_p,max_p,center_point);
    
    vector<ival> left, right;
    for(int i = 0; i < n; ++i) {
      if(ivals[i].first <= center_point && center_point <= ivals[i].second) {
	node->sorted_start.push_back(ivals[i]);
	node->sorted_end.push_back(ivals[i]);
      } else if(ivals[i].second < center_point) {
	left.push_back(ivals[i]);
      } else if(ivals[i].first > center_point) {
	right.push_back(ivals[i]);
      }
    }
    
    sort(node->sorted_start.begin(),node->sorted_start.end(), [&](const ival i1, const ival i2) {
      return i1.first < i2.first || (i1.first == i2.first && i1.second < i2.second);
    });
    sort(node->sorted_end.begin(),node->sorted_end.end(), [&](const ival i1, const ival i2) {
      return i1.second > i2.second || (i1.second == i2.second && i1.first > i2.first);
    });
    
    node->left = buildCenteredIntervalTree(node->left, left);
    node->right = buildCenteredIntervalTree(node->right, right);
    
    return node;
  }
  
  IntervalNode * createNode(int min_p, int max_p, int center_point) {
    IntervalNode *tmp = new IntervalNode;
    tmp->left = tmp->right = NULL;
    tmp->min_p = min_p; tmp->max_p = max_p;
    tmp->center_point = center_point;
    return tmp;
  }
  
  IntervalNode *root;
  vector<ival> _ivals;
};

int main() {
  
  int n; cin >> n;
  vector<ival> ivals(n,make_pair(0,0));
  for(int i = 0; i < n; ++i) cin >> ivals[i].first >> ivals[i].second;
  
  CenteredIntervalTree it(ivals);
  
  set<ival> inter = it.findIntersectionWithInterval(make_pair(1,20));
  for(ival it : inter) 
    cout << "("<<it.first << "," << it.second << ") ";
  cout << endl;
  
  
  return 0;
}
