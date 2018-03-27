#include <bits/stdc++.h>

using namespace std;


int main() {
    int N; cin >> N;
    string t; cin >> t;
    t.push_back('_');
    string s = "_" + t; N+=2;
    bool insideBP = false;
    int lastWordBegin = -1;
    
    int max_word_length = 0;
    int words_inside_bp = 0;
    
    for(int i = 0; i < N; ++i) {
        if(s[i] == '_' || s[i] == '(' || s[i] == ')') {
            if(lastWordBegin != -1 && !insideBP) {
                max_word_length = max(max_word_length,i-(lastWordBegin+1));
            } else if(lastWordBegin != -1 && insideBP && (i-(lastWordBegin+1)) > 0) {
                words_inside_bp++;
            }
            lastWordBegin = i;
            if(s[i] == '(') insideBP = true;
            else if(s[i] == ')') insideBP = false;
        }
    }
    
    cout << max_word_length << " " << words_inside_bp << endl;
    
	return 0;
}
