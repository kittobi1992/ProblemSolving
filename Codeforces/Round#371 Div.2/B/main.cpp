#include <bits/stdc++.h>

using namespace std;

int main() {
  
    int n; cin >> n;
    vector<int> a(n);
    std::set<int> dis;
    for(int i = 0; i < n; ++i) { cin >> a[i]; dis.insert(a[i]); };
    
    if(dis.size() <= 2) {
        cout << "YES" << endl;
        return 0; 
    }
    
    sort(a.begin(),a.end());
    
    int x = (a[n-1]-a[0])/2;
    a[0] += x; a[n-1] -= x;
    if(a[0] != a[n-1]) {
        cout << "NO" << endl;
        return 0;
    }
    for(int i = 1; i < n-1; ++i) {
        if(a[i] < a[0]) a[i] += x;
        else if(a[i] > a[0]) a[i] -= x;
        if(a[i] != a[0]) {
            cout << "NO" << endl;
            return 0;
        }
    }
    
    cout << "YES" << endl;
    
	return 0;
}
