#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
ll minimum;

vector<ll> primes;

void printFactorization(vector<pll>& fact) {
	for(int i = 0; i < fact.size(); i++) {
		cout << fact[i].first << "^" << fact[i].second << ", ";
	}
	cout << endl;
}

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

vector<ll> all_prime_divisor(set<ll> div) {
	vector<ll> p_div;
	for(ll d : div) {
		vector<pll> fact = factorize(d+1);
		if(fact.size() == 1 && fact[0].second == 1)
			p_div.push_back(d);
	}
	return p_div;
}

bool sub_from_fact(vector<pll>& fact, ll n) {
	vector<pll> n_fact = factorize(n);
	for(int i = 0; i < fact.size(); i++) {
		for(int j = 0; j < n_fact.size(); j++) {
			if(n_fact[j].first == fact[i].first && fact[i].second - n_fact[j].second < 0)
				return false;
		}
	}

	for(int i = 0; i < fact.size(); i++) {
		for(int j = 0; j < n_fact.size(); j++) {
			if(n_fact[j].first == fact[i].first)
				fact[i] = make_pair(fact[i].first,fact[i].second - n_fact[j].second);
		}
	}

	return true;

}

void add_to_fact(vector<pll>& fact, ll n) {
	vector<pll> n_fact = factorize(n);
	for(int i = 0; i < fact.size(); i++) {
		for(int j = 0; j < n_fact.size(); j++) {
			if(n_fact[j].first == fact[i].first)
				fact[i] = make_pair(fact[i].first,fact[i].second + n_fact[j].second);
		}
	}
}

ll value(vector<pll>& fact) {
	ll val = 1;
	for(int i = 0; i < fact.size(); i++)
		val *= pow(fact[i].first,fact[i].second);
	return val;
}

ll isValidNumber(vector<pll>& fact, set<ll>& cur_p) {
	for(int i = 0; i < fact.size(); i++) {
		if(fact[i].second > 0 && cur_p.find(fact[i].first) == cur_p.end())
			return -1;
	}


	ll val = 1;
	for(ll p : cur_p) {
		bool found = false;
		for(int i = 0; i < fact.size(); i++) {
			if(p == fact[i].first) {
				val *= pow(p,fact[i].second+1); found = true; break;
			}
		}	
		if(found) continue;
		val *= p;	
	}
	return val;
	
}

void search(vector<pll>& fact, vector<ll>& p_div, set<ll>& cur_p, int pos) {
	for(int i = pos; i < p_div.size(); i++) {
		ll n = p_div[i];
		if(sub_from_fact(fact,n)) {
			cur_p.insert(n+1);
			ll num = isValidNumber(fact,cur_p);
			if(num != -1) {
				minimum = min(num,minimum);
			}
			search(fact,p_div,cur_p,i+1);
			cur_p.erase(n+1);
			add_to_fact(fact,n);
		}
		else {
			if(value(fact) <= n)
				return;
		}
	}
}


int main() {

	primeSieve(100000);

	ll n, c = 1;
	while(cin >> n) {
		if(n == 0)
			break;

		vector<pll> fact = factorize(n);
		set<ll> div = all_divisor(n);
		vector<ll> p_div = all_prime_divisor(div);

		sort(fact.begin(),fact.end());
		
		set<ll> cur_p; minimum = LLONG_MAX;
		search(fact,p_div,cur_p,0);

		cout << "Case " << c << ": " << n << " " << minimum << endl;
		c++;

	}
	

	return 0;
}
