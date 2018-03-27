#include <bits/stdc++.h>
#include <iostream>
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
						rmq[layer_idx[i]+j].push_back((a[access(l,l+m)] < a[access(l+m+1,l+s-1)] ? access(l,l+m) : access(l+m+1,l+s-1)));		
				}
			}
		}

		int query(int i, int j) {
			int s = pow(2,floor(log(j-i+1)/log(2)));
			return (a[access(i,i+s-1)] < a[access(j-(s-1),j)] ? access(i,i+s-1) : access(j-(s-1),j));
		}

		void printRMQ() {
			cout << "Layer Index: ";
			for(int i = 0; i < layer_idx.size(); i++)
				cout << layer_idx[i] << " ";
			cout << endl;

			for(int i = 0; i < rmq.size(); i++) {
				cout << i << ":";
				for(int j = 0; j < rmq[i].size(); j++) 
					cout << " " << rmq[i][j] << "(" << a[rmq[i][j]] << ")";
				cout << endl;
			}
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

	
	int n; cin >> n;
	vector<int> h(n);
	for(int i = 0; i < n; i++)
		cin >> h[i];

	RMQ<int> rmq(h);
	int cur_max = h[0];
	int max_part = 1;
	for(int i = 1; i < n; i++) {
		if(cur_max <= h[i]) {
			int min_val = h[rmq.query(i,n-1)];
			if(min_val >= cur_max) {
				cur_max = h[i];
				max_part++;
			}
			else {
				if(cur_max < h[i])
					cur_max = h[i];
			}
		}
	}

	cout << max_part << endl;
		

	return 0;

}
