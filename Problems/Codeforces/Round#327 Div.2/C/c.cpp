#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef pair<int,int> point;

int main() {

	ios::sync_with_stdio(false);

	int n; cin >> n;
	vector<int> bit(n);
	for(int i = 0; i < n; i++) {
		cin >> bit[i];
	}
	bit.push_back(bit[n-1]);

	int bit_before = bit[0];
	int bit_start = bit[0];
	int start = 0;
	int cur_max = 0;
	for(int i = 1; i < n+1; i++) {
		if(bit_before == bit[i]) {
			int end = i-1;
			cur_max = max(cur_max, (end-start)/2);
			if(bit_start != bit[end]) {
				for(int j = start+1; j <= (end+start)/2; j++)
					bit[j] = bit_start;
				for(int j = (end+start)/2+1; j < end; j++)
					bit[j] = bit[end];
			}
			else {
				for(int j = start; j <= end; j++)
					bit[j] = bit[end];
			}
			start = i;
			bit_start = bit[i];
		}
		bit_before = bit[i];
	}

	cout << cur_max << endl;
	for(int i = 0; i < n-1; i++)
		cout << bit[i] << " ";
	cout << bit[n-1] << endl;
	

	
		

	return 0;

}
