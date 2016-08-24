#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

#define SIZE 2000000
#define INVALID -1

struct node {
  int num;
  node *min;
  node *max;
  node *pred;
  node *succ;
};

int n, u, k; 
int data[SIZE];
vector<vector<node>> xFastTrie;;

void initializeXFastTrie() {
  k = ceil(log2(u));
  xFastTrie.assign(k+1,vector<node>(u,{INVALID,nullptr,nullptr,nullptr,nullptr}));
  
  //Insert Sentinel 0
  xFastTrie[k][0] = {0,nullptr,nullptr,nullptr,nullptr};
  xFastTrie[k][0].max = &xFastTrie[k][0]; xFastTrie[k][0].min = &xFastTrie[k][0];
  xFastTrie[k][0].succ = &xFastTrie[k][0]; xFastTrie[k][0].pred = &xFastTrie[k][0];
  
  //Insert inner nodes for sentinel 0
  for(int i = k-1; i >= 0; i--) {
    xFastTrie[i][0] = {0,nullptr,nullptr,nullptr,nullptr};
    xFastTrie[i][0].max = &xFastTrie[k][0]; xFastTrie[i][0].min = &xFastTrie[k][0];
  }
}

bool member(int num) {
  return xFastTrie[k][num].num != INVALID;
}


node * predecessor(int num) {
  int l = 0, r = k;
  int prefix = 0;
  
  while(l+1 < r) {
    int m = (l+r)/2; prefix = num >> (k-m);
    if(xFastTrie[m][prefix].num != INVALID) l = m;
    else r = m;
  }
  
  if(xFastTrie[r][num >> (k-r)].num != INVALID)
    l = r;
  prefix = num >> (k-l);
  
  if(xFastTrie[l][prefix].min->num > num)
    return xFastTrie[l][prefix].min->pred;
  else
    return xFastTrie[l][prefix].max;
}

node * insert(int num, node *pred) {
  if(num == 0 || member(num))
    return &xFastTrie[k][num];
  
  xFastTrie[k][num] = {num,nullptr,nullptr,pred,pred->succ};
  xFastTrie[k][num].min = &xFastTrie[k][num]; xFastTrie[k][num].max = &xFastTrie[k][num];
  pred->succ->pred = &xFastTrie[k][num];
  pred->succ = &xFastTrie[k][num];
  
  for(int i = k-1; i >= 0; i--) {
    int prefix = num >> (k-i);
    if(xFastTrie[i][prefix].num != INVALID) {
      if(xFastTrie[i][prefix].min->num > num)
	xFastTrie[i][prefix].min = &xFastTrie[k][num];
      if(xFastTrie[i][prefix].max->num < num)
	xFastTrie[i][prefix].max = &xFastTrie[k][num];
    }
    else {
      xFastTrie[i][prefix] = {prefix,&xFastTrie[k][num],&xFastTrie[k][num],nullptr,nullptr};
    }
  }
  
  return &xFastTrie[k][num];
}

void buildXFastTrie() {
  initializeXFastTrie();
  sort(data, data + n);
  node * pred = &xFastTrie[k][0];
  for(int i = 0; i < n; ++i) {
    pred = insert(data[i],pred);
  }
}

void printLeaves() {
  node cur = *xFastTrie[k][0].succ;
  while(cur.num != 0) {
    cout << cur.num << " ";
    cur = *cur.succ;
  }
  cout << endl;
}

double diffclock(clock_t clock1,clock_t clock2)
{
    double diffticks=clock2-clock1;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return diffms;
}

int main() {
  	ios::sync_with_stdio(false);

	cin >> n >> u;
	memset(data,0,sizeof(data));
	for(int i = 0; i < n; i++)
	  cin >> data[i];
	
	
	buildXFastTrie();
	
	double elapseFast = 0;
	double elapseBinary = 0;
	for(int i = 0; i < u; ++i) {
	  clock_t t0=clock();
	  int pred = predecessor(i)->num;
	  elapseFast += diffclock(t0,clock());
	  t0 = clock();
	  auto verification = lower_bound(data,data+n,i);
	  if(*verification > i)
	    verification--;
	  elapseBinary += diffclock(t0,clock());
	  if(*verification != pred)
	    cout << "predecessor("<<i<<") = " << *verification << " != " << pred << endl; 
	}
	cout << "xFastTrie Time = " << elapseFast << " ms"<< endl;
	cout << "BinarySearch Time = " << elapseBinary << " ms" << endl;
	cout << "Speed Increase Factor = " << static_cast<double>(elapseBinary)/static_cast<double>(elapseFast) << endl;
	
	//printLeaves();
	return 0;
}
