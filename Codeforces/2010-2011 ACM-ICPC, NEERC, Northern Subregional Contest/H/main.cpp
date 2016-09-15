#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

ifstream fin("horrible.in");
ofstream fout("horrible.out");

#define pb push_back
#define snd second
#define fst first

vi vis;

void run(){

	ll n;
	fin >> n;


	if(n == 1){
		fout << "1" << endl;
		fout << "1 0" << endl;
		return;
	}

	vii eps;

	eps.pb({2, -1});	
	for(int f = 0; f < n-1; f++){
		eps.pb({f+1, 0});

		ll cf = 0;
		ll ncf = 0;
		for(int i = 0; i < n-1; i++){
			if(cf == f) cf++;
			eps.pb({cf+1, f+1});
			if(ncf == (f+1)) ncf++;			
			eps.pb({ncf+1, -(f+1+1)});
			cf++;
			ncf++;
		}
	}
	eps.pb({n, 0});
	eps.pb({1, n});


	fout << eps.size() << endl;
	for(size_t i = 0; i < eps.size(); i++){
		fout << eps[i].fst << " " << eps[i].snd << endl;
	}

}



int main(){

	run();
}
