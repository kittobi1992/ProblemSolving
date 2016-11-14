#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<string> bindecimal;
vector<string> div10(200);

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

pair<bool,string> isBindecimal(string& n, bool before = false) {
    string tmp = n;
    int N = n.size();
    string bin = "";
    int i = 1;
    while(i <= N-before) {
        if(((int)(tmp[tmp.size()-1]-'0')) % 2 != ((int)(n[N-i]-'0'))) return make_pair(false,"");
        tmp = std::move(divideBy2(tmp));
        i++;
    }
    return make_pair(true,tmp);
}

string add(string& s1, string& s2) {
    string s = "";
    int i = s1.size()-1; int j = s2.size()-1; 
    int carry = 0;
    while(i != -1 || j != -1 || carry != 0)  {
        int num1 = (i != -1 ? s1[i]-'0' : 0);
        int num2 = (j != -1 ? s2[j]-'0' : 0);
        int num3 = num1+num2+carry;
        carry = num3/10;
        s += ((num3%10) + '0');
        if(i != -1) i--;
        if(j != -1) j--;
    }
    reverse(s.begin(),s.end());
    return s;
}

int main() {
//     freopen("binary.in", "r",stdin);
//     freopen("binary.out", "w",stdout);
    
    string s = "1";
    for(int i = 1; i < 200; ++i) {
        div10[i]= isBindecimal(s,true).second;
        s.push_back('0');
    }
    
    queue<pair<string,string>> q; q.push(make_pair("0","0")); q.push(make_pair("1","0"));
    while(!q.empty() && bindecimal.size() != 10100) {
        string s1 = q.front().first; 
        string s2 = q.front().second;
        if(s1[0] == '0') {
            if(((int)(s2[s2.size()-1]-'0')) % 2 == ((int)(s1[0]-'0'))) {
                s2 = divideBy2(s2);
                q.push(make_pair("0"+s1,s2)); q.push(make_pair("1"+s1,s2));
            }
        } else {
            string s3 = add(s2,div10[s1.size()]);
            if(((int)(s3[s3.size()-1]-'0')) % 2 == 1) {
                s3 = divideBy2(s3);
                bindecimal.push_back(s1);
                q.push(make_pair("0"+s1,s3)); q.push(make_pair("1"+s1,s3));
            }
        }
        q.pop();
    }
    
    
    sort(bindecimal.begin(),bindecimal.end(),[&](const string& s1, const string& s2) {
        return s1.size() < s2.size() || (s1.size() == s2.size() && s1.compare(s2) < 0);
    });
    
    
    int N; 
    while(cin >> N) cout << bindecimal[N-1] << endl;
    
    
    
	return 0;
}
