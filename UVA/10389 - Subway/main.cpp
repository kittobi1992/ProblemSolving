#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define INF DBL_MAX/2

typedef pair<int,int> ii;
typedef pair<double,int> di;
typedef vector<vector<di>> graph;

priority_queue<di,vector<di>,greater<di>> pq;
vector<double> dist;

vector<int> split (string &s, string delim) { // zerlegt s anhand aller Zeichen in delim
  vector<int> result ; char* token ;
  token = strtok ((char*)s.c_str() , (char*) delim.c_str());
  while (token != NULL) {
    result.push_back(stoi(string(token)));
    token = strtok (NULL, (char*) delim.c_str());
  }
  return result;
}

void initialize(int N) {
  dist.assign(N,INF);
  priority_queue<di,vector<di>,greater<di>> empty_pq;
  swap(pq,empty_pq);
}

double dijkstra(graph& g, int s, int t) {
  initialize(g.size());
  dist[s] = 0; pq.push(make_pair(0,s));
  while(!pq.empty()) {
    int cur_node = pq.top().second; double cur_dist = pq.top().first; pq.pop();
    if(cur_dist > dist[cur_node]) continue;
    if(cur_node == t) break;
    
    for(int i = 0; i < g[cur_node].size(); i++) {
      int u = g[cur_node][i].second; double c = g[cur_node][i].first;
      if(dist[cur_node] + c < dist[u]) {
	dist[u] = dist[cur_node] + c; pq.push(make_pair(dist[u],u));
      }
    }
  }
  
  return dist[t];
}

double distance(ii p1, ii p2, bool walk) {
  return hypot((double)(p1.first-p2.first),(double)(p1.second-p2.second))*6.0/
	  (1000.0*(walk ? 1.0 : 4.0));
}

void addNodes(int N, graph& g) {
  for(int i = 0; i < N; i++)
    g.push_back(vector<di>(0));
}

void addEdge(graph& g, vector<ii>& p, int u, int v, bool walk) {
  g[u].push_back(make_pair(distance(p[u],p[v],walk),v));
}

int main() {
      string line; getline(cin,line);
      int test = split(line," ")[0];
      getline(cin,line);
      while(test--) {
	vector<ii> point; graph g; getline(cin,line);
	vector<int> init = split(line," ");
	ii home = make_pair(init[0],init[1]), school = make_pair(init[2],init[3]);
	point.push_back(home); point.push_back(school);
	addNodes(2,g);
	
	while(getline(cin,line) && line.compare("") != 0) {
	  vector<int> sub = split(line, " ");
	  for(int i = 0; i < sub.size()-2; i+=2)
	    point.push_back(make_pair(sub[i],sub[i+1]));
	  int start = g.size()+1;
	  addNodes((sub.size()-2)/2,g);
	  for(int i = start; i < g.size(); i++) {
	    addEdge(g,point,i-1,i,false);
	    addEdge(g,point,i,i-1,false);
	  }
	}
	
	for(int i = 0; i < g.size(); i++) {
	  for(int j = i+1; j < g.size(); j++) {
	    addEdge(g,point,i,j,true);
	    addEdge(g,point,j,i,true);
	  }
	}
	
	cout << ((int)(dijkstra(g,0,1)+0.5)) << endl << (test ? "\n" : "");
	
      }
  

      return 0;
}
