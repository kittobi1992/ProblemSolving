#include <bits/stdc++.h>

using namespace std;

#define MAXN 105
#define INVALID INT_MAX

using graph = vector<vector<int>>;

int N; 
graph g;
int randNum[MAXN];
int col[MAXN], removed[MAXN];

void printGraph() {
    for(int i = 0; i < N; ++i) {
        cout << "Node " << i << ": ";
        for(int j = 0; j < g[i].size(); ++j) cout << g[i][j] << " ";
        cout << endl;
    }
}

vector<string> split(string& s, string delim) {
    vector<string> result; char *token;
    token = strtok((char*) s.c_str(), (char*)delim.c_str());
    while(token != NULL) {
        result.push_back(string(token));
        token = strtok(NULL,(char*)delim.c_str());
    }
    return result;
}

void resetAll() {
    for(int i = 0; i < N; ++i) {
        col[i] = INVALID;
        removed[i] = 0;
    }
}

void reset() {
    for(int i = 0; i < N; ++i) {
        if(col[i] == INVALID) removed[i] = 0;
    }
}

void remove_neighbors(int u) {
    for(int j = 0; j < g[u].size(); ++j) {
        int v = g[u][j];
        removed[v] = 1;
    }
}

//Find maximum independent set
void lubys_algorithm(int color) {
    bool all_nodes_removed = true;
    for(int i = 0; i < N; ++i) {
        all_nodes_removed = all_nodes_removed && removed[i];
        if(!removed[i]) randNum[i] = rand() % 20;
    }
    if(all_nodes_removed) { reset(); return; }
    
    for(int u = 0; u < N; ++u) {
        if(!removed[u]) {
            bool is_smaller_than_all_neighbors = true;
            for(int j = 0; j < g[u].size(); ++j) {
                int v = g[u][j];
                if(!removed[v]) {
                    if(randNum[u] >= randNum[v]) {
                        is_smaller_than_all_neighbors = false;
                        break;
                    }
                }
            }
            if(is_smaller_than_all_neighbors) {
                col[u] = color;
                removed[u] = 1;
                remove_neighbors(u);
            }
        }
    }
    
    return lubys_algorithm(color);
}

int main() {
  
    cin >> N;
    
    
    string s;
    vector<set<int>> g_tmp(N,set<int>());
    while(cin >> s) {
        vector<string> edge = split(s,"-");
        int u = atoi(edge[0].c_str());
        int v = atoi(edge[1].c_str());
        u--; v--;
        g_tmp[u].insert(v);
        g_tmp[v].insert(u);
    }
    
    g.assign(N,vector<int>());
    for(int i = 0; i < N; ++i) {
        for(int j : g_tmp[i]) {
            g[i].push_back(j);
        }
    }
    
    bool found = false;
    while(!found) {
        resetAll();
        for(int i = 1; i <= 4; ++i) {
            lubys_algorithm(i);
        }
        found = true;
        for(int i = 0; i < N; ++i) {
            if(col[i] == INVALID) found = false;
        }
    }
    
    for(int i = 0; i < N; ++i) {
        cout << (i+1) << " " << col[i] << endl;
    }
    
    
    
	return 0;
}
