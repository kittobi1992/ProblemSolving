#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

template<typename T>
class RMQ {

	public:
		RMQ(vector<T> a) : rmq(), layer_idx(), a(a) {
			int n = a.size();
			int k = floor(log(n)/log(2));
			layer_idx.push_back(0);
			rmq.push_back(vector<int>());
			for(int i = 0; i < n; i++)
				rmq[0].push_back(i);

			for(int i = 1; i <= k; i++) {
				int s = pow(2,i); int m = (s-1)/2;
				layer_idx.push_back(rmq.size());
				for(int j = 0; j < s; j++) {
					rmq.push_back(vector<int>());
					for(int l = j; l+s-1 < n; l += s)
						rmq[layer_idx[i]+j].push_back((a[access(l,l+m)] > a[access(l+m+1,l+s-1)] ? access(l,l+m) : access(l+m+1,l+s-1)));		
				}
			}
		}

		int query(int i, int j) {
			int s = pow(2,floor(log(j-i+1)/log(2)));
			return (a[access(i,i+s-1)] > a[access(j-(s-1),j)] ? access(i,i+s-1) : access(j-(s-1),j));
		}


	private:
		int access(int i, int j) {
			//j-i+1 = 2^n n € N
			int k = j-i+1, layer = floor(log(k)/log(2)), off = i % max(k,1), idx = (i - off)/k;
			return rmq[layer_idx[layer]+off][idx];
		}


		vector<vector<int>> rmq;
		vector<int> layer_idx;
		vector<T> a;

};



int main() {


	ios::sync_with_stdio(false);

	int n;
	while(cin >> n) {
		if(n == 0)
			break;
		int q; cin >> q;
		vector<int> a(n);
		for(int i = 0; i < n; i++)
			cin >> a[i];

		vector<int> f(n,-1);
		vector<int> s;
		int tmp = 1;
		int before = a[0];
		for(int i = 1; i < n; i++) {
			if(a[i] != before) {
				int j = i-1;
				while(f[j] == -1) f[j--] = tmp;
				tmp = 1; before = a[i]; s.push_back(j+1);
			} else 
				tmp++;
		}
		int j = n-1;
		while(f[j] == -1) f[j--] = tmp;
		s.push_back(j+1);

		RMQ<int> rmq(f);

		for(int i = 0; i < q; i++) {
			int l, r; cin >> l >> r;
			l--; r--;
			auto l_it = upper_bound(s.begin(),s.end(),l);
			auto r_it = upper_bound(s.begin(),s.end(),r);
			if(l_it == r_it) {
				cout << (r-l+1) << endl;
				continue;
			}
			int l_adj = l;
			int r_adj = *(r_it-1);
			int v2 = (r-r_adj+1);
			if(l_it != s.end()) {
				l_adj = *l_it;
			} else {
				r_adj = r+1;
				v2 = 0;
			}
			int v1 = (l_adj-l);
			int v3 = -1;
			//cout << "(" << l << "," << r << ")" << endl;
			//cout << "(" << l << "," << (l_adj-1) << ") - (" << l_adj << "," << (r_adj-1) << ") - (" << r_adj << "," << r << ")" << endl;  
			if(l_adj <= r_adj-1)
				v3 = f[rmq.query(l_adj,r_adj-1)];
			cout << max(v1,max(v2,v3)) << endl;
		}
	}


	return 0;
}
