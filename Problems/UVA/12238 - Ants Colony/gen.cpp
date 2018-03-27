#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int main() {

	int MAX_WEIGHT = 1000000;
	int N = 100000; int Q = 100000;
	cout << N << endl;
	for(int i = 1; i < N; i++) {
	  int u = rand() % i, l = rand() % MAX_WEIGHT;
	  cout << u << " " << l << endl;
	}
	
	cout << Q << endl;
	for(int i = 0; i < Q; i++) {
	  int u = rand() % N, v = rand() % N;
	  cout << u << " " << v << endl;
	}
	
	return 0;
}
 