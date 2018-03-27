#include <bits/stdc++.h>

using namespace std;

#define MAXN 100005

int N, M; 
int d[MAXN], a[MAXN];
int vis[MAXN];
int thres = 0;
int sum_prep = 0;

bool check(int x) {
    thres++;
    int tmp_sum = sum_prep;
    int pass_exams = 0;
    for(int i = x-1; i >= 0; i--) {
        if(d[i] > 0 && !(vis[d[i]-1] == thres)) {
            if(tmp_sum <= (i+1-(M-pass_exams))) {
                vis[d[i]-1] = thres;
                tmp_sum -= a[d[i]-1];
                pass_exams++;
            }
            else return false;
        }
        if(tmp_sum == 0) return true;
    }
    return false;
}

int main() {
  
    cin >> N >> M;
    for(int i = 0; i < N; ++i) cin >> d[i];
    for(int i = 0; i < M; ++i) { cin >> a[i]; sum_prep += a[i]; }
    
    int l = 1, r = N+1;
    while(l < r) {
        int m = (l+r)/2;
        if(check(m)) r = m;
        else l = m + 1;
    }
    
    if(l > N) l = -1;
    cout << l << endl;
    
	return 0;
}
