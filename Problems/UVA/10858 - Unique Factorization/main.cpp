#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

#define N 2000000

vector<ll> dv;
vector<vector<ll>> res;
ll buf[N];

void findAllDivisors(ll n) {
	dv.clear();
	for(ll i = 2; i <= sqrt(n); ++i) {
		if(n % i == 0) { 
			dv.push_back(i); 
			if(i*i != n) dv.push_back(n/i);
		}
	}
	sort(dv.begin(),dv.end());
}

void search(ll n, int idx, int i) {

	if(n == 1) {
		vector<ll> tmp;
		for(int j = 0; j < idx; ++j) {
			tmp.emplace_back(buf[j]);
		}
		res.emplace_back(tmp);
		return;
	}
	
	
	for(int j = i; j < dv.size(); ++j) {
		if(n % dv[j] == 0) {
			buf[idx] = dv[j];
			search(n/dv[j],idx+1,j);
		}
	}
	
}

int main() {
	
	ll n; 
	while(cin >> n) {
		if(n == 0) break;
		if(n == 1 || n == 2) { cout << "0" << endl; continue; }
		
		findAllDivisors(n);
		if(dv.size() == 0) { cout << "0" << endl; continue; } 
		
		res.clear();
		search(n,0,0);
		
		cout << res.size() << endl;
		for(int i = 0; i < res.size(); ++i) {
			for(int j = 0; j < res[i].size(); ++j) {
				cout << res[i][j] << ((j+1 == res[i].size()) ? "\n" : " ");
			}
		}
		
	}

	
	return 0;
}
