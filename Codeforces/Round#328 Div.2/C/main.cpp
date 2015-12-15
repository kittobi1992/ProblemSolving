#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

ll gcd(ll a, ll b) {
  return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
  return a * (b / gcd(a,b));
}

bool overflow_check(ll a, ll b, ll c) {
  if(a > c/b)
    return false;
  return true;
}

int main() {
      
	ll t, w, b;
	cin >> t >> w >> b;
	ll lcm_wb = lcm(w,b);

	if(!overflow_check(w,b/gcd(w,b),t)) {
	  if(w > t && b > t) {
	    cout << "1/1" << endl;
	    return 0;
	  }
	  ll tie = min(w,b)-1;
	  ll gcd_tiet = gcd(tie,t);
	  cout << tie/gcd_tiet << "/" << t/gcd_tiet << endl;
	  return 0;
	}
	ll tie = (t/lcm_wb - 1)*min(w,b);
	tie += min(w,b)-1;
	tie += min((t-(t/lcm_wb)*lcm_wb)+1,min(w,b));
	ll gcd_tiet = gcd(tie,t);
	
	
	cout << tie/gcd_tiet << "/" << t/gcd_tiet << endl;

	return 0;
}
