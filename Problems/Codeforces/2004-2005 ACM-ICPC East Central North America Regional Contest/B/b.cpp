#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;

int n,m,d;

vector<int> isPrime;

void primeSieve (ll n) {
	isPrime.assign(n,true);
	for(ll i = 2; i < n; i+=2) {
		if(isPrime[i]) {
			if(i*i <= n) {
				for(ll j = i; i*j < n; j++) isPrime[i*j] = false;
			}
		}
		if(i == 2) i--;
	}
}

bool isAntiPrime(vector<int>& anti_prime) {
	int sum = anti_prime[anti_prime.size()-1];
	for(int i = anti_prime.size()-2; i >= max(0,((int)anti_prime.size()-d)); i--) {
		sum += anti_prime[i];
		if(isPrime[sum]) {
			return false;
		}
	}
	return true;
}

bool search(int j, vector<int>& anti_prime, vector<bool>& used) {
	if(j == m-n+1) {
		return true;
	}

	for(int i = n; i <= m; i++) {
		if(!used[i]) {	
			anti_prime.push_back(i);
			used[i] = true;
			if(isAntiPrime(anti_prime)) {
				if(search(j+1,anti_prime,used))
					return true;
			}
			used[i] = false;
			anti_prime.pop_back();
		}
	}
	return false;

}

int main() {
	primeSieve(10000);

	while (cin >> n >> m >> d) {
   		if(n == 0 && m == 0 && d == 0)
			break;

		bool found = false;
		for(int i = n; i <= m; i++) {
			vector<bool> used(m+1,false);
			vector<int> anti_prime;
			used[i] = true;
			anti_prime.push_back(i);
			if(search(1,anti_prime,used)) {
				for(int i = 0; i < anti_prime.size()-1; i++) {
					cout << anti_prime[i] << ",";
				}
				cout << anti_prime[anti_prime.size()-1] << endl;
				found = true;
				break;
			}
		}
		if(!found) {
			cout << "No anti-prime sequence exists." << endl;
		}

	}
	return 0;
}
