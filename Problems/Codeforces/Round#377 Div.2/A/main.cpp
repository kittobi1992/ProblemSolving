#include <bits/stdc++.h>

using namespace std;

int main() {
    
    int K, R; cin >> K >> R;
    int shovels = 1;
    while(true) {
        int cost = shovels * K;
        if(cost % 10 == 0 || (cost-R) % 10 == 0) {
            cout << shovels << endl;
            return 0;
        }
        shovels++;
    }
    
	return 0;
}
