#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

int main() {

   ll l1, r1, l2, r2, k;
   cin >> l1 >> r1 >> l2 >> r2 >> k;
   
   ll l = max(l1,l2);
   ll r = min(r1,r2);
   
   if(l > r) {
        cout << "0" << endl;
        return 0;
   }
   ll time = 0;
   if(l <= k && r >= k) time = (r-l);
   else time = (r-l+1);
   
   cout << time << endl;
    
	return 0;
}
