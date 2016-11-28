#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

int main() {
    
    int T; cin >> T;
    while(T--) {
        ll N; cin >> N;
        ll sum = 0;
        for(int i = 0; i < N; ++i) {
            ll candies; cin >> candies;
            candies = candies % N;
            sum = (sum + candies) % N;
        }
        if(sum == 0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    
	return 0;
}
