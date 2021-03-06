#include <bits/stdc++.h>
#include <iostream>

using namespace std;

long long fak(long long n) {
	if(n == 1 || n == 0)
		return 1;
	return n*fak(n-1);
}

long long n, k;

void createBeatifulPermutation(int i, int& count, vector<int>& permut, vector<bool>& dist, vector<bool>& num) {
	if(i == permut.size()) {
		count++;
		return;
	}
	for(int j = 1; j < permut.size() + 1; j++) {
		if(i > 0) {
			if(dist[abs(permut[i-1]-j)] || num[j]) 
				continue;
			dist[abs(permut[i-1]-j)] = true;
		}
		num[j] = true;
		permut[i] = j;
		createBeatifulPermutation(i+1,count,permut,dist,num);
		if(count == k)
			return;
		if(i > 0)
			dist[abs(permut[i-1]-j)] = false;
		num[j] = false;
	}
	return;
}

int main() {

	int test;
	cin >> test;
	int c = 1;
	while(test--) {
		cin >> n >> k;
		vector<int> permut(n);
		vector<bool> dist(n,false);
		vector<bool> num(n+1,false);
		int count = 0;
		createBeatifulPermutation(0,count,permut,dist,num);
		cout << "Case " << c << ": ";
		if(count == k) {
			for(int i = 0; i < permut.size()-1; i++) {
				cout << permut[i] << " ";
			}
			cout << permut[permut.size()-1] << endl;
		}
		else
			cout << "-1" << endl;



		c++;
	}

	return 0;
}
