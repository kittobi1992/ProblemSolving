#include <bits/stdc++.h>
#include <iostream>

using namespace std;


typedef pair<int,int> alphabet;
typedef vector<int>::iterator it;

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

#define N 100000
    
public:
  
  /*
   * Constructor of the Wavelet-Tree class. 
   * Calls the construction method and build the naive rank structure.
   * Sigma is the range of the integer alphabet and X the sequence which
   * should be processed.
   */
  WaveletTree(vector<int> X, alphabet sigma) : n(X.size()), sigma(sigma), logSigma(0) {
    constructWaveletTree(X.begin(),X.begin(),X.end(),sigma.first,sigma.second,0);
    count.assign(logSigma*n,0);
    for(int i = 1; i <= logSigma*n; ++i) count[i] = count[i-1] + B[i-1];
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
  
  /*
   * The rank operation (Time complexity O(log(|sigma|))).
   * @return #a in X[0..(i-1)]
   */
  int rank(int i, int a) {
      return rank_recursive(i,a,0,n,sigma.first,sigma.second,0);
  }
  
  void print() {
      for(int i = 0; i < n; i++) cout << i << " ";
      cout << endl;
      for(int i = 0; i < n; i++) cout << "--";
      cout << endl;
      for(int i = 0; i < n*logSigma; i++) {
          cout << ((i % n == 0 && i != 0) ? "\n" : "") << B[i] << " ";
      }
      cout << endl;
  }
  
private:
  
  void constructWaveletTree(it b, it s, it e, int sigma0, int sigma1, int level) {
      if(sigma0 > sigma1) return;
      logSigma = max(level+1,logSigma);
      int m = (sigma0+sigma1)/2;
      for(it i = s; i != e; ++i) B.set(level*n+distance(b,i),*i > m);
      auto bound = stable_partition(s,e,[&](const int val) { return val <= m; });
      if(sigma0 == sigma1) return;
      constructWaveletTree(b,s,bound,sigma0,m,level+1);
      constructWaveletTree(b,bound,e,m+1,sigma1,level+1);
  }
  
  /*
   * Recursive method to solve rank(i,a).
   */
  int rank_recursive(int i, int a, int i0, int i1, int sigma0, int sigma1, int level) {
      if(sigma0 == sigma1) return i-i0;
      int m = (sigma0+sigma1)/2;
      if(a <= m) return rank_recursive(i0+rank0(i0,i,level),a,i0,i0+rank0(i0,i1,level),sigma0,m,level+1);
      else return rank_recursive(i0+rank0(i0,i1,level)+rank1(i0,i,level),a,i0+rank0(i0,i1,level),i1,m+1,sigma1,level+1);
  }
  
  int rank1(int i0, int i1, int level) {
    return count[level*n+i1]-count[level*n+i0];
  }
  
  int rank0(int i0, int i1, int level) {
    return (i1-i0)-rank1(i0,i1,level);
  }
  
  bitset<N> B;
  vector<int> count;
  int n;
  alphabet sigma;
  int logSigma;
};

int main() {
  vector<int> X = {1,3,5,2,3,7,1,0,4,7,6};
  WaveletTree wt(X,make_pair(0,7));
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