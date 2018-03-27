#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second

typedef long double ld;
typedef pair<ld,ld> point;
typedef pair<ld,pair<int,point>> label;

using PQ = priority_queue<label,vector<label>,greater<label>>;

ld W;
int N;
vector<point> p;

ld dist[2][1005];
PQ pq;


ld distance(int u, int v, bool stone = false) {
    ld dist = 0.0;
    if(v == 0 || u == N+1) dist = numeric_limits<ld>::max();
    if(u == 0 && v == N+1) dist = sqrt(W*W);
    else if(u == 0) dist = sqrt(p[v-1].f*p[v-1].f);
    else if(v == N+1) dist = sqrt((W-p[u-1].f)*(W-p[u-1].f));
    else dist = sqrt((p[v-1].f-p[u-1].f)*(p[v-1].f-p[u-1].f) + (p[v-1].s-p[u-1].s)*(p[v-1].s-p[u-1].s));
    if(stone) dist /= 2.0;
    return dist;
}

point addStone(int u, int v) {
    point p1, p2;
    if(u == 0 && v == N+1) {
        p1 = make_pair(0.0,0.0); p2 = make_pair(W,0.0);
    } else if(u == 0) {
        p2 = p[v-1]; p1 = make_pair(0.0,p2.s);
    } else if(v == N+1) {
        p1 = p[u-1]; p2 = make_pair(W,p1.s);
    } else {
        p1 = p[u-1]; p2 = p[v-1];
    }
    return make_pair((p1.f+p2.f)/2.0,(p1.s+p2.s)/2.0);
}


void initialize() {
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 1005; ++j) dist[i][j] = numeric_limits<ld>::max();
    }
    PQ empty_pq; swap(pq,empty_pq);
}

point dijkstra(int s, int t) {
    initialize();
    dist[0][s] = static_cast<ld>(0); pq.push(make_pair(static_cast<ld>(0),make_pair(s,make_pair(-1.0,-1.0))));
    while(!pq.empty()) {
        int u = pq.top().s.f; ld cur_dist = pq.top().f; point stone = pq.top().s.s; pq.pop();
        
        if(stone.f == -1.0 && cur_dist > dist[0][u]) continue;
        else if(stone.f != -1.0 && cur_dist > dist[1][u]) continue;
        if(u == t) {
            if(stone.f == -1) {
                stone.f = 1.0; stone.s = 0.0;
            }
            return stone;
        }
        
        bool isStoneSet = (stone.f != -1);
        for(int v = 1; v < N+2; ++v) {
            if(isStoneSet) {
                ld dist1 = distance(u,v);
                if(max(dist1,dist[1][u]) < dist[1][v]) {
                    dist[1][v] = max(dist1,dist[1][u]); pq.push(make_pair(dist[1][v],make_pair(v,stone)));
                } 
            } else {
                ld dist1 = distance(u,v);
                ld dist2 = distance(u,v,true);
                if(max(dist1,dist[0][u]) < dist[0][v]) {
                    dist[0][v] = max(dist1,dist[0][u]); pq.push(make_pair(dist[0][v],make_pair(v,stone)));
                }
                if(max(dist2,dist[0][u]) < dist[1][v]) {
                    dist[1][v] = max(dist2,dist[0][u]); pq.push(make_pair(dist[1][v],make_pair(v,addStone(u,v))));
                }
            }
        }
    }
    return make_pair(0.0,0.0);
}	

int main() {
//     freopen("froggy.in", "r",stdin);
//     freopen("froggy.out", "w",stdout);
    
    cin >> W >> N;
    p.assign(N,make_pair(0.0,0.0));
    for(int i = 0; i < N; ++i) cin >> p[i].f >> p[i].s;
    
    point stone = dijkstra(0,N+1);
    
    cout << fixed << setprecision(4) << stone.f << " " << stone.s << endl;
    
	return 0;
}
