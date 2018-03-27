#include <bits/stdc++.h>

using namespace std;

#define INF INT_MAX/4
#define MAXN 105

int g[MAXN][MAXN];

int main() {
  memset(g,0,sizeof(g));
  int test; cin >> test;
  while(test--) {
    int n,m,e,t; cin >> n >> e >> t >> m;
    e--;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
	g[i][j] = INF;
	
    for(int i = 0; i < m; i++) {
      int a,b,c; cin >> a >> b >> c;
      g[--a][--b] = c;
    }
    
    for(int i = 0; i < n; i++)
      g[i][i] = 0;
    
    for(int k = 0; k < n; k++)
      for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
	  g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	
    
    int mice = 0;
    for(int i = 0; i < n; i++)
      if(g[i][e] <= t)
	mice++;
	
    cout << mice << "\n" << (test ? "\n" : "");
      
  }
  
  return 0;
}
