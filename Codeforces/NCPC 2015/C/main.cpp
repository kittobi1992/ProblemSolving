#include <bits/stdc++.h>

using namespace std;


int main() {
    
    string s; cin >> s;
    int num = 0;
    for(int i = 0; i < s.size(); i += 3) {
        if(s[i] != 'P') num++;
        if(s[i+1] != 'E') num++;
        if(s[i+2] != 'R') num++;
    }
    
    cout << num << endl;
    
    return 0;
}
