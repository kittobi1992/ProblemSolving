#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

#define SIZE 2000000
#define UNIVERSE 3000000
#define LOG_UNIVERSE 24
#define INVALID -1


/*
 * Pre-/Sucecessor Datastructure, which determines the pre-/sucecessor of an element x in dataset D of size n
 * in O(log(log(u))) time, where u is the size of a universe U. More precise D \subseteq U. Experiments shows
 * (on random numbers with n > 2000000 and u > 3000000) that predecessor search over an xFastTrie is twice as fast
 * as with std::lower_bound.
 * The space of the datastructure is O(n*log(u)) words and the construction time is O(n*log(u)).
 * 
 * The datastructure work as follow:
 * Given a sequence S of numbers and a Universe U of size u with S \subseteq U. We construct a binary tree, which exists
 * of the binary prefixes of the numbers in S as inner nodes and the numbers in S as leaves. To store the tree we create log(u)
 * levels of size u (inserts nodes in corresponding bucket). On the leaf level we construct a double linked list, which represents, 
 * if we iterate over the list, S in sorted order. On each level from the buttom to top we shrink the universe by a factor of 1/2 and
 * the nodes on this level represents prefixes of the levels below. For each inner node v we store the min and max value of v subtree.
 * 
 * If we want to answer a predecessor query of a number num, we can perform binary search on the prefixes over log(u) levels which can be
 * determined in log(log(u)). If we have determined the longest prefix of num with a number in S, we can determine with an constant number
 * of operations the predecessor of num (see method predecessor).
 */

struct node {
  int num;
  node *min; node *max; node *pred; node *succ;
  bool valid;
};

int n, u, k; 
int data[SIZE];
node xFastTrie[LOG_UNIVERSE][UNIVERSE];

size_t node_size() {
  return sizeof(int) + 4*sizeof(node *) + sizeof(bool);
}

void initializeXFastTrie() {
  k = ceil(log2(u));
  memset(xFastTrie,0,node_size()*LOG_UNIVERSE*UNIVERSE);
  /*for(int i = 0; i <= k; ++i) {
    for(int j = 0; j < u; ++j)
      xFastTrie[i][j] = {INVALID,nullptr,nullptr,nullptr,nullptr};
  }*/
  
  //Insert Sentinel 0
  xFastTrie[k][0] = {0,nullptr,nullptr,nullptr,nullptr,true};
  xFastTrie[k][0].max = &xFastTrie[k][0]; xFastTrie[k][0].min = &xFastTrie[k][0];
  xFastTrie[k][0].succ = &xFastTrie[k][0]; xFastTrie[k][0].pred = &xFastTrie[k][0];

  //Insert inner nodes for sentinel 0
  for(int i = k-1; i >= 0; i--) {
    xFastTrie[i][0] = {0,nullptr,nullptr,nullptr,nullptr,true};
    xFastTrie[i][0].max = &xFastTrie[k][0]; xFastTrie[i][0].min = &xFastTrie[k][0];
  }
}

//num is part of the dataset if the corresponding node in the leaf-level is valid.
bool member(int num) {
  return xFastTrie[k][num].valid;
}

//Return predecessor of num in O(log(log(u))) time
node * predecessor(int num) {
  int l = 0, r = k;
  int longestPrefix = 0;
  
  //Searching longest prefix of num with an existing value in the dataset
  //over binary search on the length of the prefix.
  while(l+1 < r) {
    int m = (l+r)/2; longestPrefix = num >> (k-m);
    if(xFastTrie[m][longestPrefix].valid) l = m;
    else r = m;
  }
  
  if(xFastTrie[r][num >> (k-r)].valid) l = r;
  longestPrefix = num >> (k-l);
  
  //Let's denote min and max with the minimal and maximal number in the subtree of
  //xFastTrie[l][prefix]
  //Two case:
  //1. min is bigger as than num => Return predecessor of min
  if(xFastTrie[l][longestPrefix].min->num > num)
    return xFastTrie[l][longestPrefix].min->pred;
  //2. max is smaller than num => Return max
  else
    return xFastTrie[l][longestPrefix].max;
}

//Inserts a node into xFastTrie after node pred
void insert(int num, node *pred) {
  if(num == 0 || member(num))
    return &xFastTrie[k][num];
  
  //Inserts new node into double linked list on the lowest level of the trie
  xFastTrie[k][num] = {num,nullptr,nullptr,pred,pred->succ,true};
  xFastTrie[k][num].min = &xFastTrie[k][num]; xFastTrie[k][num].max = &xFastTrie[k][num];
  pred->succ->pred = &xFastTrie[k][num];
  pred->succ = &xFastTrie[k][num];
  
  //Inserts new node in the trie for the prefixes of num or updates min and max of 
  //existing nodes.
  for(int i = k-1; i >= 0; i--) {
    int prefix = num >> (k-i);
    if(xFastTrie[i][prefix].valid) {
      bool change = false; 
      if(xFastTrie[i][prefix].min->num > num) {
	xFastTrie[i][prefix].min = &xFastTrie[k][num]; change = true;
      }
      if(xFastTrie[i][prefix].max->num < num) {
	xFastTrie[i][prefix].max = &xFastTrie[k][num]; change = true;
      }
      //Performance trick: if min or max didn't change the corresponding nodes on
      //higher levels still exist and num didn't change their min and max value.
      if(!change) break;
    }
    else {
      xFastTrie[i][prefix] = {prefix,&xFastTrie[k][num],&xFastTrie[k][num],nullptr,nullptr,true};
    }
  }
  
}

//Build the xFastTrie in O(n*(log(log(u)) + log(u))) = O(n*log(u)) time
void buildXFastTrie() {
  initializeXFastTrie();
  for(int i = 0; i < n; ++i) {
    //O(log(log(u)))
    node *pred = predecessor(data[i]);
    //O(log(u))
    insert(data[i],pred);
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
	
	cout << "Element n = " << n << endl;
	cout << "Universe u = " << u << endl;
	clock_t t0 = clock();
	buildXFastTrie();
	cout << "Build xFastTrie = " << diffclock(t0,clock()) << " ms" << endl;
	
	t0 = clock();
	sort(data,data+n);
	cout << "Sorting data = " << diffclock(t0,clock()) << " ms" << endl;
	
	double elapseFast = 0;
	double elapseBinary = 0;
	for(int i = 0; i < u; ++i) {
	  t0=clock();
	  int pred = predecessor(i)->num;
	  elapseFast += diffclock(t0,clock());
	  t0 = clock();
	  auto verification = lower_bound(data,data+n,i);
	  if(*verification > i)
	    verification--;
	  elapseBinary += diffclock(t0,clock());
	  /*if(*verification != pred)
	    cout << "predecessor("<<i<<") = " << *verification << " != " << pred << endl; */
	}
	cout << "xFastTrie Time = " << elapseFast << " ms"<< endl;
	cout << "BinarySearch Time = " << elapseBinary << " ms" << endl;
	cout << "Speed Increase Factor = " << static_cast<double>(elapseBinary)/static_cast<double>(elapseFast) << endl;
	
	return 0;
}
