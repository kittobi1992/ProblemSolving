#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

#define MAX 1000001

typedef long long ll;
typedef pair<ll,ll> pll;
ll r1,c1,r2,c2,p;

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

ll create_number(vector<ll>& frog_prime, vector<ll>& count) {
	ll num = 1;
	for(ll i = 0; i < frog_prime.size(); i++)
		num *= pow(frog_prime[i],count[i]);
	return num;	
}

int main() {
	

	primeSieve(10001);
	
	ll test;
	cin >> test;
	while(test--) {
		cin >> r1 >> c1 >> r2 >> c2 >> p;
		set<ll> frog_prime;
		for(int i = 0; i < p; i++) {
			ll fp; cin >> fp;
			frog_prime.insert(fp);
		}

		/*vector<ll> mul(MAX,0);
		for(ll i = 2; i <= (MAX-1)/2; i++) {
			for(ll j = 2; j*i < MAX; j++) {
				mul[i*j] += (j-1) - mul[i];
			}
		}*/		


		ll corn = 0;
		for(ll n = c1; n <= c2; n++) {
			vector<pll> fact = factorize(n);
			ll sum = 1;
			bool all = true, one = false; 
			for(ll i = 0; i < fact.size(); i++) {
				sum *= pow(fact[i].first,fact[i].second - 1)*(fact[i].first - 1);	
			}
			if(all)
				corn--;		
			corn += 2*(n-sum);
		}
		

		cout << corn << endl;

	}

	return 0;
}
