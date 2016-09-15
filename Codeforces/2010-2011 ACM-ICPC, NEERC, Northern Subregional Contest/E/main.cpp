#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ifstream fin("explicit.in");
ofstream fout("explicit.out");

#define pb push_back

void run(){

	ll n = 10;
	vi al(n);
	for(int i = 0; i < n; i++) fin >> al[i];

	ll sum = 0;
	ll t = 0;
	for(int i = 0; i< n; i++){
		for(int j = i+1; j < n; j++){
			sum ^= (al[i] || al[j]);
			t++;
		}
	}

	//cout << t << endl;
	t = 0;

	for(int i = 0; i< n; i++){
		for(int j = i+1; j < n; j++){
			for(int k = j+1; k < n; k++){
				sum ^= (al[i] || al[j] || al[k]);
				t++;
			}
		}
	}

	//cout << t << endl;

	fout << sum << endl;
}

int main(){

	run();
}
