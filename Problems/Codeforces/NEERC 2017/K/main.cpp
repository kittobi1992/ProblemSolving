#include <bits/stdc++.h>

using namespace std;

ifstream fin("king.in");
ofstream fout("king.out");

vector<int> days = {31,28,31,30,31,30,31,31,30,31,30,31};

int d,m,y; 

int calcAge(int di, int mi, int yi) {
    int age = 0;
    while(di != d || mi != m) {
        di++; age++;
        if(di > days[mi]) {
            mi++; di = 1;
            if(mi == 12) {
                yi++; mi = 0;
            }
        }
    }
    while(yi != y) { yi++; age += 365; }
    return age;
}

int main() {
        fin >> d >> m >> y; m--;
        int N; fin >> N;
        int idx = -1;
        int min_val = INT_MAX;
        for(int i = 0; i < N; ++i) {
            int di, mi, yi; fin >> di >> mi >> yi;
            mi--;
            int age = calcAge(di,mi,yi);
            if(age/365 >= 18 && age < min_val) {
                min_val = age;
                idx = i+1;
            }
        }
        
        fout << idx << endl;
    
	return 0;
}
