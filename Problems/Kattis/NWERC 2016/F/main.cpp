#include <bits/stdc++.h>

using namespace std;

#define SIZE 2000005
#define LOG_SIZE 22

int n; 
int data[SIZE];
int pre[SIZE];
int rmq[SIZE][LOG_SIZE];

map<int,int> occ;

//Preprocessing RMQ-Datastructure in O(n*log(n))
void buildRMQ() {
    for(int i = 0; i < n; ++i)
        rmq[i][0] = i;
    
    int l = log2(n) + 1;
    for(int i = 1; i < l; ++i) {
        int p = 1 << i;
        for(int j = 0; j+p < n; ++j) {
            rmq[j][i] = (data[rmq[j][i-1]] <= data[rmq[j+p/2][i-1]]) ? rmq[j][i-1] : rmq[j+p/2][i-1];
        }
    }
}

//RMQ-Query in O(1)
int query(int l, int r) {
    int k = log2(r-l+1), p = 1 << k;
    return (data[rmq[l][k]] <= data[rmq[r-p+1][k]]) ? rmq[l][k] : rmq[r-p+1][k];
}

int main() {
    
    cin >> n; n *= 2;
    for(int i = 0; i < n; ++i) { cin >> data[i]; data[i] = -data[i]; }
    buildRMQ();
    
    for(int i = 0; i < n; ++i) {
        auto it = occ.find(data[i]);
        if(it == occ.end()) {
            pre[i] = -1;
            occ.insert(make_pair(data[i],i));
        }
        else {
            pre[i] = it->second;
        }
    }
    
    int max_weight = 0;
    int N = n/2;
    for(int i = 0; i < n; ++i) {
        int p = pre[i];
        if(p == -1) continue;
        if(p < N && i >= N) { max_weight = max(max_weight,-data[i]); continue; }
        if(i-p == 1) continue;
        int j = query(p+1,i-1);
//      cout << -data[i] << " " << -data[j] << " " << p << " " << i << endl;
        if(-data[j] > -data[i]) max_weight = max(max_weight,-data[i]);
        else max_weight = max(max_weight,-data[j]);
    }
    
    cout << max_weight << endl;
    
	return 0;
}
