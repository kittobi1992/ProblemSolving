#include <bits/stdc++.h>

using namespace std;

int N, M;
vector< string > s;
vector< vector< int > > char_occ;
unordered_map< char, int > char_idx;

struct Move {
    int gain;
    pair< int, int > pos;
    char c;

    void print() {
        cout << gain << " " << pos.first << " " << pos.second << " " << c << endl;
    }
};

bool operator<( const Move& m1, const Move& m2 ) {
    return m1.gain < m2.gain ||
           ( m1.gain == m2.gain && m1.pos.first < m2.pos.first ) ||
           ( m1.gain == m2.gain && m1.pos.first == m2.pos.first && m1.pos.second < m2.pos.second ) ||
           ( m1.gain == m2.gain && m1.pos.first == m2.pos.first && m1.pos.second == m2.pos.second && m1.c < m2.c );
}

bool operator>( const Move& m1, const Move& m2 ) {
    return m1.gain > m2.gain ||
           ( m1.gain == m2.gain && m1.pos.first > m2.pos.first ) ||
           ( m1.gain == m2.gain && m1.pos.first == m2.pos.first && m1.pos.second > m2.pos.second ) ||
           ( m1.gain == m2.gain && m1.pos.first == m2.pos.first && m1.pos.second == m2.pos.second && m1.c > m2.c );
}

using pq = priority_queue< Move, vector< Move >, less< Move > >;

void init_map() {
    char_idx[ 'A' ] = 1;
    char_idx[ 'G' ] = 2;
    char_idx[ 'C' ] = 4;
    char_idx[ 'T' ] = 8;
}

void init_bitset_field( int i, int j ) {
    char_occ[ i ][ j ] = 0;
    char_occ[ i ][ j ] |= char_idx[ s[ i ][ j ] ];
    char_occ[ i ][ j ] |= char_idx[ s[ i + 1 ][ j ] ];
    char_occ[ i ][ j ] |= char_idx[ s[ i ][ j + 1 ] ];
    char_occ[ i ][ j ] |= char_idx[ s[ i + 1 ][ j + 1 ] ];
}

void init_bitset() {
    char_occ.assign( N, vector<int>(M,0) );
    for ( int i = 0; i < N - 1; ++i ) {
        for ( int j = 0; j < M - 1; ++j ) {
            init_bitset_field( i, j );
        }
    }
}

void print_solution() {
    for ( int i = 0; i < N; ++i )
        cout << s[i] << endl;
}

bool contains_char( int i, int j, char c ) {
    return char_occ[ i ][ j ] & char_idx[ c ];
}

set< char > get_missing_chars( int i, int j ) {
    set< char > m;
    if ( !contains_char( i, j, 'A' ) )
        m.insert( 'A' );
    if ( !contains_char( i, j, 'G' ) )
        m.insert( 'G' );
    if ( !contains_char( i, j, 'C' ) )
        m.insert( 'C' );
    if ( !contains_char( i, j, 'T' ) )
        m.insert( 'T' );

    return m;
}

vector< pair< int, int > > get_move_candidates( int i, int j, vector<vector<bool>>& visited ) {
    unordered_map< char, int > cnt;
    for ( int k = i; k < i + 2; ++k )
        for ( int l = j; l < j + 2; ++l )
            cnt[ s[k][l] ]++;

    vector< pair< int, int > > candidates;
    for ( int k = i; k < i + 2; ++k )
        for ( int l = j; l < j + 2; ++l )
            if ( !visited[k][l] && cnt[s[k][l]] > 1 )
                candidates.push_back( make_pair( k, l ) );

    return candidates;
}

Move gain( int i, int j, char c ) {
    Move move;
    move.pos = make_pair( i , j );
    move.c = c;
    move.gain = 0;
    if ( s[ i ][ j ] == c )
        return move;

    if ( i > 0 )
        move.gain += !contains_char( i - 1, j, c );
    if ( j > 0 )
        move.gain += !contains_char( i, j - 1, c );
    if ( i < N - 1 && j < M - 1 )
        move.gain += !contains_char( i, j, c );
    if ( i > 0 && j > 0 )
        move.gain += !contains_char( i - 1, j - 1, c );

    return move;
}

void change_cell( const Move& move ) {
    int i = move.pos.first;
    int j = move.pos.second;
    s[ i ][ j ] = move.c;
    if ( i > 0 && j < M - 1 )
        init_bitset_field( i - 1, j );
    if ( j > 0 && i < N - 1 )
        init_bitset_field( i, j - 1 );
    if ( i < N - 1 && j < M - 1 )
        init_bitset_field( i, j );
    if ( i > 0 && j > 0 )
        init_bitset_field( i - 1, j - 1 );
}


int main() {

    cin >> N >> M;
    s.resize( N );
    for ( size_t i = 0; i < N; ++i )
        cin >> s[i];
    
    init_map();
    init_bitset();

    vector< vector< bool > > visited( N, vector< bool >( M, false ) );
    for ( int i = 0; i < N - 1; ++i ) {
        for ( int j = 0;  j < M - 1; ++j ) {
            pq p;
            set< char > m = get_missing_chars( i, j );
            if ( m.size() > 0 ) {

                vector< pair< int, int > > c = get_move_candidates( i, j, visited );
                for ( pair< int, int > pos : c ) {
                    for ( char c : m )
                        p.push( gain( pos.first, pos.second, c ) );
                }

                while ( !p.empty() ) {
                    Move move = p.top();
                    p.pop();

                    if (  !visited[ move.pos.first ][ move.pos.second ] &&
                          m.find( move.c ) != m.end() ) {
                        change_cell( move );
                        visited[ move.pos.first ][ move.pos.second ] = true;
                        m.erase( move.c );
                    }

                    if( m.size() == 0 )
                        break;
                }
            }
        }
    }

    print_solution();

	return 0;
}
