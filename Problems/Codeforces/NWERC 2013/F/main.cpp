#include <bits/stdc++.h>

using namespace std;

vector<int> lookup[10000][13][32];

vector<int> convertDate(string& s_date, string delim) {
    vector<int> date; char *token;
    token = strtok((char*)s_date.c_str(), (char*)delim.c_str());
    while(token != NULL) {
        date.push_back(stoi(string(token)));
        token = strtok(NULL,(char*)delim.c_str());
    }
    return date;
}

string toStringDate(vector<int>& date) {
    stringstream ss;
    ss << date[0] << "-" << (date[1] < 10 ? "0" : "") << date[1] << "-" << (date[2] < 10 ? "0" : "") << date[2];
    return ss.str();
}

vector<int> m {42,31,28,31,30,31,30,31,31,30,31,30,31};

int month_day(int month, int year, bool greg = false) {
    if(month != 2) return m[month];   
    bool is_leapyear = (year % 4 == 0);
    if(greg) is_leapyear = is_leapyear ^ (year % 100 == 0) ^ (year % 400 == 0);
    return 28 + is_leapyear; 
}


void proceed_to_next_day(vector<int>& j, vector<int>& g) {
    lookup[j[0]][j[1]][j[2]] = g;
    j[2]++; 
    if(j[2] > month_day(j[1],j[0])) {
        j[2] = 1; j[1]++;
    } 
    if(j[1] > 12) { j[1] = 1; j[0]++; }
    
    g[2]++;
    if(g[2] > month_day(g[1],g[0],true)) {
        g[2] = 1; g[1]++;
    } 
    if(g[1] > 12) { g[1] = 1; g[0]++; }
    
}

void precompute() {
    vector<int> date {9999,12,31};
    vector<int> jul_start {1582,10,4};
    vector<int> greg_start {1582,10,15};
    while(!(jul_start[0] == date[0] && jul_start[1] == date[1] && jul_start[2] == date[2])) {
        proceed_to_next_day(jul_start,greg_start);
    }
}

int main() {
    ios::sync_with_stdio(false);
    precompute();
    string s_date;
    while(cin >> s_date) {
        vector<int> date = convertDate(s_date, "-");
        if(lookup[date[0]][date[1]][date[2]].size() != 0) {
            cout << toStringDate(lookup[date[0]][date[1]][date[2]]) << endl;
        }
    }
    
	return 0;
}
