#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 10000000
ll smallest_divisor[N+1];

int n;
vector<ll> t;
vector<int> parent;
vector<int> prev_occ;
vector<int> succ_occ;
map<int, int> occ_idx;

void precalcSmallestPrimeDivisor() {
	smallest_divisor[0] = smallest_divisor[1] = 0;
	for(ll i = 2; i <= N; i++) smallest_divisor[i] = (i % 2 == 0 ? 2 : i);
	
	for(ll i = 3; i * i <= N; i+=2) {
		if(smallest_divisor[i] == i) {
			for(ll n = i*i; n <= N; n += (i<<1)) {
				if(smallest_divisor[n] == n) smallest_divisor[n] = i;
			}
		}
	}
}

vector<ll> fastFactorize(ll n) {
	vector<ll> res;
	while(n > 1) {
		res.push_back(smallest_divisor[n]);
		n /= smallest_divisor[n];
	}
	return res;
}

bool solve(int l, int r, int p) {
    if(r < l) return true;
    if(l == r) {
        parent[l] = p;
        return true;
    }
    int root = -1;
    for(int i = 0; i <= (r-l)/2 && root < 0; ++i) {
        if(prev_occ[l+i] < l && succ_occ[l+i] > r) root = l + i;
        if(prev_occ[r-i] < l && succ_occ[r-i] > r) root = r - i;
    }
    if(root == -1) return false;
    parent[root] = p;
    return solve(l,root-1,root+1) && solve(root+1,r,root+1);
}

int main() {

    precalcSmallestPrimeDivisor();

    cin >> n;
    t.resize(n);
    for(int i = 0; i < n; ++i) cin >> t[i];
    prev_occ.assign(n,0); succ_occ.assign(n,0);
    parent.assign(n,0);

    for(int i = 0; i < n; ++i) {
        int max_i = -1;
        vector<ll> fact = fastFactorize(t[i]);
        for(ll f : fact) {
            if(occ_idx.find(f) != occ_idx.end()) max_i = max(max_i, occ_idx[f]);
        }
        for(ll f : fact) {
            if(occ_idx.find(f) != occ_idx.end()) occ_idx[f] = i;
            else occ_idx.insert(make_pair(f,i));
        }
        prev_occ[i] = max_i;
    }
    occ_idx.clear();

    for(int i = n-1; i >= 0; --i) {
        int max_i = n;
        vector<ll> fact = fastFactorize(t[i]);
        for(ll f : fact) {
            if(occ_idx.find(f) != occ_idx.end()) max_i = min(max_i, occ_idx[f]);
        }
        for(ll f : fact) {
            if(occ_idx.find(f) != occ_idx.end()) occ_idx[f] = i;
            else occ_idx.insert(make_pair(f,i));
        }
        succ_occ[i] = max_i;
    }

    if(solve(0,n-1,0)) {
        for(int i = 0; i < n; ++i) cout << parent[i] << (i == n-1 ? "\n" : " ");
    } else {
        cout << "impossible" << endl;
    }
    
    return 0;
}