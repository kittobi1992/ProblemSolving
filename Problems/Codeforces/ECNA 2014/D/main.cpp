#include <bits/stdc++.h>

using namespace std;

#define MAXN 52

typedef long long ll;

int N;
vector<int> res[MAXN][MAXN];
vector<ll> vis(10000,0); ll thres = 1;


int romanValue(char c) {
    if(c == 'I') return 1;
    else if(c == 'V') return 5;
    else if(c == 'X') return 10;
    else if(c == 'L') return 50;
    else if(c == 'C') return 100;
    return 0;
}

int value(int a, int b) {
    if(a >= b) return a + b;
    else return b - a;
}

void new_values(int p, int q, vector<int>& a, vector<int>& b) {
    for(int i = 0; i < a.size(); ++i) {
        for(int j = 0; j < b.size(); ++j) {
            int val = value(a[i],b[j]);
            if(vis[val] < thres) {
                res[p][q].push_back(val);
                vis[val] = thres;
            }
        }
    }
}

void initialize() {
    for(int i = 0; i < MAXN; ++i) {
        for(int j = 0; j < MAXN; ++j) {
            res[i][j] = vector<int>();
        }
    }
}

void clear() {
    for(int i = 0; i < MAXN; ++i) {
        for(int j = 0; j < MAXN; ++j) {
            res[i][j].clear();
        }
    }
}

int main() {
  
    initialize();
    int t = 1;
    string s;
    while(cin >> s) {
        if(s == "0") break;
        clear();
        N = s.size();
        
        for(int i = 0; i < N; ++i) res[i][i].push_back(romanValue(s[i]));
        
        for(int l = 1; l < N; ++l) {
            for(int i = 0; i+l < N; ++i) {
                int j = i+l;
                for(int k = i; k < j; ++k) {
                    new_values(i,j,res[i][k],res[k+1][j]);
                }
                thres++;
            }
        }
        
        sort(res[0][N-1].begin(),res[0][N-1].end());
        cout << "Case " << t++ << ": ";
        for(int i = 0; i < res[0][N-1].size(); ++i)
            cout << res[0][N-1][i] << (i == res[0][N-1].size()-1 ? "" : " ");
        cout << endl;
        
    }
    
    return 0;
}
