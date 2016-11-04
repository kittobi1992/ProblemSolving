#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

ll mat[110][110];
ll wins[110][110];

void run(){
	
	ll r, c;
	cin >> r >> c;
	

	
	for(int j = 0; j < r; j++){
		for(int i = 0; i < c; i++){
			cin >> mat[j][i];
		}	
	}

	for(int j = 0; j < r; j++){
		ll maxi = -1;
		for(int i = 0; i < c; i++){
			if(mat[j][i] > maxi){
				wins[j][i]++;
				maxi = mat[j][i];
			}
		}	
	}
	
	for(int j = 0; j < r; j++){
		ll maxi = -1;
		for(int i = c-1; i >= 0; i--){
			if(mat[j][i] > maxi){
				wins[j][i]++;
				maxi = mat[j][i];
			}
		}
	}

	for(int i = 0; i < c; i++){
		ll maxi = -1;
		for(int j = r-1; j >= 0; j--){
			if(mat[j][i] > maxi){
				wins[j][i]++;
				maxi = mat[j][i];
			}
		}
	}
	

	for(int i = 0; i < c; i++){
		ll maxi = -1;
		for(int j = 0; j < r; j++){
			if(mat[j][i] > maxi){
				wins[j][i]++;
				maxi = mat[j][i];
			}
		}
	}
	
	ll am = 0;
	for(int j = 0; j < r; j++){
		for(int i = 0; i < c; i++){
			am += wins[j][i];
		}	
	}
	
	cout << am << endl;

}


int main(){
	freopen("lucky.in", "r", stdin);
	freopen("lucky.out", "w", stdout);

	run();
}
