#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M; 
vector<vector<int>> cnt;



pair<int,int> findMinMax() {
    int min_i = 1; ll min_value = cnt[1].size();
    int max_i = 1; ll max_value = cnt[1].size();
    for(int i = 2; i <= M; ++i) {
        if(min_value > cnt[i].size()) {
            min_i = i;
            min_value = cnt[i].size();
        }
        if(max_value < cnt[i].size()) {
            max_i = i;
            max_value = cnt[i].size();
        }
    }
    return make_pair(min_i,max_i);
}

struct history {
    int min_val;
    int idx;
    ll val;
};


int main() {
    cin >> N >> M;
    vector<ll> a(N);
    cnt.assign(M+1,vector<int>());
    vector<int> idx;
    for(int i = 0; i < N; ++i) {
        cin >> a[i];
        if(a[i] <= M) cnt[a[i]].push_back(i);
        else idx.push_back(i);
    }
    
    stack<history> his;
    
    int changes = 0;
    
    for(int i = 0; i < idx.size(); ++i) {
        int j = idx[i];
        int min_i = findMinMax().first;
        history h; h.min_val = cnt[min_i].size(); h.idx = j; h.val = a[j];
        his.push(h);
        a[j] = min_i;
        cnt[a[j]].push_back(j);
        changes++;
    }
    
    while(true) {
        auto minmax = findMinMax();
        int min_i = minmax.first;
        int max_i = minmax.second;
        if(cnt[min_i].size() + 1 >= cnt[max_i].size()) break;
        int i = cnt[max_i][cnt[max_i].size()-1];
        history h; h.min_val = cnt[min_i].size(); h.idx = i; h.val = a[i];
        his.push(h);
        a[i] = min_i;
        changes++;
        cnt[max_i].pop_back(); cnt[min_i].push_back(i);
    }
    
    ll min_value = LLONG_MAX;
    for(int i = 1; i <= M; ++i) {
        if(cnt[i].size() < min_value) min_value = cnt[i].size();
    }
    
    while(!his.empty() && his.top().min_val == min_value) {
        a[his.top().idx] = his.top().val;
        his.pop();
        changes--;
    }
    
    cout << min_value << " " << changes << endl;
    for(int i = 0; i < N; ++i) {
        cout << a[i] << (i == N-1 ? "\n" : " ");
    }
    
    
	return 0;
}
