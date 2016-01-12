#include <bits/stdc++.h>

using namespace std;


//Searches the longest increasing subsequence in sequence X in O(n*log(n))
//Returns the indices which are part of this subsequence
//Precondidition: \forall i \in N: X[i] > 0
vector<int> longestIncreasingSubsequence(vector<int>& X) {
  int n = X.size();
  //M[j] stores an index k, such that there is an increasing subsequence of length j
  //ending at X[k]
  //P[k] stores the predecessor of X[k] in the longest increasing subsequence, which
  //ending at X[k]
  vector<int> M(n+1), P(n), s;
  
  int L = 0;
  for(int i = 0; i < n; i++) {
    int lo = 1, hi = L;
    //Try to extend an existing subsequence with X[i]
    //We search the length L' with binary search
    while(lo <= hi) {
      int mid = (lo+hi)/2;
      if(X[M[mid]] < X[i]) lo = mid+1;
      else hi = mid-1;
    }
    int newL = lo; P[i] = M[newL-1]; M[newL] = i;
    if(newL > L) L = newL;
  }
  
  //Reconstruct longest increasing subsequence
  int k = M[L];
  for(int i = L-1; i >= 0; i--) {
    s.push_back(k);
    k = P[k];
  }
  reverse(s.begin(),s.end());
  
  return s;
}



int main() {
  int n;
  vector<int> X;
  while(cin >> n) {
    X.push_back(n);
  }
  vector<int> lis = longestIncreasingSubsequence(X);
  cout << lis.size() << endl;
  cout << "-" << endl;
  for(int i = 0; i < lis.size(); i++)
    cout << X[lis[i]] << endl;
  
  return 0;
}
