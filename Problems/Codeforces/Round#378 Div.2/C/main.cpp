#include <bits/stdc++.h>

using namespace std;

typedef pair<char,int> ci;

int N, K;
vector<int> a;
vector<int> b;
vector<ci> t;


int biggestMonster(int s, int e) {
    int idx = s;
    int val = a[s];
    for(int i = s+1; i <= e; ++i) {
        if(a[i] >= val && ((i > s && a[i-1] < a[i]) || (i < e && a[i] > a[i+1]))) {
            idx = i;
            val = a[i];
        }
    }
    return idx;
}

void eat(int i1, int i2) {
    vector<int> tmp_a;
    for(int i = 0; i < a.size(); i++) {
        if(i != i1 && i != i2) tmp_a.push_back(a[i]);
        else if(i == i2) tmp_a.push_back(a[i1]+a[i2]);
    }
    swap(a,tmp_a);
}

bool eat(int s, int e, int b) {
    int b_idx = biggestMonster(s,e);
    int b_w = a[b_idx];
    bool found = false;
    while(e-s > 0) {
        if(b_idx + 1 <= e && a[b_idx+1] < a[b_idx]) {
            t.push_back(make_pair('R',b_idx+1));
            eat(b_idx,b_idx+1); e--;
            found = false;
        } else if(b_idx - 1 >= s && a[b_idx-1] < a[b_idx]) {
            t.push_back(make_pair('L',b_idx+1));
            eat(b_idx,b_idx-1); e--; b_idx--;
            found = false;
        } else {
            if(found) return false;
            b_idx = biggestMonster(s,e);
            found = true;
        }
    }
    return a[b_idx] == b;
}

int main() {
    
    cin >> N;
    a.resize(N);
    for(int i = 0; i < N; ++i) cin >> a[i];
    
    
    cin >> K;
    b.resize(K);
    for(int i = 0; i < K; ++i) cin >> b[i];
    
    int b_idx = 0;
    int startIdx = 0;
    int sum = a[0];
    for(int i = 1; i < N+1; ++i) {

//         cout << startIdx << " " << i << " " << sum << " " << N << endl;
        
        if(i == N && sum != b[b_idx]) {
            cout << "NO" << endl;
            return 0;
        }
        if(sum == b[b_idx]) {
            if(!eat(startIdx,i-1,sum)) {
                cout << "NO" << endl;
                return 0;
            }
            N = a.size();
            b_idx++;
            startIdx = b_idx;
            i = b_idx;
            sum = a[i];
        } else if(sum > b[b_idx]) {
            cout << "NO" << endl;
            return 0;
        } else {
            sum += a[i];
        }
    }
    
    if(b_idx != K) {
        cout << "NO" << endl;
        return 0;
    }
    
    cout << "YES" << endl;
    for(int i = 0; i < t.size(); ++i) {
        cout << t[i].second << " " << t[i].first << endl;
    }
    
	return 0;
}
