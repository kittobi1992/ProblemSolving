#include <bits/stdc++.h>

using namespace std;

int main() {
  
    int N,K; cin >> N >> K;
    vector<int> a(N);
    for(int i = 0; i < N; ++i) cin >> a[i];
    
    int add = 0;
    for(int i = 1; i < N; ++i) {
        if(K - (a[i-1] + a[i]) > 0) {
            add += (K - (a[i-1] + a[i]));
            a[i] = (K - a[i-1]);
        }
    }
    
    cout << add << endl;
    for(int i = 0; i < N; ++i) {
        cout << a[i] << (i < N-1 ? " " : "\n");
    }
        
    
	return 0;
}
