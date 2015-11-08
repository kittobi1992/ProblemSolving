#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



int main() {
	
	int test;
	cin >> test;
	while(test--) {
			int n; cin >> n;
			vector<int> num(n);
			for(int i = 0; i < n; i++)
				cin >> num[i];
			vector<int> c(10001,0);
			for(int i = 0; i < n; i++)
				c[num[i]]++;
			
			int res = 0;
			for(int i = 1; i <= 10000; i++) {
					if(c[i] > 0) {
							res += (c[i]*(c[i]-1))/2;
							for(int j = i+1; j < min(i+32,10001); j++) {
									if(c[j] > 0)
										res += c[i]*c[j];
							}
					}
			}
			
			cout << res << endl;
			
			
	}
	
	return 0;
}
