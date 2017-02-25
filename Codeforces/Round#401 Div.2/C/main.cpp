#include <bits/stdc++.h>

using namespace std;

#define X first
#define Y second

typedef long long ll; 
typedef pair<int,int> ival;

size_t N,M,K;
vector<vector<ll>> A;

bool check_enclosing(const ival& i1, const ival& i2) {
    return i1.X <= i2.X && i1.Y >= i2.Y;    
}

int main() {

    cin >> N >> M;
    A.assign(N,vector<ll>(M,0));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) cin >> A[i][j];
    }
    
    set<ival> S;
    for(int j = 0; j < M; ++j) {
        int start = 0;
        for(int i = 1; i < N; ++i) {
            if(A[i-1][j] > A[i][j]) {
                S.insert(make_pair(start+1,i));
                start = i;
            }
        }
        S.insert(make_pair(start+1,N));
    }
    
    vector<ival> d;
    for(const ival& i : S) {
        if(d.size() == 0) d.push_back(i);
        else {
            if(check_enclosing(i,d.back())) {
                d.pop_back(); d.push_back(i);
            } else if(!check_enclosing(d.back(),i)) {
                d.push_back(i);
            }
        }
    }
   
    cin >> K;
    int n = d.size();
    for(int i = 0; i < K; ++i) {
        int l,r; cin >> l >> r;
        ival req = make_pair(l,r);
        size_t left = 0, right = n;
        while(right - left > 0) {
            size_t m = (left+right)/2;
            if(check_enclosing(d[m],req)) {
                left = m; break;
            }
            if(d[m].X > req.X) right = m;
            else if(d[m].X <= req.X) left = m+1;
        }
        if(check_enclosing(d[left],req)) 
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    
	return 0;
}
