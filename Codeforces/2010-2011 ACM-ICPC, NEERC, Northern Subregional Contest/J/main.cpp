#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;

vvii adj1;
vvii adj2;

int main() {
  
	ll n, s, t;
	cin >> n >> s >> t;
	s--; t--;

	ll m1;
	cin>> m1;
	adj1 = vvii(n);
	for(int i = 0; i<m1; i++){
		ll a, b, l;
		cin>> a >> b >> l;
		a--; b--;
		adj1[a].pb({b, l});
		adj1[b].pb({a, l});
	}

	ll m2;
	cin>> m2;
	adj2 = vvii(n);
	for(int i = 0; i<m2; i++){
		ll a, b, l;
		cin>> a >> b >> l;
		a--; b--;
		adj2[a].pb({b, l});
		adj2[b].pb({a, l});
	}


	vi dis1(n, 10000000000LL);

	priority_queue<ii> pq;
	pq.push({0, t});
	while(!pq.empty()){
		ii top = pq.top();
		ll l = top.fst;
		ll id = top.snd;
		pq.pop();

		if(l >= dis[id]) continue;

		for(int i = 0; i < adj1[id].size(); i++){
			pq.push({l+adj1[id][i].snd, adj[id][i].fst});
		}
	}

  return 0;
}
