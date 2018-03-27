#include <bits/stdc++.h>

using namespace std;

string num; int K;

int main() {
    cin >> num >> K;
    int res = 0, cnt = 0;
    for(int i = num.size()-1; i >= 0; --i) {
        if(K == cnt) break;
        if(num[i] != '0') res++;
        else cnt++;
    }
    
    if(cnt + res == num.size()) cout << num.size()-1 << endl;
    else cout << res << endl;
    
	return 0;
}
