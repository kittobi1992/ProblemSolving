#include <bits/stdc++.h>

using namespace std;

#define MAXN 200005
#define INF 2000000005LL

typedef long long ll; 
typedef pair<ll,ll> pll;

ll N,M,K,X,S;
ll a[MAXN], b[MAXN], c[MAXN], d[MAXN];
pll e[MAXN];

ll calc_time(int spell) {
  if(b[spell] > S) return LLONG_MAX;
  ll time = 0, potion = 0;
  ll x = a[spell];
  ll mana = S-b[spell];
  auto it = upper_bound(e,e+K,make_pair(mana,INF));
  
  ll p = 0;
  if(it == e+K || (it->first > mana && it != e)) it--;
  if(it->first <= mana) { p = it->second; }
  
  potion = p;
  time = x*(N-potion);
  
//   cout << "p="<<p << " x=" << x << " N-p=" << (N-p) << " Mana=" << mana << " Time=" << time << endl;

  return time;
}

int main() {
  ios::sync_with_stdio(false);
  
  cin >> N >> M >> K >> X >> S;
  for(int i = 0; i < M; ++i) cin >> a[i];
  for(int i = 0; i < M; ++i) cin >> b[i];
  for(int i = 0; i < K; ++i) cin >> c[i];
  for(int i = 0; i < K; ++i) cin >> d[i];
  for(int i = 0; i < K; ++i) e[i] = make_pair(d[i],c[i]);
  a[M] = X; b[M] = 0;
  M++;
  
  ll min_time = LLONG_MAX;
  for(int i = 0; i < M; ++i) {
    ll time = calc_time(i);
    if(time < min_time) min_time = time;
  }
  
  cout << min_time << endl;
    
	return 0;
}
