#include <bits/stdc++.h>

using namespace std;

template<typename T>
void backtrackLongestCommonSubsequence(vector<T>& lcs, vector<vector<size_t>>& dp, vector<T>& X, vector<T>& Y, int i, int j) {
  if(i == 0 || j == 0) return;
  else if(X[i-1] == Y[j-1]) {
    lcs.push_back(X[i-1]);
    backtrackLongestCommonSubsequence<T>(lcs,dp,X,Y,i-1,j-1);
  }
  else {
    if(dp[i-1][j] > dp[i][j-1]) backtrackLongestCommonSubsequence<T>(lcs,dp,X,Y,i-1,j);
    else backtrackLongestCommonSubsequence<T>(lcs,dp,X,Y,i,j-1);
  }
}

template<typename T, bool BacktrackLCS = false>
size_t findLongestCommonSubsequence(vector<T> X, vector<T> Y, vector<T>* lcs = nullptr) {
  size_t n = X.size(), m = Y.size();
  vector<vector<size_t>> dp(n+1,vector<size_t>(m+1,0));
  for(int i = 1; i < n+1; i++) {
    for(int j = 1; j < m+1; j++) {
      if(X[i-1] == Y[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
      else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
    }
  }
  
  if(BacktrackLCS && lcs) {
    backtrackLongestCommonSubsequence<T>(*lcs,dp,X,Y,n,m);
    reverse(lcs->begin(),lcs->end());
  }
  
  return dp[n][m];
}

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
	vector<int> X {1,5,3,2,6,4,3,1,4};
	vector<int> Y {1,3,4,2,4};
	vector<int> lcs;
	cout << findLongestCommonSubsequence<int,true>(X,Y,&lcs) << endl;
	for(int i = 0; i < lcs.size(); i++)
	  cout << lcs[i] << " ";
	cout << endl;
	
	return 0;
}
