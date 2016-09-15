#include <bits/stdc++.h>

using namespace std;


bool search(vector<int>& res, int i, int j, int k) {
	if(i == j && k > 0) { res.push_back(i); return true; }
	else if(k <= 0) return false;
	
	if(j-i < 0) return true;
	
	int l = i; int r = j;
	while(r-l > 0) {
		int m = (r+l)/2;
		int height = ceil(log2(j-m+1));
		if(height < k) r = m;
		else l = m+1;
	}
	res.push_back(l);
	if(!search(res,i,l-1,k-1)) return false;
	else if(!search(res,l+1,j,k-1)) return false;
	else return true;
}

int main() {
  
	int t = 1;
	int n, h;
	while(cin >> n >> h) {
		if(n == 0 && h == 0) break;
		
		vector<int> res;
		if(!search(res,1,n,h)) {
			cout << "Case " << t++ << ": Impossible." << endl;	
			continue;
		}
		
		cout << "Case " << t << ": ";
		for(int i = 0; i < res.size(); ++i)
			cout << res[i] << ((i+1 == res.size()) ? "\n" : " ");
		
		t++;
	}
	
  return 0;
}
