#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd (b, a % b);
}

int main() {

	int n;
	cin >> n;
	set<ll> number;
	unordered_map<ll,ll> count;
	for(int i = 0; i < n*n; i++) {
		ll num; cin >> num;
		count[num]++;
		number.insert(num); 
	}

	vector<ll> a;
	for(ll num : number) {
		if(count[num] % 2 == 1)
			a.push_back(num);
	} 

	for(ll n1 : a) {
		for(ll n2 : a) {
			ll ggt = gcd(n1,n2);
			count[ggt]--;
			if(count[ggt] == 0)
				number.erase(ggt);
		}
	}

	while(a.size() != n) {
		ll b = *(--number.end());
		count[b] -= 4;
		if(count[b] == 0)
			number.erase(b);
		for(ll n1 : a) {
			ll ggt = gcd(n1,b);
			count[ggt] -= 4;
			if(count[ggt] == 0)
				number.erase(ggt);	
		}
		a.push_back(b);
		a.push_back(b);
	}

	for(int i = 0; i < n - 1; i++)
		cout << a[i] << " ";
	cout << a[n-1] << endl;

	
	

}
