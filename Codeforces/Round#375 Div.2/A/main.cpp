#include <bits/stdc++.h>

using namespace std;


int main() {
    int x1, x2, x3; cin >> x1 >> x2 >> x3;
    int min1 = abs(x1-x2)+abs(x1-x3);
    int min2 = abs(x2-x3)+abs(x2-x1);
    int min3 = abs(x3-x1)+abs(x3-x2);
    
    cout << min(min1,min(min2,min3)) << endl;
    
	return 0;
}
