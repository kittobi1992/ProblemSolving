#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define INF INT_MAX

int main() {
    
    int N; 
    
    N = (rand()%100000)+1;
   
    
    
    ofstream fout("g.in");
    
    fout << N << endl;
    
    ll p = 0;
    ll m = 0;
    
    while(p+m < 2*N){
        if((rand()%2 == 1 && m < p) || p == N){
            fout << "- " << (p+m)+1 << endl;
            m++;
        } else {
            fout << "+ " << (p+m)+1 << endl;
            p++;
        }
    }

    
    return 0;
}
