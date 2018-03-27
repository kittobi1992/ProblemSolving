#include <bits/stdc++.h>

using namespace std;

int N,K;
vector<int> A, B;

int main() {
    
    cin >> N >> K;
    A.resize(N); B.resize(N);
    for(int i = 0; i < N; ++i) cin >> A[i];
    for(int i = 0; i < N; ++i) cin >> B[i];
    
    vector<int> idx(N);
    std::iota(idx.begin(),idx.end(),0);
    std::sort(idx.begin(),idx.end(),[&](const int i1, const int i2) {
        return B[i1] - A[i1] > B[i2] - A[i2];
    });
    
    int price = 0;
    for(int i = 0; i < K; ++i) {
        price += A[idx[i]];
    }
    
    for(int i = K; i < N; ++i) {
        if(A[idx[i]] < B[idx[i]]) price += A[idx[i]];
        else price += B[idx[i]];
    }
    
    cout << price << endl;
    
	return 0;
}
