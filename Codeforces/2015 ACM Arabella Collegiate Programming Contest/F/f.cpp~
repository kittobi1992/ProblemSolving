#include <iostream>
#include <string>
#include <vector>

#define MOD     1000000007

typedef long long ll;

using namespace std;

    int n,m;
    string s;

vector <int> parent , rank2; // manche Compiler verbieten Variable mit Namen rank

int findSet(int n) { // Pfadkompression
    if (parent[n] != n) parent[n] = findSet(parent[n]);
    
    return parent[n];
}

void linkSets(int a, int b) { // union by rank
if (rank2[a] < rank2[b]) parent[a] = b;
    else if (rank2[b] < rank2[a]) parent[b] = a;
    else {
        parent[a] = b;
        rank2[b]++;
    }
}

void unionSets (int a, int b) {
    if (findSet(a) != findSet(b)) linkSets(findSet(a), findSet(b));
}


bool addConstraint(int a, int b) {
        char ca, cb;
        ca = s[findSet(a)], cb = s[findSet(b)];
        if(ca != '?' && cb != '?' && ca != cb) {
                cout << "0\n";
                return false;
        } else {
                char tmp = (ca == '?' ? cb : ca);
                unionSets(a,b);
                s[findSet(a)] = tmp;
        }   
        
        return true;
}


void solve() {
    cin >> n >> m;
    cin >> s;
    
    parent = vector<int>(n, 0);
    for(int i = 0; i < n; i++) parent[i] = i;
    rank2 = vector<int>(n, 0);
    

    
    int a,b;
    bool cont = true;
    //given constraints
    for(int i = 0; i < m;i++) {
        cin >> a >> b;
        if(cont) {
            cont = addConstraint(a-1,b-1);
        }
    }
    
    if(!cont) return;
    
    //constraints by the props of a palyn.
    for(int i = 0; i < n / 2; i++) {
        a = i, b = (n - 1) - i;
        if(!addConstraint(a,b)) return;
    }
    
    ll c = 1;
    for(int i = 0; i < n; i++) {
        int idx = findSet(i);
        if(s[idx] == '?') {
                c = (c * 26) % MOD;
                s[idx] = '#';
        }
    }
    
    cout << c << "\n";
}


int main() {
    
    int T; cin >> T;
    
    while(T--) {
            solve();
    }
    
    return 0;
}
