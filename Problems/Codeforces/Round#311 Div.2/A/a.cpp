#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;

int main() {

	ll n;
	cin >> n;
	vector<ll> min_dip(3); 
	vector<ll> max_dip(3); 
	for(int i = 0; i < 3; i++) {
		cin >> min_dip[i];
		cin >> max_dip[i];
	}

	vector<ll> dis {max_dip[0],max_dip[1],max_dip[2]};
	ll sum = max_dip[0] +max_dip[1] + max_dip[2];
	for(int i = 2; i >= 0; i--) {
		ll dip = sum - n;
		dis[i] -= dip;
		if(dis[i] < min_dip[i]) {
			dis[i] = min_dip[i];
		}
		sum = dis[0] + dis[1] + dis[2];
		if(sum == n)
			break;
	}

	cout << dis[0] << " " << dis[1] << " " << dis[2] << endl;

	

}
