#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int N; 

ll minimumFlick(vector<int> b1, vector<int> b2) {
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j <= i; ++j) {
//             cout << j << " " << i << " " << b1[j] << " " << b2[i] << endl;
            int min_b = min(b1[j],b2[i]);
            b1[j] -= min_b; b2[i] -= min_b;
        }
    }
    int flick = 0;
    for(int i = 0; i < 10; ++i) flick += b1[i];
    return flick;
}

ll maximumFlick(vector<int> b1, vector<int> b2) {
    int flick = 0;
    for(int i = 0; i < 10; ++i) {
        for(int j = i-1; j >= 0; --j) {
            int min_b = min(b1[j],b2[i]);
            b1[j] -= min_b; b2[i] -= min_b;
            if(i > j) flick += min_b;
        }
    }
    return flick;
}

int main() {
    cin >> N;
    string n1, n2; cin >> n1 >> n2;
    
    vector<int> b1(10,0), b2(10,0);
    for(int i = 0; i < N; ++i) {
        b1[n1[i]-'0']++; b2[n2[i]-'0']++;
    }
    
    cout << minimumFlick(b1,b2) << endl;
    cout << maximumFlick(b1,b2) << endl;
    
	return 0;
}
