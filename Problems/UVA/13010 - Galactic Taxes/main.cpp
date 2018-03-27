#include <bits/stdc++.h>

using namespace std;


typedef pair<double,int> di;

template<typename T> 
using Graph = vector<vector<T>>;

#define DOUBLE_MAX numeric_limits<double>::max()/2.0
#define EPS 1e-10

priority_queue<di,vector<di>,greater<di>> pq;
Graph<int> g; Graph<double> A, B, C;
vector<double> dist;
int n, m;

void initialize(int N) {
	dist.assign(N,DOUBLE_MAX);
	priority_queue<di,vector<di>,greater<di>> empty_pq; swap(pq,empty_pq);
}



double dijkstra(int s, int t) {
	initialize(n);
	dist[s] = 0; pq.push(make_pair(0,s));
	while(!pq.empty()) {
		int cur_node = pq.top().second; double cur_dist = pq.top().first; pq.pop();
		if(cur_dist > dist[cur_node]) continue;
		if(cur_node == t) break;
		
		for(int i = 0; i < g[cur_node].size(); i++) {
			int u = g[cur_node][i]; double c = C[cur_node][i];
			if(dist[cur_node] + c < dist[u]) {
				dist[u] = dist[cur_node] + c; pq.push(make_pair(dist[u],u));
			}
		}
	}
	return dist[t];
}  

double calculateTaxes(double t) {

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < g[i].size(); ++j) {
			C[i][j] = A[i][j]*t + B[i][j];	
		}
	}
	
	return dijkstra(0,n-1);
}

int main() {
  
	while(cin >> n >> m) {
			g.assign(n,vector<int>());
			A.assign(n,vector<double>());
			B.assign(n,vector<double>());
			C.assign(n,vector<double>());
			for(int i = 0; i < m; ++i) {
				int x, y; double a, b;
				cin >> x >> y >> a >> b;
				--x; --y;
				g[x].push_back(y); g[y].push_back(x);
				A[x].push_back(a); A[y].push_back(a);
				B[x].push_back(b); B[y].push_back(b);
				C[x].push_back(b); C[y].push_back(b);
			}
			
			double l = 0.0, r = 1440.0;
			double res = 0.0;
			while(abs(r-l) > EPS) {
				double m1 = l + (r-l)/3.0;
				double m2 = r - (r-l)/3.0;
			 	double res1 = calculateTaxes(m1), res2 = calculateTaxes(m2);
				res = max(res, max(res1,res2));
				if(res1 < res2) l = m1;
				else r = m2;
				if(abs(res1 - res2) < EPS) break;
			}

         cout << fixed << setprecision(5) << res << endl;
	}
	
  	return 0;
}
