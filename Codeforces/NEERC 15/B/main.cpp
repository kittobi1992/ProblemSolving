#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<string> bindecimal;

string divideBy2(string& n) {
    ll remainder = 0;
    string s = "";
    bool firstOne = false;
    for(int i = 0; i < n.size(); i++) {
        remainder = remainder*10 + ((ll) (n[i]-'0'));
        if((remainder / 2) > 0 || firstOne) { s += ((char) ((remainder/2)+'0')); firstOne = true; }
        remainder = remainder % 2;
    }
    return s;
}

pair<bool,string> isBindecimal(string& n) {
    string tmp = n;
    int N = n.size();
    string bin = "";
    int i = 1;
    while(i <= N) {
        if(((int)(tmp[tmp.size()-1]-'0')) % 2 != ((int)(n[N-i]-'0'))) return make_pair(false,"");
        tmp = std::move(divideBy2(tmp));
        i++;
    }
    return make_pair(true,tmp);
}

int main() {
//     freopen("binary.in", "r",stdin);
//     freopen("binary.out", "w",stdout);
    
    
    queue<pair<string,string>> q; q.push(make_pair("0","0")); q.push(make_pair("1",""));
    while(!q.empty() && bindecimal.size() != 10100) {
        string s1 = q.front().first; 
        if(s1[0] == '0') {
            string s2 = q.front().second;
            if(((int)(s2[s2.size()-1]-'0')) % 2 == ((int)(s1[0]-'0'))) {
                s2 = divideBy2(s2);
                q.push(make_pair("0"+s1,s2)); q.push(make_pair("1"+s1,""));
            }
        } else {
            auto isBin = isBindecimal(s1);
            if(isBin.first) {
                bindecimal.push_back(s1);
                q.push(make_pair("0"+s1,isBin.second)); q.push(make_pair("1"+s1,""));
            }
        }
        q.pop();
    }
    
    sort(bindecimal.begin(),bindecimal.end(),[&](const string& s1, const string& s2) {
        return s1.size() < s2.size() || (s1.size() == s2.size() && s1.compare(s2) < 0);
    });
    
    
    int N; cin >> N; 
    cout << bindecimal[N-1] << endl;
    
    
    
	return 0;
}
