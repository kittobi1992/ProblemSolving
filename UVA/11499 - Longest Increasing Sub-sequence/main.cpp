#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

#define MAX_N 605

int n,m;
vector<vector<int>> M, P;

void printArray(vector<vector<int>>& X) {
	  for(int i = 0; i < n; i++) {
	    for(int j = 0; j < m; j++)
	      cout << X[i][j] << " ";
	    cout << endl;
	  }
}

int main() {
  
	M.assign(MAX_N,vector<int>(MAX_N)); P.assign(MAX_N,vector<int>(MAX_N)); 

	while(cin >> n >> m) {
	  if(n+m==0)
	    break;
	  for(int i = 0; i < n; i++) {
	    cin >> M[i][0]; int start = 0; P[i][0] = start;
	    for(int j = 1; j < m; j++) {
	      cin >> M[i][j];	      
	      if(M[i][j-1] >= M[i][j])	start = j;
	      P[i][j] = start;
	    }
	  }
	   
	  int max_size = 0;
	  for(int i = 0; i < n; i++) {
	    for(int j = 0; j < m; j++) {
	      if((n-i)*(j-P[i][j]+1) <= max_size)
		continue;
	      int cur_start = P[i][j];
	      max_size = max(j - P[i][j] + 1,max_size);
	      for(int k = i+1; k < n; k++) {
		if(M[k][j] <= M[k-1][j])
		  break;
		cur_start = ((int)(upper_bound(M[k].begin()+max(P[k][j],cur_start),M[k].begin()+j,M[k-1][j])-M[k].begin()));
		max_size = max((k-i+1)*(j-cur_start+1),max_size);
		if((n-i)*(j-cur_start+1) <= max_size)
		  break;
	      }
	    }
	  }
	  
	  cout << max_size << endl;
	  
	  
	  
	}

	return 0;
}
