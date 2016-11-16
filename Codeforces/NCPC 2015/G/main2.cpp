#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define MAXN 10000

typedef pair<int,int> ii;

bool MAP[10001][10001];

int main() {
    
    for(int i = 0; i <= 10000; ++i)
        for(int j = 0; j <= 10000; ++j)
            MAP[i][j] = 0;
    
   int N; cin >> N;
   vector<ii> g(N,make_pair(0,0));
   for(int i = 0; i < N; ++i) cin >> g[i].x >> g[i].y;
   
   int M; cin >> M;
   vector<ii> s(M,make_pair(0,0));
   vector<int> r(M);
   for(int i = 0; i < M; ++i) cin >> s[i].x >> s[i].y >> r[i];
   
   for(int i = 0; i < M; ++i) {
       int X = s[i].x, Y = s[i].y, R = r[i];
       for(int k = max(0,X-R); k <= min(MAXN,X+R); ++k) {
            for(int l = max(0,Y-R); l <= min(MAXN,Y+R); ++l) {
                if((X-k)*(X-k) + (Y-l)*(Y-l) <= R*R) MAP[k][l] = 1;
            }
       }
   }
   
   int num = 0;
   for(int i = 0; i < N; ++i) {
       int X = g[i].x, Y = g[i].y;
       if(!MAP[X][Y]) num++;
   }
   
   
   cout << num << endl;
       
    
    return 0;
}
