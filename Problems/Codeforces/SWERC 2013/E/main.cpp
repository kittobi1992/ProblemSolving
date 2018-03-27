#include <bits/stdc++.h>

using namespace std;

int N;

unordered_map<string,bool> ngrams;

void learnSentence(vector<string>& sentence, bool ignore_words = false) {
    for(int i = 1+ignore_words; i <= N; ++i) {
        for(int j = 0; j <= static_cast<int>(sentence.size())-i; ++j) {
            string s = "";
            for(int k = 0; k < i; ++k) s += sentence[j+k] + " ";
            s.pop_back();
            std::transform(s.begin(), s.end(), s.begin(), ::tolower);
            ngrams[s] = true;
        }
    }
}

void checkUnderstanding(vector<string>& sentence) {
    string sen = "";
    for(int i = 0; i < sentence.size(); ++i) sen += sentence[i] + " ";
    sen.pop_back();
    bool understand = true;
    for(int i = 1; i <= N; ++i) {
        for(int j = 0; j <= static_cast<int>(sentence.size())-i; ++j) {
            string s = "";
            string word = "";
            for(int k = 0; k < i; ++k) { s += sentence[j+k] + " "; }
            s.pop_back();
            if(i == 1) { word = s;}
            std::transform(s.begin(), s.end(), s.begin(), ::tolower);
            if(!ngrams.count(s)) {
                if(i == 1) {
                    ngrams[s] = true;
                    cout << "What does the word \"" << word << "\" mean?" << endl;
                }
                understand = false;
            } 
        }
    }
    
    if(!understand && sentence.size() > 1)
        cout << "What does the sentence \"" << sen << "\" mean?" << endl;
    
}

int main() {
  
    int test = 1;
    while(cin >> N) {
        cout << "Learning case " << test++ << endl;
        ngrams["joe"] = true;
        vector<string> sentence; string cur;
        while(cin >> cur) {
            if(cur[0] == '*' || cur[0] == '.' || cur[0] == ',' || cur[0] == ':' || cur[0] == ';' || cur[0] == '?' || cur[0] == '!') {
                if(sentence.size() != 0)
                    learnSentence(sentence);
                sentence.clear();    
                if(cur[0] == '*') break;
            }
            else {
                sentence.push_back(cur);
            }
        }
        
        while(cin >> cur) {
            if(cur[0] == '#' || cur[0] == '.' || cur[0] == ',' || cur[0] == ':' || cur[0] == ';' || cur[0] == '?' || cur[0] == '!') {
                if(sentence.size() != 0) {
                    checkUnderstanding(sentence);
                    learnSentence(sentence,true);
                }
                sentence.clear();    
                if(cur[0] == '#') break;
            }
            else {
                sentence.push_back(cur);
            }
        }
        
        unordered_map<string,bool> empty;
        ngrams = std::move(empty);
        cout << endl;
        
    }
    
	return 0;
}
