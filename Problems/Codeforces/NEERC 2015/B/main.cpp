#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("black.in", "r",stdin);
    freopen("black.out", "w",stdout);
    
    int b,w; cin >> b >> w;
    
    int m = max(b,w);
    int N = 2*m;
    char rect[2][N];
    int cur = 0;
    for(int i = 0; i < N; ++i) {
        rect[0][i] = (cur == 0 ? '@' : '.');
        rect[1][i] = (cur == 0 ? '@' : '.');
        cur = (cur + 1) % 2;
    }
    
    if(b < w) {
        for(int i = 1; i < 1 + 2*(w-b); i += 2) {
            rect[0][i] = '@';
        }
    } else if(b > w) {
        for(int i = 2; i < 2+2*(b-w); i += 2) {
            rect[0][i] = '.';
        }
    }
    
    cout << 2 << " " << N << endl;
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < N; ++j) {
            cout << rect[i][j];
        }
        cout << endl;
    }
    
    
    return 0;
}
