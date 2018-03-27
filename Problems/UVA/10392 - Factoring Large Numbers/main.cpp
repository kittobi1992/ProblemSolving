#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 1000001
vector<ll> primes;
typedef pair<ll,ll> ii;

void initializePrimes() {
  bitset<N> isPrime; isPrime.set();
  isPrime[0] = isPrime[1] = 0;
  for(ll i = 2; i < N+1; i+=2) {
      if(isPrime[i]) {
	  for(ll j = i*i; j >= 0 && j < N+1; j+=i) isPrime[j] = 0;
	  primes.push_back(i);
      }
      if(i == 2) i--;
  }
}

vector<ii> factorize(ll n) {
  vector<ii> fact; ll num = n, i = 0, c = 0;
  while(num != 1) {
    if(num % primes[i] == 0) {
      c++; num /= primes[i];
    } else {
      if(c > 0)
	fact.push_back(make_pair(primes[i],c));
      i++; c = 0;
      if(primes[i]*primes[i] > num || i == primes.size()) break;
    }
  }
  if(num != 1) fact.push_back(make_pair(num,c+1));
  return fact;
}

int main() {
  initializePrimes();
  ll n;
  while(cin >> n) {
    if(n == -1)
      return 0;
    
    vector<ii> fact = factorize(n);
    ll num = 1;
    for(int i = 0; i < fact.size(); i++) {
      for(int j = 0; j < fact[i].second; j++)
	cout << "    " << fact[i].first << endl;
    }
    cout << endl;
  }  
}
