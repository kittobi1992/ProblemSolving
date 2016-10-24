#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;

int main() {
    int n, p, s;
    cin >> n >> p >> s;
    vector<int> a(n), ai(n);
    vector<int> b(n), bi(n);
    iota(ai.begin(),ai.end(),0);
    iota(bi.begin(),bi.end(),0);
    for(int i = 0; i < n; ++i) cin >> a[i];
    for(int i = 0; i < n; ++i) cin >> b[i];
    
    sort(ai.begin(),ai.end(),[&](const int i1, const int i2) {
       return a[i1] > a[i2] || (a[i1] == a[i2] && i1 < i2); 
    });
    sort(bi.begin(),bi.end(),[&](const int i1, const int i2) {
       return b[i1] > b[i2] || (b[i1] == b[i2] && i1 < i2); 
    });
    
    vector<bool> p_team(n,false), s_team(n,false);
    int sum = 0;
    for(int i = 0; i < p; ++i) { p_team[ai[i]] = true; sum += a[ai[i]]; }
    for(int i = 0; i < s; ++i) { s_team[bi[i]] = true; sum += b[bi[i]]; }
    
    vector<int> isect;
    for(int i = 0; i < n; ++i) if(p_team[i] && s_team[i]) isect.push_back(i);
    sort(isect.begin(),isect.end(),[&](const int i1, const int i2) {
       return a[i1]+b[i1] > a[i2]+b[i2] || (a[i1]+b[i1] == a[i2]+b[i2] && i1 < i2); 
    });
    int pi = p, si = s;
    while(isect.size() > 0) {
        int cur_stud = isect[isect.size()-1];
        cout << cur_stud << endl;
        int p_stud = ai[pi];
        int s_stud = bi[si];
        
        int p_sum = sum + a[p_stud] - a[cur_stud];
        int s_sum = sum + b[s_stud] - b[cur_stud];
        //cout << p_stud << " " << s_stud << endl;
        if(p_sum > s_sum) {
            bool intersect = false;
            p_team[p_stud] = true; p_team[cur_stud] = false;
            if(s_team[p_stud]) intersect = true;
            sum = p_sum;
            pi++;
            isect.pop_back();
            if(intersect) isect.push_back(p_stud);
        }
        else {
            bool intersect = false;
            s_team[s_stud] = true; s_team[cur_stud] = false;
            if(p_team[s_stud]) intersect = true;
            sum = s_sum;
            si++;
            isect.pop_back();
            if(intersect) isect.push_back(s_stud);
        }
        
            sort(isect.begin(),isect.end(),[&](const int i1, const int i2) {
       return a[i1]+b[i1] > a[i2]+b[i2] || (a[i1]+b[i1] == a[i2]+b[i2] && i1 < i2); 
    });
        
    }
    
    
    
    //#################################################
    cout << sum << endl;
    string p_str = "";
    for(int i = 0; i < n; ++i) if(p_team[i]) p_str = p_str + "" + to_string(i+1) + " ";
    p_str.pop_back();
    cout << p_str << endl;
    
    string s_str = "";
    for(int i = 0; i < n; ++i) if(s_team[i]) s_str = s_str + "" + to_string(i+1) + " ";
    s_str.pop_back();
    cout << s_str << endl;
    
    
    return 0;
}
