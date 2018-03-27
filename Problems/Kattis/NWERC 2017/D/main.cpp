#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, m;
map<string, vector<string>> correct;
map<string, vector<string>> incorrect;
vector<string> sentence;
vector<string> translation;

void insert(const string& d, const string& e, const string& c) {
    if(c == "correct") {
        if(correct.find(d) == correct.end()) correct.insert(make_pair(d,vector<string>(0)));
        correct[d].push_back(e);
    }
    else {
        if(incorrect.find(d) == incorrect.end()) incorrect.insert(make_pair(d,vector<string>(0)));
        incorrect[d].push_back(e);
    }
}

ll numTranslation(const string& d) {
    ll num = 0;
    if(correct.find(d) != correct.end()) num += correct[d].size();
    if(incorrect.find(d) != incorrect.end()) num += incorrect[d].size();
    return num;
}

ll numCorrectTranslation(const string& d) {
    ll num = 0;
    if(correct.find(d) != correct.end()) num += correct[d].size();
    return num;
}

ll numIncorrectTranslation(const string& d) {
    ll num = 0;
    if(incorrect.find(d) != incorrect.end()) num += incorrect[d].size();
    return num;
}

bool translate(const string& d, string& trans) {
    // Precondition: numTranslation(d) == 1
    if(correct.find(d) != correct.end()) {
        trans = correct[d][0];
        return true;
    } else {
        trans = incorrect[d][0];
        return false;   
    }
}

int main() {

    cin >> n;
    sentence.resize(n);
    translation.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> sentence[i];
    }

    cin >> m;
    for(int i = 0; i < m; ++i) {
        string d, e, c;
        cin >> d >> e >> c;
        insert(d,e,c);
    }

    ll numCorrect = 1;
    ll numIncorrect = 1;
    bool correctTrans = true;
    bool foundTranslation = true;
    for(int i = 0; i < n; ++i) {
        int numTrans = numTranslation(sentence[i]);
        if(numTrans == 1) {
            correctTrans &= translate(sentence[i], translation[i]);
        } else {
            numCorrect *= numCorrectTranslation(sentence[i]);
            numIncorrect *= numTrans;
            foundTranslation = false;
        }
    }

    numIncorrect -= numCorrect;

    if(foundTranslation) {
        for(int i = 0; i < n; ++i) {
            cout << translation[i] << (i == n-1 ? "\n" : " ");
        }
        cout << (correctTrans ? "correct" : "incorrect") << endl;
    }
    else {
        cout << numCorrect << " correct" << endl;
        cout << numIncorrect << " incorrect" << endl; 
    }

    return 0;
}