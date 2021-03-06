#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define MAX_SEARCH 1000

typedef long long ll;
typedef pair<ll,ll> pll;

vector<ll> primes;

void primeSieve(ll n) {
	vector<bool> isPrime(n,true);
	for(ll i = 2; i < n; i += 2) {
		if(isPrime[i]) {
			primes.push_back(i);
			if(i*i <= n) {
				for(ll j = i; i*j < n; j+=2) isPrime[i*j] = false; 
			}
		}
		if(i == 2) i--;
	}
}

vector<pll> factorize(ll n) {
	unordered_map<ll,ll> factor;
	ll num = n;
	int pos = 0;
	while(num != 1) {
		if(num % primes[pos] == 0) {
			num /= primes[pos];
			factor[primes[pos]]++;
		}
		else pos++;
		if(primes[pos]*primes[pos] > num) break;
	}
	if(num != 1) factor[num]++;
	
	vector<pll> fact;
	for(auto f : factor)
		fact.push_back(make_pair(f.first,f.second));

	return fact;
}

int main() {

	primeSieve(100000);
	
	ll n; cin >> n;
	vector<pll> fact = factorize(n);
	if(fact.size() == 1 && fact[0].second == 1) {
		cout << "1" << endl << n << endl;
		return 0;
	}

	ll first_prime = 4;
	fact = factorize(first_prime);
	int c = 0;
	while(fact.size() != 1 || fact[0].second != 1) {
		first_prime = (max(((ll)3),n - ((ll)MAX_SEARCH)) + rand() % min(n-3,((ll)MAX_SEARCH))) % n;
		fact = factorize(first_prime);
		c++;
	}
	ll nn = n-first_prime;


	if(nn == 2) {
		cout << "2" << endl << "2 " << first_prime << endl;
		return 0;
	}


	ll second_prime = 0, third_prime = 0;
	bool found = false;
	for(int i = 0; i < primes.size(); i++) {
		for(int j = i; j < primes.size(); j++) {
			if(primes[i] + primes[j] == nn) {
				second_prime = primes[i]; third_prime = primes[j]; found = true; break;
			}
			if(found)
				break;
		}
	}

	cout << "3\n" << first_prime << " " << second_prime << " " << third_prime << endl;
	return 0;

}
