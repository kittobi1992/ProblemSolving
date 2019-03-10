#include <bits/stdc++.h>

using namespace std;

int main() {

    int N, M, K;
    cin >> N >> M >> K;
    std::vector<int> p(N);
    std::vector<int> s(N);
    std::vector<int> c(K);

    for ( int i = 0; i < N; ++i )
        cin >> p[i];
    for ( int i = 0; i < N; ++i ) {
        cin >> s[i];
        s[i]--;
    }
    for ( int i = 0; i < K; ++i ) {
        cin >> c[i];
        c[i]--;
    }

    int S = M;
    for ( int i = 0; i < K; ++i )
    {
        int idx = c[i];
        for ( int j = 0; j < N; ++j )
        {
            if ( idx == j )
                continue;
            if ( s[idx] == s[j] && p[idx] < p[j] )
            {
                s[idx] = S++;
                break;
            }
        }
    }    

    std::cout << S - M << std::endl;

    return 0;
}
