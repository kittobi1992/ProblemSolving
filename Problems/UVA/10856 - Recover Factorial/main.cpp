#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define PRIME_MAX 3000000

//stores the smallest prime divisor for each i <= PRIME_MAX <= 10^8
ll sd[PRIME_MAX+1];

ll sum_factorial[PRIME_MAX+1];

//precalculates the smallest primefactor for each i <= PRIME_MAX
//O(n*log(log(n)))
void precalc() {
	sd[0] = sd[1] = 0;
	for(ll i = 2; i <= PRIME_MAX; i++) sd[i] = (i % 2 == 0 ? 2 : i);
	
	for(ll i = 3; i * i <= PRIME_MAX; i+=2) {
		if(sd[i] == i) {
			for(ll n = i*i; n <= PRIME_MAX; n += (i<<1)) {
				if(sd[n] == n) sd[n] = i;
			}
		}
	}
}

void calculateSumOfFactorials() {
  sum_factorial[0] = sum_factorial[1] = 0;
  
  for(ll i = 2; i <= PRIME_MAX; ++i) sum_factorial[i] = sum_factorial[i/sd[i]] + 1;
  for(ll i = 2; i <= PRIME_MAX; ++i) sum_factorial[i] += sum_factorial[i-1];
}

int main() {
  
  precalc();
  calculateSumOfFactorials();
  
  ll n;
  int c = 1;
  while(cin >> n) {
    if(n < 0)
      break;
    
    ll *res = lower_bound(sum_factorial, sum_factorial + PRIME_MAX + 1, n);
    cout << "Case " << c << ": ";
    if(*res == n) cout << (res-sum_factorial) << "!" << endl;
    else cout << "Not possible." << endl;
    
    c++;
  }
  
  return 0;
}
