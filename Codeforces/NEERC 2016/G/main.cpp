#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

bool check_intersect(pll ival1, pll ival2) {
    return !((ival1.second < ival2.first) || (ival2.second < ival1.first));
}

int main() {
  
    int N; cin >> N;
    vector<pll> a;
    a.push_back(make_pair(0,0));
    a.push_back(make_pair(1e10,1e10+1));
    for(int i = 0; i < N; ++i) {
        ll s, d; cin >> s >> d;
        pll schedule = make_pair(s,s+d-1);
        bool find = true;
        for(int j = 0; j < a.size(); ++j) {
            if(check_intersect(schedule,a[j])) {
                find = false; break;
            }
        }
        if(find) {
            a.push_back(schedule);
            cout << schedule.first << " " << schedule.second << endl; 
        }
        else {
            for(int j = 1; j < a.size(); ++j) {
                pll ival = make_pair(a[j-1].second+1,a[j].first-1);
                if(ival.second-ival.first+1 > d) {
                    schedule = make_pair(ival.first,ival.first+d-1);
                    a.push_back(schedule);
                    cout << schedule.first << " " << schedule.second << endl; 
                    break;
                }
            } 
        }
        sort(a.begin(),a.end());
    }
    
	return 0;
}
