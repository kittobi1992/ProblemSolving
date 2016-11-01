#include <bits/stdc++.h>

using namespace std;

vector<char> vowel = {'A','E','I','O','U','Y'};

bool isVowel(char c) {
    for(int i = 0; i < vowel.size(); ++i) {
        if(c == vowel[i]) return true;
    }
    return false;
}

int main() {
    string s; cin >> s;
    int N = s.size();
    int lastVowel = 0;
    int a = 1;
    for(int i = 0; i < s.size(); ++i) {
        if(isVowel(s[i])) {
            a = max(a,i+1-lastVowel);
            lastVowel = i+1;
        }
    }
    a = max(a,N+1-lastVowel);
    cout << a << endl;
    
	return 0;
}
