#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> graph;

int N,M;
graph g;
vector<int> in, out;
vector<int> euler;


void eulerTour(int start) {
  stack<int> s;
  int cur = start;
  do {
    if(g[cur].size() == 0) {
      euler.push_back(cur);
      if(!s.empty()) { cur = s.top(); s.pop(); }
      if(s.empty() && g[cur].size() == 0) euler.push_back(cur);
    } else {
      s.push(cur);
      auto edge = g[cur].begin();
      swap(edge,--g[cur].end());
      g[cur].pop_back();
      cur = *edge;
    }
  } while(!s.empty());
}

int main() {

  while(cin >> N >> M) {
    if(N == 0 && M == 0) break;
    
    euler.clear();
    g.assign(N,vector<int>()); in.assign(N,0); out.assign(N,0);
    for(int i = 0; i < M; ++i) {
      int u, v; cin >> u >> v;
      g[u].push_back(v);
      out[u]++; in[v]++;
    }
    
    int cnt = 0;
    vector<int> start(2,-1);
    for(int i = 0; i < N; ++i) {
      if(in[i] != out[i]) {
        if(cnt < 2) start[cnt] = i;
        cnt++;
      }
    }
    
    if(cnt == 0) {
      int s = 0;
      for(; s < N; ++s) {
        if(g[s].size() > 0) break;
      }
      eulerTour(s);
    } else if(cnt == 1) {
      int u = start[0];
      if(out[u] == in[u]+1) eulerTour(u);
      else {
        cout << "Impossible" << endl;
        continue;
      }
    } else if(cnt == 2) {
      int u = start[0], v = start[1];
      if(out[u] == in[u]+1 && in[v] == out[v] +1) {
        int s = u; eulerTour(s);
      } else if(out[v] == in[v]+1 && in[u] == out[u] +1) {
        int s = v; eulerTour(s);
      }
      else {  
        cout << "Impossible" << endl;
        continue;
      }
    } else {
      cout << "Impossible" << endl;
      continue;
    }
    
    reverse(euler.begin(),euler.end());
    if(euler.size() != M+1) {
      cout << "Impossible" << endl;
      continue;
    }
    
    for(int i = 0; i < euler.size(); ++i) cout << euler[i] << (i == euler.size()-1 ? "\n" : " ");
    
    
  }
  
	return 0;
}
