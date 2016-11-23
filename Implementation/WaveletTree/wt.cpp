#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define N 100000

typedef pair<int,int> ii;

/*
 * Class constructs a Wavelet-Tree over a sequence X for an integer alphabet sigma
 * The Wavelet-Tree supports rank and select operations for sequences over integer alphabets.
 * The rank-operation is implemented in O(log(|sigma|)) and the select-operation in O(log(|sigma|)*log(|X|))
 * 
 * This Wavelet-Tree implementation uses one single bitvector B to store the whole tree topology.
 * For a sequence X over an alphabet sigma we have to allocate O(|X|log(|sigma|)) bits space to store the
 * Wavelet-Tree. The first level of the WT is than represented by B[0..|X|), the second by B[|X|..2|X|) and
 * the i-th level by B[(i-1)|B|..i|B|).
 * To get the child of a node which is represent by an interval [x0..x1) on level l (=> B[(l-1)*|X|+x0 .. (l-1)*|x|+x1))
 * we have to count the amount of zeros in this interval on B. Let z be the result of this operation than the two child
 * nodes of [x0..x1] are on level l+1 in interval [x0,x0+z) and [x0+z,x1).
 */
class WaveletTree {

public:
  
  /*
   * Constructor of the Wavelet-Tree class. 
   * Calls the construction method and build the naive rank structure.
   * Sigma is the range of the integer alphabet and X the sequence which
   * should be processed.
   */
  WaveletTree(pair<int,int> sigma, vector<int>& X) : sigma(sigma), n(X.size()), X(X) {
    memset(count,0,sizeof(count));
    constructWaveletTree(0,0,sigma,X);
    for(int i = 1; i <= size; i++) {
      //count[i] = #1 in B[0..(i-1)]
      count[i] =  count[i-1] + (B[i-1] == 1 ? 1 : 0);
    }
  }
  
  /*
   * The rank operation (Time complexity O(log(|sigma|))).
   * @return #a in X[0..(i-1)]
   */
  int rank(int i, int a) {
      return recursive_rank(0,make_pair(0,n),sigma,i,a);
  }
  
  /*
   * The select operation is implemented with rank and binary search
   * => Time complexity O(log(|sigma|)*log(|X|))
   * @return i-th occurence of integer a in X
   */
  int select(int i, int a) {
      if(rank(n,a) < i) return -1;
      int l = 0, r = n;
      while(l < r-1) {
	int m = (l+r)/2;
	if(rank(m,a) < i) l = m;
	else r = m;
      }
      return l;
  }
  
  
  void print() {
    for(int i = 0; i < n; i++) cout << X[i] << " ";
    cout << endl;
    for(int i = 0; i < n; i++) cout << "--";
    cout << endl;
    cout << B[0] << " ";
    for(int i = 1; i <= size; i++) {
      cout << (i % n == 0 ? "\n" : "") << B[i] << " ";
    }
    cout << endl;
  }
  
  
private:
  
  /*
   * Recursive method to solve rank(i,a).
   */
  int recursive_rank(int level, pair<int,int> ival, pair<int,int> sigma_range, int i0, int a) {
    //Interval within level level
    int x0 = ival.first, x1 = ival.second;
    //Alphabet-Range of node [x0,x1)
    int sigma0 = sigma_range.first, sigma1 = sigma_range.second;
    
    //If we reach a leaf, we count #0 in B[idx(level,x0)..idx(level,x0+i0)-1]
    if(sigma1-sigma0 <= 0) 
      return rank_b(0,level,x0,i0);
    
    int m = (sigma0+sigma1)/2;
    //a <= m => Leaf with label 'a' is in the left child
    if(a <= m) {
      //Mapping i0 to corresponding interval in the left child
      int i1 = rank_b(0,level,x0,i0);
      pair<int,int> left_child = child(level,x0,x1,1);
      pair<int,int> new_sigma_range = make_pair(sigma0,m);
      return recursive_rank(level+1,left_child,new_sigma_range,i1,a);
    }
    //a > m => Leaf with label 'a' is in the right child
    else {
      //Mapping i0 to corresponding interval in the right child
      int i1 = rank_b(1,level,x0,i0);
      pair<int,int> right_child = child(level,x0,x1,0);
      pair<int,int> new_sigma_range = make_pair(m+1,sigma1);
      return recursive_rank(level+1,right_child,new_sigma_range,i1,a);     
    }
  }
  
