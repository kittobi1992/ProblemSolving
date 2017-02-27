#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A,B;
vector<int> n1,n2;

int main() {
    cin >> N;
    A.resize(N); B.resize(N);
    n1.assign(6,0); n2.assign(6,0);
    for(int i = 0; i < N; ++i) {
        cin >> A[i]; n1[A[i]]++;
    }
    for(int i = 0; i < N; ++i) {
        cin >> B[i]; n2[B[i]]++;
    }
    
    int res = 0;
    for(int i = 1; i <= 5; ++i) {
        if((n1[i] + n2[i]) % 2 == 1) {
            cout << "-1" << endl;
            return 0;
        }
    }
    
    for(int i = 1; i <= 5; ++i) {
        for(int j = i+1; j <= 5; ++j) {
            if(n1[i] < n2[i] && n1[j] > n2[j]) {
                while(n1[i] < n2[i] && n1[j] > n2[j]) {
                    res++; n1[i]++; n2[i]--; n1[j]--; n2[j]++;
                }
            }
            else if(n1[i] > n2[i] && n1[j] < n2[j]) {
                while(n1[i] > n2[i] && n1[j] < n2[j]) {
                    res++; n1[i]--; n2[i]++; n1[j]++; n2[j]--;
                }
            }
        }
    }
    
    for(int i = 0; i <= 5; ++i) {
        if(n1[i] != n2[i]) {
            cout << "-1" << endl;
            return 0;
        }
    }
    
    cout << res << endl;
    
	return 0;
}
