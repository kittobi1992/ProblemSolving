#include <bits/stdc++.h>

using namespace std;

int main() {
        
        int N;
        cin >> N;
        vector<vector<bool>> a(N,vector<bool>(N,false));
        for(int i = 0; i < N; ++i) a[i][i] = true;
        a[N-1][0] = true;
        vector<bool> complete(N,false);
        cout << "1 1 0" << endl;
        int free = 0;
        while(true) {
            int next = 0;
            for(int i = 0; i < a[free].size(); ++i) {
                if(!a[free][i]) { next = i; break; }
            }
            if(a[free][next] == true) break;
            a[free][next] = true;
            cout << (next+1) << " " << (next+1) << " " << (free+1) << endl;
            free = next;
            bool isComplete = true;
            for(int i = 0; i < a[free].size(); ++i) {
                if(!a[free][i]) { isComplete = false; break; }
            }
            complete[free] = isComplete;
            int num_complete = 0;
            for(int i = 0; i < N; ++i) {
                num_complete += complete[i];
            }
            if(num_complete == N-2) break;
        }
        cout << "0 1 " << N << endl;
    
	return 0;
}
