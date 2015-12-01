#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

#define MAX_VALUE pow(10,18)

ll r, s, m, d, n;
vector<ll> b;
vector<vector<ll>> dish;
map<ll,set<ll>> inc;

ll res;

ll overflow_check(ll a, ll b) {
	if(b > ((ll)MAX_VALUE)/a) {
		return 1+((ll) MAX_VALUE);
	}
	return a*b;
}

ll calc_combi(vector<int>& cur_d) {
	if(inc[cur_d[0]].find(cur_d[1]) != inc[cur_d[0]].end())
		return 0;
	if(inc[cur_d[0]].find(cur_d[2]) != inc[cur_d[0]].end())
		return 0;
	if(inc[cur_d[1]].find(cur_d[2]) != inc[cur_d[1]].end())
		return 0;

	set<ll> ingredient;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < dish[cur_d[i]].size(); j++) {
			if(ingredient.find(dish[cur_d[i]][j]) == ingredient.end()) {
				ingredient.insert(dish[cur_d[i]][j]);
			}
		}
	}

	ll ways = 1;
	for(ll ing : ingredient) {
		ways = overflow_check(ways,b[ing]);
	}
	
	return ways;

}


int main() {

	cin >> r >> s >> m >> d >> n;

	b.resize(r);
	for(int i = 0; i < r; i++)
		cin >> b[i];	

	dish.assign(s+m+d,vector<ll>());
	for(int i = 0; i < s+m+d; i++) {
		ll k; cin >> k;
		dish[i].resize(k);
		for(int j = 0; j < k; j++) {
			cin >> dish[i][j]; dish[i][j]--;
		}
		sort(dish[i].begin(),dish[i].end());
	}

	for(int i = 0; i < n; i++) {
		ll a, b;
		cin >> a >> b; a--; b--;
		inc[min(a,b)].insert(max(a,b));
	}

	res = 0;
	for(int i = 0; i < s; i++) {
		for(int j = s; j < s+m; j++) {
			for(int k = s+m; k < s+m+d; k++) {
				vector<int> cur_d(3); cur_d[0] = i; cur_d[1] = j; cur_d[2] = k;
				res += calc_combi(cur_d); 
				if(res > ((ll)MAX_VALUE)) {
					cout << "too many" << endl;
					return 0;
				}
			}
		}
	}
	
	cout << res << endl;

	return 0;
}
