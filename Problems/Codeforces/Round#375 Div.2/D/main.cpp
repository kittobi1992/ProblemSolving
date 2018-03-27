#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> point;

int N, M, K;
vector<string> m;
vector<vector<point>> lakes;
vector<vector<bool>> vis;
int cur = 0;

bool findLake(int i, int j) {
    bool isLake = true;
    vis[i][j] = true;
    lakes[cur].push_back(make_pair(i,j));
    if(i == 0 || i == N-1 || j == 0 || j == M-1) isLake = false;
    
    if(i > 0 && !vis[i-1][j] && m[i-1][j] == '.') isLake = findLake(i-1,j) && isLake;
    if(i < N-1 && !vis[i+1][j] && m[i+1][j] == '.') isLake = findLake(i+1,j) && isLake;
    if(j > 0 && !vis[i][j-1] && m[i][j-1] == '.') isLake = findLake(i,j-1) && isLake;
    if(j < M-1 && !vis[i][j+1] && m[i][j+1] == '.') isLake = findLake(i,j+1) && isLake;
    
    return isLake;
}


int main() {
    
    cin >> N >> M >> K;
    m.resize(N); vis.assign(N,vector<bool>(M,false));
    for(int i = 0; i < N; ++i) cin >> m[i];
    
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            if(m[i][j] == '.' && !vis[i][j]) {
                lakes.push_back(vector<point>());
                if(!findLake(i,j)) lakes.pop_back();
                else cur++;
            }
        }
    }
    sort(lakes.begin(),lakes.end(),[&](const vector<point>& l1, const vector<point>& l2) {
        return l1.size() < l2.size();
    });
    int cur_k = lakes.size();
    int earth = 0;
    int idx = 0;
    while(cur_k != K) {
        for(int i = 0; i < lakes[idx].size(); ++i) {
            int x = lakes[idx][i].first, y = lakes[idx][i].second;
            m[x][y] = '*';
            earth++;
        }
        idx++;
        cur_k--;
    }
    
    cout << earth << endl;
    for(int i = 0; i < m.size(); ++i) cout << m[i] << endl;
    
	return 0;
}
