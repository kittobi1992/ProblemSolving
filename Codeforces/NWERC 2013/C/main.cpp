#include <bits/stdc++.h>

using namespace std;

#define UNKNOWN INT_MAX

int n, m;
vector<int> a;

int main() {
  
	while(cin >> n >> m) {
		a.assign(n,0);	
		int end_pos = m;
		for(int i = 0; i < n; ++i) {
			string c; cin >> c;
			if(c == "K" || c == "Q" || c == "J" || c == "10") a[i] = 10;
			else if(c == "A") a[i] = 11;
			else a[i] = c[0] - '0';
			end_pos += a[i];
		}
		end_pos -= a[n-1];
		
		vector<int> cards(end_pos+1,UNKNOWN); int pos = m;
		for(int i = 0; i < n; ++i) {
			cards[pos] = a[i]; pos += a[i];	
		}
		vector<double> dp(end_pos+1,0.0);
		for(int i = 1; i <= min(end_pos,10); ++i) dp[i] = 0.1;
		double p1 = 1.0/13.0;
		double p2 = 4.0/13.0;
		
		for(int i = 1; i < end_pos; ++i) {
			if(cards[i] != UNKNOWN) dp[i+cards[i]] += dp[i];	
			else {
				for(int j = 2; j <= 11; ++j) {
					if(i+j <= end_pos) {
						if(j != 10) dp[i+j] += dp[i]*p1;
						else dp[i+j] += dp[i]*p2;
					}
					else break;
				}
			}
		}
		
		cout << fixed << setprecision(15) << dp[end_pos] << endl;
		
	}
	
	return 0;
}
