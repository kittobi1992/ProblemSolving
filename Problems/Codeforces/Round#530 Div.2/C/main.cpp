#include <bits/stdc++.h>

using namespace std;

bool is_regex_symbol( const string& s, int i ) {
    return s[i] == '?' || s[i] == '*';
}

int main() {

    string s;
    int k;
    cin >> s >> k;

    int N = s.size();
    int cur_k = 0;
    for ( int i = 0; i < N; ++i ) {
        if ( s[i] == '?' || s[i] == '*' ) 
            continue;
        cur_k += ( i < N - 1 ? !is_regex_symbol( s, i + 1 ) : 1 );
    }

    if ( cur_k > k ) {
        cout << "Impossible" << endl;
        return 0;
    }

    string t = "";
    for ( int i = 0; i < N; ++i ) {
        if ( is_regex_symbol( s, i ) )
            continue;
        if ( i < N - 1 && is_regex_symbol( s, i + 1 ) ) {
            if ( s[ i + 1 ] == '?' ) {
                if ( cur_k < k ) {
                    t.push_back(s[i]);
                    cur_k++;
                }
            } else if ( s[ i + 1 ] == '*' ) {
                while( cur_k < k ) {
                    t.push_back(s[i]);
                    cur_k++;
                }
            }
        } else {
            t.push_back( s[i] );
        }
    }

    if ( t.size() == k )
        cout << t << endl;
    else
        cout << "Impossible" << endl;

	return 0;
}
