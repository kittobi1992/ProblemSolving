#include <bits/stdc++.h>

using namespace std;

#define INVALID LLONG_MAX

typedef long long ll;

struct figure {
  ll x,y;
  char f;
};

int N;
ll kx, ky;
vector<figure> fig;
bool used[3][3];


ll dist(const figure& fig) {
  return abs(kx-fig.x) + abs(ky-fig.y);
}

bool isOccupied(ll x, ll y) {
  return used[1+(x-kx)][1+(y-ky)];
}

void occupy(ll x, ll y) {
  if(x == INVALID) return;
  used[1+(x-kx)][1+(y-ky)] = 1;
}

pair<ll,ll> project(const figure& fig) {
  ll x = fig.x, y = fig.y;
  ll dx = (kx-x), dy = (ky-y);
  if(abs(dx) == abs(dy)) {
    return make_pair(x + (dx-dx/abs(dx)),y + (dy-dy/abs(dy)));
  } else if(dx == 0 || dy == 0) {
    if(dx == 0) return make_pair(x,y + (dy-dy/abs(dy)));
    else return make_pair(x + (dx-dx/abs(dx)),y);
  }
  else return make_pair(INVALID,INVALID);
}

int main() {
  
  ios::sync_with_stdio(false);
  
  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j) 
      used[i][j] = 0;
  used[1][1] = 1;
  
  cin >> N >> kx >> ky;
  fig.resize(N);
  for(int i = 0; i < N; ++i) cin >> fig[i].f >> fig[i].x >> fig[i].y;
  
  sort(fig.begin(),fig.end(),[&](const figure& fig1, const figure& fig2) {
    return dist(fig1) < dist(fig2);
  });
  
  for(int i = 0; i < N; ++i) {
//       cout << fig[i].x << " " << fig[i].y << " " << fig[i].f << " " << dist(fig[i]) << endl;
      ll x = fig[i].x, y = fig[i].y;
      ll dx = (kx-x), dy = (ky-y);
      ll xs = project(fig[i]).first, ys = project(fig[i]).second;
      if((fig[i].f == 'B' || fig[i].f == 'Q') && abs(dx) == abs(dy)) {
        if(!isOccupied(xs,ys)) {
          cout << "YES" << endl;
          return 0;
        }
      } else if((fig[i].f == 'R' || fig[i].f == 'Q') && (abs(dx) == 0 || abs(dy) == 0)) {
        if(!isOccupied(xs,ys)) {
          cout << "YES" << endl;
          return 0;
        }
      }
      occupy(xs,ys);
  }
  
  cout << "NO" << endl;
  
	return 0;
}
