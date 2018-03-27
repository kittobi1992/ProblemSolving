#include <bits/stdc++.h>

using namespace std;

string generateHallway(int n) {
    int len = pow(2,n)-1;
    string s(len,'L');
    
    for(int i = 1; i < len; ++i) {
        int k = log2(i+1);
        if(pow(2,k) != i+1) {
            int j = 2*pow(2,k) - i - 2;
            s[i] = (s[j] == 'L' ? 'R' : 'L');
        }
    }
    
    return s;
}

vector<string> pre_calc;

bool find(string& S, string& P) {
    int j = 0;
    for(int i = 0; i < S.size(); ++i) {
        while(j < P.size() && i+j < S.size() && S[i+j] == P[j]) j++;
        if(j == P.size()) return true;
        else j = 0;
    }
    return false;
}

int main() {

    int idx = 1, cnt = -1;
    while(cnt != 3) {
        string h = generateHallway(idx++);
        pre_calc.push_back(h);
        if(h.size() >= 100) cnt++;
    }
    
    int N = pre_calc.size();
    int test, t = 1; cin >> test;
    while(test--) {
        int n; cin >> n; string s; cin >> s;
        n = min(N,n);
        bool match = false;
        for(int i = 0; i < n; ++i) {
            match = find(pre_calc[i],s);
            if(match) break;
        }
        
        cout << "Case " << t++ << ": ";
        if(match)  cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    
	return 0;
}
