#include <bits/stdc++.h>

using namespace std;

class UnionFind {

public:
  UnionFind() {}
  
  void init(int N) {
    uf.assign(N,-1);
  }
  
  int findSet(int i) {
    if(uf[i] < 0) return i;
    uf[i] = findSet(uf[i]);
    return uf[i];
  }
  
  void linkSets(int i, int j) {
    if(abs(uf[i]) < abs(uf[j])) { 
      uf[j] += uf[i]; uf[i] = j; 
    } else {
      uf[i] += uf[j]; uf[j] = i; 
    }
  }
  
  void unionSets(int i, int j) {
    if(findSet(i) != findSet(j)) linkSets(findSet(i),findSet(j));
  } 
  
  int countSets(int n) {
    set<int> sets;
    for(int i = 0; i < n; i++) {
      sets.insert(findSet(i));
    }
    return sets.size();
  }
  
private:
  vector<int> uf;
};

typedef pair<double,double> point;
typedef pair<int,int> ii;
typedef vector<pair<double,ii>> graph;

UnionFind uf;
int N;

double distance(point& p1, point& p2) {
  return sqrt((p2.first-p1.first)*(p2.first-p1.first) + (p2.second-p1.second)*(p2.second-p1.second));
}

double buildMST(graph& g) {
  double mst_cost = 0; int M = g.size();
  sort(g.begin(),g.end());
  for(int i = 0; i < M; i++) {
    int u = g[i].second.first, v = g[i].second.second;
    if(uf.findSet(u) != uf.findSet(v)) {
      mst_cost += g[i].first;
      uf.unionSets(u,v);
    }
  }
  return mst_cost;
}

int main() {
  
  int test; cin >> test;
  int a = 1;
  while(test--) {
    double T;
    cin >> N >> T;
    uf.init(N);
    vector<point> c(N);
    for(int i = 0; i < N; ++i) {
      double x,y; cin >> x >> y;
      c[i] = make_pair(x,y);
    }
    
    graph g1, g2;
    for(int i = 0; i < N; i++) {
      for(int j = i+1; j < N; j++) {
	if(distance(c[i],c[j]) <= T)
	  g1.push_back(make_pair(distance(c[i],c[j]),make_pair(i,j)));
	else
	  g2.push_back(make_pair(distance(c[i],c[j]),make_pair(i,j)));
      }
    }
    
    int g1_mst_cost = round(buildMST(g1));
    int states = uf.countSets(N);
    int g2_mst_cost = round(buildMST(g2));
    
    cout << "Case #" << a << ": " << states << " " << g1_mst_cost << " " << g2_mst_cost << endl;
    a++;
  }
  
  return 0;
}
