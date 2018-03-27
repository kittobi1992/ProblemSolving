#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ii;

struct Node {
  int start, end;
  int negative, zero;
  Node *left, *right;
};

Node *root;

Node * createNode(int start, int end) {
  Node *tmp = new Node;
  tmp->start = start; tmp->end = end;
  tmp->negative = 0; tmp->zero = 0;
  tmp->left = NULL; tmp->right = NULL;
  return tmp;
}

Node * buildSegmentTree(vector<int>& a, int start, int end) {
  
  if(end - start == 0) {
    Node *node = createNode(start,end);
    if(a[start] == 0) node->zero++;
    else if(a[start] < 0) node->negative++;
    return node;
  }
  
  int m = start + (end-start)/2;
  Node *node = createNode(start,end);
  node->left = buildSegmentTree(a,start,m);
  node->right = buildSegmentTree(a,m+1,end);
  
  node->negative = node->left->negative + node->right->negative;
  node->zero = node->left->zero + node->right->zero;
  return node;
  
}

void update(Node *node, int i, int val, vector<int>& a) {
  //Precondition: a[i] != val
  if(node->start <= i && i <= node->end) {
    if(a[i] == 0) node->zero--;
    else if(a[i] < 0) node->negative--;
    if(val == 0) node->zero++;
    else if(val < 0) node->negative++;
    if(node->left)
      update(node->left,i,val,a);
    if(node->right)
      update(node->right,i,val,a);
  }
}

void printTree(Node *node) {
  if(node) {
    cout << "Segment: [" << node->start << "," << node->end << "]"<< endl;
    cout << "Negative: " << node->negative << ", Zero: " << node->zero << endl;
    cout << "--------------------" << endl;
    printTree(node->left);
    printTree(node->right);
  }
}

ii query(Node *node, int start, int end) {
  if(node && (node->start > end || node->end < start))
    return make_pair(0,0);
  
  if(start <= node->start && node->end <= end) {
    return make_pair(node->negative,node->zero);
  } else {
   
    ii res = make_pair(0,0);
    
    ii left_res = query(node->left,start,end);
    ii right_res = query(node->right,start,end);
    res.first = left_res.first + right_res.first;
    res.second = left_res.second + right_res.second;
    
    return res;
    
  }
}

int main() {
  
  int n, k;
  while(cin >> n >> k) {
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
      int tmp; cin >> tmp;
      if(tmp == 0) a[i] = 0;
      else if(tmp < 0) a[i] = -1;
      else a[i] = 1;
    }
    //for(int i = 0; i < n; ++i) cout << a[i] << " "; cout << endl;
    
    //create tree;
    root = buildSegmentTree(a,0,a.size()-1);
    //printTree(root);
    
    for(int i = 0; i < k; ++i) {
      char c; int i1, i2; cin >> c >> i1 >> i2;
      if(c == 'C') {
	//Update
	i1--;
	i2 = (i2 == 0)  ? 0 : i2/abs(i2);
	update(root,i1,i2,a);
	a[i1] = i2;
	
      }
      else {
	//Calculate Interval Product
	i1--; i2--;
	pair<int,int> q = query(root, i1,i2);
	if(q.second > 0)
	  cout << "0";
	else if(q.first % 2 == 0)
	  cout << "+";
	else
	  cout << "-";
      }
    }
    cout << endl;
  }
  return 0;
}
