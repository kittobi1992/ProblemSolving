#include <bits/stdc++.h>

using namespace std;

int N, M;
string P,T;
vector<int> A;
vector<int> contain;
int thres = 1;

bool test(int k) {
    for(int i = N-1; i >= k; --i) {
        contain[A[i]-1] = thres;
    }
    
    int pos = M-1;
    for(int i = N-1; i >= 0; --i) {
        if(pos == -1) break;
//         cout << contain[i] << " == " << thres << " && " << T[i] << " == " << P[pos] << endl; 
        if(contain[i] == thres && T[i] == P[pos]) pos--;
    }
    thres++;
    return pos == -1;
}

int main() {
    cin >> T >> P;
    N = T.size(), M = P.size();
    A.resize(N); contain.assign(N,0);
    for(int i = 0; i < N; ++i) cin >> A[i];
    
    int l = 0, r = N-1;
    while(r-l > 1) {
        int m = (l+r)/2;
        if(test(m)) l = m;
        else r = m-1;
    }
    
    if(test(r)) cout << r << endl;
    else cout << l << endl;
    
	return 0;
}