  /*
   * Mapping a specific position i within a level to the corresponding position
   * in bitvector B
   */
  int idx(int level, int i) {
    return level*n+i;
  }
  
  /*
   * Rank on bitvector B
   * @Return if rank_one than #1 in B[idx(level,x0)..idx(level,x0+i)-1]
   * 	     else #0 in B[idx(level,x0)..idx(level,x0+i)-1]
   */
  int rank_b(bool rank_one, int level, int x0, int i) {
    if(rank_one)
      return count[idx(level,x0+i)] - count[idx(level,x0)];
    return i-(count[idx(level,x0+i)] - count[idx(level,x0)]);
  }
  
  /*
   * Returns the two child nodes of the node which is 
   * represented by interval [x0,x1) on level level
   */
  pair<pair<int,int>,pair<int,int>> expand(int level, int x0, int x1) {
    int z = rank_b(0,level,x0,x1-x0);
    return make_pair(make_pair(x0,x0+z),make_pair(x0+z,x1));
  }
  
  /*
   * Returns either the left (left = true) or
   * right (left = false) child of the node which is 
   * represented by interval [x0,x1) on level level
   */
  pair<int,int> child(int level, int x0, int x1, bool left) {
    if(left)
      return expand(level,x0,x1).first;
    else 
      return expand(level,x0,x1).second;
  }
  
  /*
   * Method constructs recursively the wavelet tree of sequence Y.
   */
  void constructWaveletTree(int level, int off, pair<int,int> sigma_range, vector<int>& Y) {
    int sigma0 = sigma_range.first, sigma1 = sigma_range.second;
    if(sigma1 < sigma0)
      return;
    int m = (sigma0+sigma1)/2;
    //Y1 = {y | y \in Y: y <= m}
    //Y2 = {y | y \in Y: y > m}
    vector<int> Y1, Y2;
    for(int i = 0; i < Y.size(); ++i) {
      //B[i] = 1 <=> Y[i] > m
      if(Y[i] <= m) { B.set(idx(level,off+i),0); Y1.push_back(Y[i]); }
      else { B.set(idx(level,off+i),1); Y2.push_back(Y[i]); }
      size = max(size,idx(level,off+i));
    }
    if(m < sigma1)
      constructWaveletTree(level+1,off,make_pair(sigma0,m),Y1);
    constructWaveletTree(level+1,off+Y1.size(),make_pair(m+1,sigma1),Y2);
  }
  
  //Sequence over the WT is constructed.
  vector<int> X;
  //Bitvector which store the tree topology
  bitset<N> B;
  //Alphabet
  pair<int,int> sigma;
  //Size of sequence X
  int n;
  //Size of bitvector B
  int size;
  //count[i] = #1 in B[0..i)
  int count[N];

};

int main() {
  vector<int> X = {1,3,5,2,3,7,1,0,4,7,6};
  WaveletTree wt(make_pair(0,7),X);
  wt.print();
  cout << wt.rank(11,6) << endl;
  cout << wt.rank(7,3) << endl;
  cout << wt.rank(3,3) << endl;
  cout << wt.select(1,1) << ": " << X[wt.select(1,1)] << endl;
  cout << wt.select(1,3) << ": " << X[wt.select(1,3)] << endl;
  cout << wt.select(1,5) << ": " << X[wt.select(1,5)] << endl;
  cout << wt.select(1,2) << ": " << X[wt.select(1,2)] << endl;
  cout << wt.select(2,3) << ": " << X[wt.select(2,3)] << endl;
  cout << wt.select(1,7) << ": " << X[wt.select(1,7)] << endl;
  cout << wt.select(2,1) << ": " << X[wt.select(2,1)] << endl;
  cout << wt.select(1,0) << ": " << X[wt.select(1,0)] << endl;
  cout << wt.select(1,4) << ": " << X[wt.select(1,4)] << endl;
  cout << wt.select(2,7) << ": " << X[wt.select(2,7)] << endl;
  cout << wt.select(1,6) << ": " << X[wt.select(1,6)] << endl;
  return 0;
}