#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;

int main() {

	int n;
	cin >> n;
	vector<ll> l(n); 
	vector<ll> d(n);
	vector<ll> idx(n);
	map<ll,ll> c;
	map<ll,ll> e;
	map<ll,set<ll>> es;
	set<ll> ls;
	for(int i = 0; i < n; i++) {
		cin >> l[i];
		c[l[i]]++;
		ls.insert(l[i]);
		idx[i] = i;
	}
	for(int i = 0; i < n; i++) {
		cin >> d[i];
		e[l[i]] += d[i];
		es[l[i]].insert(d[i]);
	}

	sort(idx.begin(),idx.end(),[&](const int i1, const int i2) {
		if(d[i1] < d[i2]) 
			return true;
		else if(d[i1] == d[i2]) {
			return i1 < i2;
		} else {
			return false;
		}
	});

	vector<ll> pre_sum(n+1,0);
	for(int i = 0; i < n; i++) {
		pre_sum[i+1] += d[idx[i]];
	}

	map<ll,ll> suf_sum;
	map<ll,ll> del_leg;
	ll sum = 0;
	ll del = 0;
	for(auto b = --e.end(); b != e.begin(); b--) {
		suf_sum[b->first] = sum;
		del_leg[b->first] = del;
		del += c[b->first];
		sum += b->second;
	}
	suf_sum[e.begin()->first] = sum;
	del_leg[e.begin()->first] = del;

	ll min_energy = INT_MAX;
	for(ll l : ls) {
		ll energy = suf_sum[l];
		ll legs_to_remove = n - del_leg[l];
		if(c[l] > legs_to_remove/2) {
			legs_to_remove = 0;
		}
		else {
			legs_to_remove = (1-2*c[l])+legs_to_remove; 
		}
		sum = 0;
		int c = 0;
		for(ll ac : es[l]) {
			if(ac <= d[idx[legs_to_remove]]) {
				c++;
				sum += ac;
			}
			else {
				break;
			}
		}
		energy += pre_sum[legs_to_remove+c]-sum;
		cout << pre_sum[legs_to_remove+c] << endl;
		if(energy < min_energy)
			min_energy = energy;
			
	}

	cout << min_energy << endl;

	

	

}
