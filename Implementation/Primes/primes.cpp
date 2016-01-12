#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 10000001
vector<ll> primes;
typedef pair<int,int> ii;

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
  }
  if(num != 1) fact.push_back(make_pair(num,c+1));
  return fact;
}

int main() {
  primeSieve();
  ll n = 21;
  vector<ii> fact = factorize(n);
  ll num = 1;
  for(int i = 0; i < fact.size(); i++) {
    num *= pow(fact[i].first,fact[i].second);
    cout << fact[i].first << "^" << fact[i].second << (i == fact.size()-1 ? " = " : " * ");
  }
  cout << num << (n == num ? " = " : " != ") << n << endl;
}
