#include <bits/stdc++.h>

using namespace std;

using freq = pair<int,string>;

unordered_map<string,int> m;
vector<string> cur_words;

vector<vector<string>> days;
int cur_day = -1;

auto comp = [&](const string& s1, const string& s2) {
    auto val1 = m[s1], val2 = m[s2];
    return val1 > val2 || (val1 == val2 && s1.compare(s2) < 0);
};

void incrementWord(string& word) {
    if(m.find(word) != m.end()) m[word]++;
    else { m[word] = 1; cur_words.push_back(word); }
}

void decrementWord(string& word) {
    if(m.find(word) != m.end()) {
        m[word]--;
    }
}

void topk() {
    int K; string c; cin >> K >> c;
    sort(cur_words.begin(),cur_words.end(),comp);
    while(m[cur_words.back()] == 0) {
        m.erase(cur_words.back());
        cur_words.pop_back();
    }
    int last_freq = -1, cur_idx = 0;
    cout << "<top " << K << ">" << endl;
    while(cur_idx < cur_words.size()) {
        int freq = m[cur_words[cur_idx]];
        if(cur_idx >= K && last_freq != freq) break;
        cout << cur_words[cur_idx++] << " " << freq << endl;
        last_freq = freq;
    }
    cout << "</top>" << endl;
}


void readText() {
    vector<string> day;
    string word;
    while(cin >> word && word != "</text>") {
        if(word.size() >= 4) {
            day.push_back(word);
            incrementWord(word);
        }
    }
    cur_day++;
    days.push_back(day);
    
    if(cur_day >= 7) {
        for(string word : days[cur_day-7]) {
            decrementWord(word);
        }
    }
    
}

int main() {
    
    string tag;
    while(cin >> tag) {
        if(tag == "<text>") readText();
        else if(tag == "<top") topk();
    }
    
	return 0;
}
