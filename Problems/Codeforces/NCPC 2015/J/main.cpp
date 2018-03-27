#include <bits/stdc++.h>

using namespace std;


struct{
    
    map<string, trie> tl;
    set<string> ans;
} trie;

int main() {
//     freopen("f.in", "r",stdin);
//     freopen("f.out", "w",stdout);
    
        ll t, n;
        
        cin >> t >> n;
        
        vector< vector<string> > ql(n);
        
        for(int i = 0; i < n; i++){
            while(true){
                string s;
                cin >> s;
                ql[i].pb(s);
                if(s.back() == '?') break;
            }
            
            string ans;
            cin >> ans;
            
            ql[i].pb(ans);
        }
    
        sort(ql.begin(), ql.end());
    
        trie root;
        
        trie* cur = &root;
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < ql[i].size()-1; j++){
                if(cur->tl.find(ql[i][j]) == ql[i][j].end()){
                    cur->tl[ql[i][j]] = trie();
                }
                
                cur->ans.insert(ql[i].back());
                cur = &cur->tl[ql[i][j]];
            }
        }
        
        
            
        
	return 0;
}
