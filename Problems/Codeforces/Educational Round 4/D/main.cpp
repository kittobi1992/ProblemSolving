#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> ii;


int main() {
  
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);	
 
	int n, k; cin >> n >> k;
	int N = 2*n;
	vector<ii> s;
	for(int i = 0; i < n; i++) {
	  int l, r; cin >> l >> r;
	  s.push_back(make_pair(l,-1));
	  s.push_back(make_pair(r,1));
	}
	
	sort(s.begin(),s.end());
	int cur_k = 0; bool create_seg = false;
	vector<ii> segments;
	int start_l = 0;
	for(int i = 0; i < N; i++) {
	  int e = s[i].first; cur_k -= s[i].second;
	  if(cur_k >= k && !create_seg) {
	    create_seg = true; start_l = e;
	  }
	  if(cur_k < k && create_seg) {
	    create_seg = false; segments.push_back(make_pair(start_l,e));
	  }
	}
	
	cout << segments.size() << endl;
	for(int i = 0; i < segments.size(); i++) 
	  cout << segments[i].first << " " << segments[i].second << endl;

	return 0;
}
