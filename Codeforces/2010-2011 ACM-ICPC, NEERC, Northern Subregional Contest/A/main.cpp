#include <bits/stdc++.h>

using namespace std;

vector<int> a,b;
ifstream fin("acm.in");
ofstream fout("acm.out");

int main() {
    int n,m; fin >> n >> m;
    a.resize(n); b.resize(m);
    for(int i = 0; i < n; ++i) fin >> a[i];
    for(int i = 0; i < m; ++i) fin >> b[i];
    sort(a.begin(),a.end());
    
    int smallest = a[0] - 1;
    for (int i = 0; i < n; i++) {
        if (i > 0) fout << "*";
        fout << "(";
        fout << smallest;
        for (int k = 0; k < a[i] - smallest; k++) {
            fout << "+1";
        }
        fout << "-10";
        fout << ")";
    }
    fout << "=0" << endl;
    
    return 0;
}
