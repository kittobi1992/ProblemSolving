#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

template<typename T>
class RMQ {

	public:
		//RMQ preprocessing in O(n*log(n))
		RMQ(vector<T> a) : a(a) {
		  int n = a.size();
		  int k = floor(log2(n)) + 1;
		  rmq.assign(k,vector<int>(n));
		  for(int i = 0, s = 1; s <= n; s*=2, i++) {
		    //Store all minimum values of intervall [l,l+2^i) forall l \in {0..n-s}
		    for(int l = 0; l + s <= n; l++) {
		      if(i == 0) rmq[0][l] = l;
		      else {
			int r = l + s/2;
			//Minimum in intervall [l,l+2^i) is min(min([l,l+2^{i-1})),min([l+2^{i-1},l+2^i)))
			rmq[i][l] = (a[rmq[i-1][l]] <= a[rmq[i-1][r]] ? rmq[i-1][l] : rmq[i-1][r]);
		      }
		    }
		  }
		}

		//Range Minimum Query in O(1)
		//Return minimum value in intervall [i,j)
		int query(int i, int j) {
		  if(i >= j) return i;
		  //k = max {k | k < j-i}
		  int k = floor(log2(j-i)); j = j - (1 << k);
		  //Minimum in [i,j) is min(min([i,i+2^k)),min([j-2^k,j)))
		  return (a[rmq[k][i]] <= a[rmq[k][j]] ? rmq[k][i] : rmq[k][j]);
		}

		vector<vector<int>> rmq;
		vector<T> a;

};


int linearQuery(vector<int>& a, int i, int j) {
	int idx = -1;
	int min_v = INT_MAX;
	for(int k = i; k <= j; k++) {
		if(min_v > a[k]) {
			min_v = a[k];
			idx = k;
		}
	}
	return idx;
}


int main() {

	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];

	RMQ<int> rmq(a);
	int q = 3;
	for(int i = 0; i < q; i++) {
		int l = rand() % n, r = rand() % n;
		int rmq_i = rmq.query(min(l,r),max(l,r));
		//int linear_i = linearQuery(a,min(l,r),max(l,r));
		cout << "Searching for minimum in intervall [" << min(l,r) << "," << max(l,r) << "]" << endl;
		cout << "RMQ query = [Index: " << rmq_i << ", Value: " << a[rmq_i] << "]" << endl;
		//cout << "Linear query = [Index: " << linear_i << ", Value: " << a[linear_i] << "]" << endl;
	}



	return 0;
}
