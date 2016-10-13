#include <bits/stdc++.h>

using namespace std;

char off = 'A';
vector<int> cnt(27,0);
string s; 
int N;
int l = 0, r = 0;

void move() {
    if(s[l] == '?') cnt[26]--;
    else cnt[s[l]-off]--;
    l++;
    r++;
    if(s[r] == '?') cnt[26]++;
    else cnt[s[r]-off]++;
}

bool process() {
    vector<char> missing_char;
    for(int i = 0; i < 26; ++i) {
        if(cnt[i] == 0) missing_char.push_back(((char) (i+off)));
    }
    int idx = 0;
    if(missing_char.size() == cnt[26]) {
        for(int i = l; i <= r; ++i) {
            if(s[i] == '?') s[i] = missing_char[idx++];
        }
        move();
        return true;
    }
    move();
    return false;
}

int main() {
    cin >> s;
    N = s.size();
    
    if(N < 26) {
        cout << "-1" << endl;
        return 0;
    }
    
    for(int i = 0; i < 26; ++i) {
        if(s[i] == '?') cnt[26]++;
        else cnt[s[i]-off]++;
    }
    
    l = 0; r = 25;
    bool possible = false;
    while(r < N) {
        possible = possible || process();
        if(possible) break;
    }
    
    for(int i = 0; i < N; ++i) {
        if(s[i] == '?') s[i] = (char)((rand()%26)+off);
    }
    
    if(possible) cout << s << endl;
    else cout << "-1" << endl;
    
    
	return 0;
}
