#include <bits/stdc++.h>
#include <iostream>

using namespace std;

template<typename T>
class FenwickTree {
	public:
	vector<T> FT;
	int n;

	FenwickTree(vector<T>& a) {
		n = a.size();
		FT.assign(n+1,0);
		for(int i = 0; i < n; i++)
			updateFT(i,a[i]);
	}

	//Prefix-Sum of [0..i]
	T prefix_sum(int i) {
		T sum = 0; i++;
		while(i > 0) {
			sum += FT[i];
			i -= (i & (-i));
		}	
		return sum;
	}

	T interval_sum(int i, int j) {
		T sum = prefix_sum(j)-prefix_sum(--i);
		return sum;
	}

	void updateFT(int i, T val) {
		i++;
		while(i <= n) {
			FT[i] += val;
			i += (i & (-i));
		}
	}

};


int getPrefixSum(vector<int>& a, int i, int j) {
	int sum = 0;
	for(int k = i; k <= j; k++) {
		sum += a[k];
	}
	return sum;
}


int main() {

	vector<int> a {2,1,1,3,2,3,4,5,6,7,8,9};
	FenwickTree<int> ft(a);
	cout << "FT prefix sum from 0 to  = " << ft.prefix_sum(4) << endl;
	cout << "FT prefix sum from 1 to 4 = " << ft.interval_sum(1,4) << endl;
	cout << "Linear prefix sum from 1 to 4 = " << getPrefixSum(a,1,4) << endl;
	return 0;
}
