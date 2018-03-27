#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define MAX 1000001

bool isPrime[MAX];
int prefix_sum[MAX];

void initializePrimes() {
  memset(isPrime,1,sizeof(isPrime));
  isPrime[0] = false; isPrime[1] = false;
  for(ll i = 2; i*i < MAX; i++) {
      if(isPrime[i]) {
	  for(ll j = i*2; j < MAX; j+=i) isPrime[j] = false;
      }
  }
}

bool isDigitPrime(int n) {
  int sum = 0; int num = n;
  while(num != 0) {
    sum += num % 10;
    num /= 10;
  }
  return isPrime[n] && isPrime[sum];
}

void initializeDigitPrimes() {
  memset(prefix_sum,0,sizeof(prefix_sum));
  for(int i = 2; i < MAX; i++) {
    prefix_sum[i] = prefix_sum[i-1] + isDigitPrime(i);
  }
}

int main() {
  initializePrimes();
  initializeDigitPrimes();
  ios::sync_with_stdio(false);
  int test; cin >> test;
  while(test--) {
    int t1, t2; cin >> t1 >> t2;
    if(t1 == 0) t1++;
    cout << prefix_sum[t2] - prefix_sum[t1-1] << endl;
  }
  return 0;
}
