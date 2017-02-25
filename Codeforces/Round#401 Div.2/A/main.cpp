#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ll N,X; cin >> N >> X;
    
    vector<int> v1 = {0,1,2,2,1,0};
    vector<int> v2 = {1,0,0,1,2,2};
    vector<int> v3 = {2,2,1,0,0,1};
    if(v1[N % 6] == X) cout << "0" << endl;
    else if(v2[N % 6] == X) cout << "1" << endl;
    else if(v3[N % 6] == X) cout << "2" << endl;
    
	return 0;
}
