#include <bits/stdc++.h>

using namespace std;

int main() {

    int m, k, n, s;
    cin >> m >> k >> n >> s;

    std::vector<int> a(m);
    for ( int i = 0; i < m; ++i )
        cin >> a[i];
    
    std::unordered_map<int, int> b;
    for ( int i = 0; i < s; ++i ) {
        int b_i; cin >> b_i;
        b[ b_i ]++;
    }

    int max_rm = m - k * n;
    int num_types = b.size();
    bool found_solution = false;
    vector<int> res;

    for ( int i = 0; i + k <= m; i += k  )
    {
        unordered_map<int,int> tmp_b;
        vector<int> tmp_res;
        int tmp_num_types = 0;
        int j = i;
        while( j < m && j - i - tmp_res.size() < k  )
        {
            int type = a[ j ];
            int b_before = tmp_b[ type ];

            if ( b_before < b[ type ] ) {
                if( ++tmp_b[ type ] == b[ type ] )
                    tmp_num_types++;
                if ( tmp_num_types == num_types ) {
                    found_solution = true;
                    break;
                } 
            } 
            else
            {
                if ( tmp_res.size() < max_rm )
                    tmp_res.push_back( j );
            }
            ++j;
        }

        if ( found_solution ) {
            res = tmp_res;
            break;
        }
    }

    if ( found_solution )
    {
        cout << res.size() << endl;
        if ( res.size() > 0 ) {
            for ( int i = 0; i < res.size(); ++i )
                cout << ( res[ i ] + 1 ) << " ";
            cout << endl;
        }
    } else 
    {
        cout << "-1" << endl;
    }

    return 0;
}
