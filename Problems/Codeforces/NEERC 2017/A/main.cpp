#include <bits/stdc++.h>

using namespace std;

ifstream fin("anniversary.in");
ofstream fout("anniversary.out");

int main() {
    int w,h,ax,ay,bx,by;
    fin >> w >> h >> ax >> ay >> bx >> by;
    
    if(ax == bx) {
        fout << "0 " << ay << " " << w  << " " << by << endl;
    } else {
        fout << ax << " 0 " << bx << " " << h << endl;
    }
    
    return 0;
}
