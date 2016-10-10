#include <bits/stdc++.h>

using namespace std;

#define MAXN 102

int pword[MAXN];

void initialize() {
    for(int i = 0; i < MAXN; ++i) 
        pword[i] = 0;
}

int main() {
  
    initialize();
    int N, K; cin >> N >> K;
    for(int i = 0; i < N; ++i) {
        string s; cin >> s;
        pword[s.size()]++;
    }
    
    string pw; cin >> pw;
    int pw_len = pw.size();
    int sec = 0, pw_tried = 0;
    for(int i = 0; i < pw_len; ++i) {
        for(int j = 0; j < pword[i]; ++j) {
            pw_tried++; sec++;
            if(pw_tried % K == 0) sec += 5;
        }
    }
    
    int min = sec+1, max = sec;
    for(int i = 0; i < pword[pw_len]-1; ++i) {
        pw_tried++; max++;
        if(pw_tried % K == 0) max += 5;
    }
    max++;
    
    cout << min << " " << max << endl;
    
    
	return 0;
}
