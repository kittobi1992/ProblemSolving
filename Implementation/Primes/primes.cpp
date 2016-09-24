#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 10000000
vector<ll> primes;
typedef pair<int,int> ii;
ll smallest_divisor[N+1];

//Finds all primes number between 0..N
//Use this method for N < 10000000 to avoid memory access errors
void primeSieve() {
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

//Factorize a number n in its prime factors
//Call primeSieve-method before with N > sqrt(n)
//Return: Returns a vector of pairs, where the first entry in the pair is
//the prime factor p and the second counts how many times p divides n
vector<ii> factorize(ll n) {
  vector<ii> fact; ll num = n, i = 0, c = 0;
  while(num != 1) {
    if(num % primes[i] == 0) {
      c++; num /= primes[i];
    } else {
      if(c > 0)
	fact.push_back(make_pair(primes[i],c));
      i++; c = 0;
      if(primes[i]*primes[i] > num) break;
    }
    if(num == 1 && c > 0) fact.push_back(make_pair(primes[i],c));
  }
  if(num != 1) fact.push_back(make_pair(num,c+1));
  return fact;
}

//@Thanks to JBatzill: https://github.com/JBatzill/PCR/tree/master/number%20theory/factorization/smallest_prime_divisor
//precalculates the smallest prime divisor for each 0..N
//Running Time: O(n*log(log(n)))
void precalcSmallestPrimeDivisor() {
	smallest_divisor[0] = smallest_divisor[1] = 0;
	for(ll i = 2; i <= N; i++) smallest_divisor[i] = (i % 2 == 0 ? 2 : i);
	
	for(ll i = 3; i * i <= N; i+=2) {
		if(smallest_divisor[i] == i) {
			for(ll n = i*i; n <= N; n += (i<<1)) {
				if(smallest_divisor[n] == n) smallest_divisor[n] = i;
			}
		}
	}
}

//@Thanks to JBatzill: https://github.com/JBatzill/PCR/tree/master/number%20theory/factorization/smallest_prime_divisor
//Fast factorization of n (Precondition: n <= N)
//Running Time: O(log(n))
vector<ll> fastFactorize(int n) {
	vector<ll> res;
	while(n > 1) {
		res.push_back(smallest_divisor[n]);
		n /= smallest_divisor[n];
	}
	return res;
}

int main() {
  precalcSmallestPrimeDivisor();
  ll n = 1052;
  vector<ll> fact = fastFactorize(n);
  ll num = 1;
  for(int i = 0; i < fact.size(); i++) {
    num *= fact[i];
    cout << fact[i] << (i == fact.size()-1 ? " = " : " * ");
  }
  cout << num << (n == num ? " = " : " != ") << n << endl;
}
