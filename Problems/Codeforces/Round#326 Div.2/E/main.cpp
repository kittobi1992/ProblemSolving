#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> graph;
typedef pair<int,vector<int>> pv;

#define A 10

int n,m,q;
int MAX_LOG;
graph g;
graph p;

vector<vector<pv>> parent;
vector<int> h;


vector<int> merge(vector<int>& a, vector<int>& b) {
  int i = 0; int j = 0;
  vector<int> m;
  while((i < a.size() || j < b.size()) && m.size() < A) {
    if(j == b.size() || (i < a.size() && a[i] < b[j])) {
      if(m.size() == 0 || m.back() != a[i])
	m.push_back(a[i++]);
      else i++;
    } else {
      if(m.size() == 0 || m.back() != b[j])
	m.push_back(b[j++]);
      else j++;
    }
  }
  return m;
}

void dfs(int v, int par = -1) {
  parent[v][0] = make_pair(par,(par != -1 ? merge(p[par],p[v]) : p[v]));
  if(par + 1)
    h[v] = h[par] + 1;
  for(int i = 1; i < MAX_LOG; i++) {
      if(parent[v][i-1].first + 1) {
	int i_parent = parent[parent[v][i-1].first][i-1].first;
	parent[v][i] = make_pair(i_parent, (i_parent != -1 ? merge(parent[v][i-1].second,
				    parent[parent[v][i-1].first][i-1].second) : parent[v][i-1].second));
      }
  }
  for(int u : g[v]) {
    if(par - u)
      dfs(u,v);
  }
}

vector<int> LCA(int u, int v) {
  if(h[v] < h[u])
    swap(u,v);
  vector<int> l;
  for(int i = MAX_LOG-1; i >= 0; i--) {
    if(parent[v][i].first + 1 && h[parent[v][i].first] >= h[u]) {
      l = merge(l,parent[v][i].second);
      v = parent[v][i].first;
    }
  }
  if(v == u)
    return l;
  for(int i = MAX_LOG-1; i >= 0; i--) {
    if(parent[v][i].first - parent[u][i].first) {
      vector<int> m = merge(parent[v][i].second,parent[u][i].second);
      l = merge(l,m);
      v = parent[v][i].first; u = parent[u][i].first;
    }
  }
  vector<int> m = merge(parent[v][0].second,parent[u][0].second);
  return merge(m,l);
}

int main() {

	cin >> n >> m >> q;
	MAX_LOG = max((int)ceil(log2(n)),1);
	g.resize(n); p.resize(n); h.assign(n,0);
	parent.assign(n,vector<pv>(MAX_LOG, make_pair(-1,vector<int>())));
	for(int i = 0; i < n-1; i++) {
	  int u,v; cin >> u >> v;
	  g[--u].push_back(--v);
	  g[v].push_back(u);
	}
	
	for(int i = 1; i <= m; i++) {
	  int c; cin >> c;
	  p[--c].push_back(i);
	}

	dfs(0);
	
	for(int i = 0; i < q; i++) {
	  int u,v,a; cin >> u >> v >> a;
	  vector<int> l;
	  if(u != v)
	    l = LCA(--u,--v);
	  else
	    l = p[--u];
	  cout << min((int)l.size(),a);
	  for(int j = 0; j < min((int)l.size(),a); j++)
	    cout << " " << l[j];
	  cout << endl;
	}
  
	return 0;
}
