#include <bits/stdc++.h>

using namespace std;

//Creates a Matching-List such that matchinglist[i] = {j | X[i] == Y[j]}
//The Matching-Lists are sorted in decreasing order and |X| >= |Y|
//To produce the matching lists we sort the indicies of sequences and merge them
//=> Sorting: O(|X|*log(|X|)), Merge: O(|X|+|Y|) => MATCHLIST \in O(|X|*log(|X|))
void createMatchlist(vector<vector<int>>& matchlist, vector<int>& X, vector<int>& Y) {
  vector<int> posX(X.size()), posY(Y.size());
  iota(posX.begin(),posX.end(),0); iota(posY.begin(),posY.end(),0); //Produce {0,1,..,SIZE}
  //Sort Indicies of sequence X and Y in O(|X|*log(|X|)) time
  sort(posX.begin(),posX.end(), [&](const int i1, const int i2) {
    return X[i1] < X[i2] || (X[i1] == X[i2] && i1 < i2);});
  sort(posY.begin(),posY.end(), [&](const int i1, const int i2) {
    return Y[i1] < Y[i2] || (Y[i1] == Y[i2] && i1 > i2);});
  reverse(posY.begin(),posY.end()); //Reverse posY to use it as a stack
  
  for(int i = 0; i < X.size(); i++) {
    //Matching-List for number posX[i] is already created before we apply it from posX[i-1]
    if(X[posX[i]] == (i > 0 ? X[pos[i-1]] : -1)) { 
      matchlist[posX[i]].insert(matchlist[posX[i]].begin(),matchlist[posX[i-1]].begin(),matchlist[posX[i-1]].end());
      continue;
    }
    //Merges all Y[j] == X[posX[i]] into matchinglist[posX[i]]
    //Note: Lists are sorted => Merge runnning time is O(|X|+|Y|)
    while(!posY.empty() && X[posX[i]] >= Y[posY.back()]) {
      if(X[posX[i]] == Y[posY.back()])
	matchlist[posX[i]].push_back(posY.back());
      posY.pop_back();
    }
  }
}

typedef pair<int,int> ii;

//Datastructure to reconstruct the longest common subsequence
class node {
public:
  ii p;
  node* predecessor;
  node(int i, int j, node* predecessor) : p(make_pair(i,j)), predecessor(predecessor) { }
};

//Find Longest Common Subsequence in expected running time of O((n+r)*log(n))
//r is the amount of matching pairs in X and Y => r = |{(i,j) | X[i] == Y[j]}|
//Worst case running time is O(n^2 * log(n)), but on random inputs or especially for
//permutations the running time is O(n*log(n))
size_t findLongestCommonSubsequence(vector<int> X, vector<int> Y, vector<ii>* lcs = nullptr) {
  //|X| > |Y|
  if(X.size() < Y.size()) swap(X,Y);
  size_t N = X.size();
  
  //Creating Matching-List => matchlist[i] = {j | X[i] == Y[j]}
  //Matching-List are sorted in decreasing order
  vector<vector<int>> matchlist(N,vector<int>());
  createMatchlist(matchlist,X,Y);

  //Is needed to reconstruct the longest common subsequence
  vector<node*> link(N+2, new node(0,0,nullptr));
  //Background: T(i,k) = smallest j such that X[1:i] and Y[1:j] contains a common
  //subsequence of length k
  //Note: X and Y are 1-indexed
  vector<int> T(N+2,N+1); T[0] = 0;
  for(int i = 0; i < N; i++) {
    //Precondition: T[k] = T(i-1,k)
    for(int j : matchlist[i]) {
      //Lemma: T(i+1,k) = smallest j such that X[i+1] = Y[j] and T(i,k-1) < j <= T(i,k)
      //       If such a j didn't exists T(i+1,k) = T(i,k)
      auto tk = lower_bound(T.begin(),T.end(),(j+1));
      if(j+1 < *tk) {
	int k = (tk-T.begin()); *tk = j+1;
	link[k] = new node(i,j,(k > 1 ? link[k-1] : nullptr));
      }
    }
    //Postcondition: T[k] = T(i,k)
  }
  
  //LCS-Length is the biggest k, where T[k] != N+1
  size_t max_k = 0;
  for(int k = 0; k < N+2; k++) {
    if(T[k] == N+1) { max_k = k-1; break; }
  }
  
  //Reconstruct Longest common subsequence
  if(lcs) {
    node* PTR = link[max_k];
    while(PTR) {
      lcs->push_back(PTR->p); PTR = PTR->predecessor;
    }
    reverse(lcs->begin(),lcs->end());
  }
  
  return max_k;
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
	/*string s1, s2;
	while(getline(cin,s1) && getline(cin,s2)) {
	    int n = s1.size(), m = s2.size();
	    vector<int> X(n), Y(m);
	    for(int i = 0; i < n; i++)
	      X[i] = ((int) s1[i]);
	    for(int i = 0; i < m; i++)
	      Y[i] = ((int) s2[i]);
	    cout << findLongestCommonSubsequence(X,Y) << endl;
	}*/
  
	int test; cin >> test;
	while(test--) {
	  int n; cin >> n;
	  vector<int> X(n,0);
	  for(int i = 0; i < n; i++)
	    cin >> X[i];
	  
	  int m; cin >> m;
	  vector<int> Y(m,0);
	  for(int i = 0; i < m; i++)
	    cin >> Y[i];
	  
	  vector<ii> lcs;
	  int lcs_length = findLongestCommonSubsequence(X,Y,&lcs);
	  if(lcs.size() != lcs_length) {
	    cout << "LCS-Array has different length LCS!" << endl;
	  } else {
	    int last_i = -1, last_j = -1;
	    for(int k = 0; k < lcs.size(); k++) {
	      int i = lcs[k].first, j = lcs[k].second;
	      if(X[i] != Y[j] || i < last_i || j < last_j) {
		cout << "LCS-Array is not a valid lcs!" << endl;
		return 0;
	      }
	      last_i = i; last_j = j;
	    }
	  }
	}
	return 0;
}
