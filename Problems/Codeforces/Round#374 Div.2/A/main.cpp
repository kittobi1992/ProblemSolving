#include <bits/stdc++.h>

using namespace std;

int main() {
  
    int N; string s;
    vector<int> enc;
    cin >> N >> s;
    int startIdx = -1;
    bool isGroup = false;
    s.push_back('W');
    for(int i = 0; i <= N; ++i) {
        if(s[i] == 'W' && isGroup) {
            enc.push_back(i-startIdx);
            isGroup = false;
        }
        else if(s[i] == 'B' && !isGroup) {
            startIdx = i;
            isGroup = true;
        }
    }
    
    cout << enc.size() << endl;
    for(int i = 0; i < enc.size(); ++i) {
        cout << enc[i] << (i == enc.size()-1 ? "\n" : " ");
    }
    
	return 0;
}
