#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
string a,b;

ll calc_pos(ll pos, ll l, bool one) {
    if(!one) return pos;
    else return pos + 2*(l-pos)-1;
}

int main() {
    
    cin >> N >> a >> b;
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    
    ll p2 = 1;
    ll pos1 = 0, pos2 = 0;
    for(int i = 0; i < N; ++i) {
        pos1 = calc_pos(pos1,p2,a[i] == '1' ? true : false);
        pos2 = calc_pos(pos2,p2,b[i] == '1' ? true : false);
        p2 *= 2;
    }
    cout << (pos2 - pos1)-1 << endl;
    
	return 0;
}
