#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

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

set<ll> all_divisor(ll n) {
	set<ll> div;
	vector<pll> factor = factorize(n);
	vector<ll> max_c(factor.size(),0);
	vector<ll> cur_c(factor.size(),0);
	for(int i = 0; i < factor.size(); i++)
		max_c[i] = factor[i].second;
	cur_c[0] = 1;
	while(true) {
		ll d = 1;
		for(int i = 0; i < factor.size(); i++) {
			d *= pow(factor[i].first,cur_c[i]);
		}
		div.insert(d);
		int i = 0; cur_c[i]++;
		while(i < factor.size() && cur_c[i] > max_c[i]) {
			cur_c[i++] = 0;
			if(i < factor.size())
				cur_c[i]++;
		}
		if(i == factor.size()) break;
	}

	return div;
}



int main() {

	primeSieve(10000000);

	ll n;
	while(true) {
		cin >> n;
		if(n == 0) break;
		if(n == 1) {
			cout << "1 0" << endl;
			continue;
		}
		set<ll> div = all_divisor(n);
		ll trailing_sum = 0;
		for(ll d : div) {
			ll i = 1;
			while(n % ((ll) pow(d,i)) == 0) {
				trailing_sum++; i++;
			}
		}

		cout << n << " " << trailing_sum << endl;

	}
	

	return 0;
}
