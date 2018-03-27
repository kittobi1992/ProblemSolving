#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pl;
typedef pair<pair<ll,ll>,pair<ll,ll>> plpl;

int main() {
	
	int n, m;
	cin >> n >> m;

	if(m < n-1) {
		cout << "No" << endl;
		return 0;
	}
	
	vector<pl> island(n);
	vector<plpl> i_pair(n-1);
	vector<int> i_index(n-1);
	for(int i = 0; i < n; i++) {
		ll p1, p2;
		cin >> p1 >> p2;
		island[i] = make_pair(p1,p2);
		if(i != 0) {
			i_index[i-1] = i-1;
			i_pair[i-1] = make_pair(island[i-1],island[i]);
		}
	}

	sort(i_index.begin(),i_index.end(), [&](const int i1, const int i2) {
		ll dist_i1 = i_pair[i1].second.second - i_pair[i1].first.first;
		ll dist_i2 = i_pair[i2].second.second - i_pair[i2].first.first;
		if(dist_i1 < dist_i2) {
			return true;
		} else if(dist_i1 == dist_i2) {
			return i1 < i2;
		}
		else {
			return false;
		}
	});

	map<ll,set<int>> bridge;
	for(int i = 0; i < m; i++) {
		ll b;
		cin >> b;
		bridge[b].insert(i+1);
	}		 


	vector<ll> build(n-1,0);
	for(int i = 0; i < n-1; i++) {
		pl i1 = i_pair[i_index[i]].first;
		pl i2 = i_pair[i_index[i]].second;
		ll a = i2.second - i1.first;
		ll c = i2.first - i1.second;
		auto b = bridge.lower_bound(c);
		if(b != bridge.end()) {
			if(b->first <= a && b->first >= c) {
				build[i_index[i]] = *(b->second.begin());
				b->second.erase(b->second.begin());
				if(b->second.size() == 0)
					bridge.erase(b);
			}
			else {
				cout << "No" << endl;
				return 0;
			}
		}
		else {
			cout << "No" << endl;
			return 0;
		}
	}

	cout << "Yes" << endl;
	for(int i = 0; i < build.size(); i++) {
		cout << build[i] << " ";
	}
	cout << endl;
	return 0;
}
