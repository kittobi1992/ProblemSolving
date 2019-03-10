#include <bits/stdc++.h>

using namespace std;

typedef long long ll; 

using tree_t = vector<vector<int>>;
using node_sum_pair_t = pair<int,ll>;

int main() {

    int N;
    cin >> N;

    tree_t t( N, vector<int>() );
    vector<ll> a(N,-1);
    vector<ll> s(N,-1);

    for ( int i = 1; i < N; ++i ) {
        int p; cin >> p;
        t[p-1].push_back(i);
    }

    for ( int i = 0; i < N; ++i )
        cin >> s[i];
    a[0] = s[0];

    queue<node_sum_pair_t> q;
    for ( int v : t[0] )
        q.push( make_pair( v, s[0] ) );
    ll sum = a[0];
    while(!q.empty()) {
        int u = q.front().first;
        ll p_sum = q.front().second;
        q.pop();

        if ( s[u] == -1 ) {
            ll min_a = t[u].size() > 0 ? numeric_limits<ll>::max() : 0;

            for ( int v : t[u] )
                min_a = min( min_a, s[v] - p_sum );

            a[u] = min_a;
            s[u] = p_sum + a[u];
        } else {
            a[u] = s[u] - p_sum;
        }

        if ( a[u] < 0 ) {
            cout << "-1" << endl;
            return 0;
        }

        for ( int v : t[u] )
            q.push( make_pair( v, s[u] ) );
        sum += a[u];
    }

    cout << sum << endl;
    
	return 0;
}
