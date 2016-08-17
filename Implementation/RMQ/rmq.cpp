#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

#define SIZE 2500002
#define LOG_SIZE 22

int n; 
int data[SIZE];
int rmq[SIZE][LOG_SIZE];

//Preprocessing RMQ-Datastructure in O(n*log(n))
void buildRMQ(int n) {
  for(int i = 0; i < n; ++i)
    rmq[i][0] = i;
  
  int l = log2(n) + 1;
  for(int i = 1; i < l; ++i) {
    int p = 1 << i;
    for(int j = 0; j+p < n; ++j) {
      rmq[j][i] = (data[rmq[j][i-1]] <= data[rmq[j+p/2][i-1]]) ? rmq[j][i-1] : rmq[j+p/2][i-1];
    }
  }
}

//RMQ-Query in O(1)
int query(int l, int r) {
  int k = log2(r-l+1), p = 1 << k;
  return (data[rmq[l][k]] <= data[rmq[r-p+1][k]]) ? rmq[l][k] : rmq[r-p+1][k];
}

//Naive implementation for verification
int linearQuery(int i, int j) {
	int idx = -1;
	int min_v = INT_MAX;
	for(int k = i; k <= j; k++) {
		if(min_v > data[k]) {
			min_v = data[k];
			idx = k;
		}
	}
	return idx;
}

int main() {
  	ios::sync_with_stdio(false);

	cin >> n;
	memset(data,0,sizeof(data));
	memset(rmq, 0, sizeof(rmq[0][0]) * SIZE * LOG_SIZE);
	for(int i = 0; i < n; i++)
		cin >> data[i];
	
	buildRMQ(n);
	
	int q = 100000;
	for(int i = 0; i < q; i++) {
		int l = rand() % n, r = rand() % n;
		int rmq_i = query(min(l,r),max(l,r));
		//int linear_i = linearQuery(min(l,r),max(l,r));
		//cout << "Searching for minimum in intervall [" << min(l,r) << "," << max(l,r) << "]" << endl;
		//cout << "RMQ query = [Index: " << rmq_i << ", Value: " << data[rmq_i] << "]" << endl;
		//cout << "Linear query = [Index: " << linear_i << ", Value: " << data[linear_i] << "]" << endl;
	}



	return 0;
}
