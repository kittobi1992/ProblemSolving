#include <bits/stdc++.h>

using namespace std;

vector<int> cnt(5,0);

struct Hexagon {
    int val;
    Hexagon *NE, *N, *NW, *SW, *S, *SE;
    
    Hexagon() : val(6), NE(nullptr),N(nullptr),NW(nullptr),
                        SW(nullptr),S(nullptr),SE(nullptr) { }
                        
    vector<pair<Hexagon*,string>> neighbor(string dir) {
        vector<pair<Hexagon*,string>> neighbor;
        if(dir == "NE") {
            neighbor.push_back(make_pair(this,"SW"));
            if(N) neighbor.push_back(make_pair(N,"NW"));
            if(N && N->NE) neighbor.push_back(make_pair(N->NE,"N"));        
        } else if(dir == "N") {
            neighbor.push_back(make_pair(this,"S"));
            if(NW) neighbor.push_back(make_pair(NW,"SW"));
            if(NW && NW->N) neighbor.push_back(make_pair(NW->N,"NW"));
        } else if(dir == "NW") {
            neighbor.push_back(make_pair(this,"SE"));
            if(SW) neighbor.push_back(make_pair(SW,"S"));
            if(SW && SW->NW) neighbor.push_back(make_pair(SW->NW,"SW")); 
        } else if(dir == "SW") {
            neighbor.push_back(make_pair(this,"NE"));
            if(S) neighbor.push_back(make_pair(S,"SE"));
            if(S && S->SW) neighbor.push_back(make_pair(S->SW,"S")); 
        } else if(dir == "S") {
            neighbor.push_back(make_pair(this,"N"));
            if(SE) neighbor.push_back(make_pair(SE,"NE"));
            if(SE && SE->S) neighbor.push_back(make_pair(SE->S,"SE")); 
        } else if(dir == "SE") {
            neighbor.push_back(make_pair(this,"NW"));
            if(NE) neighbor.push_back(make_pair(NE,"N"));
            if(NE && NE->SE) neighbor.push_back(make_pair(NE->SE,"NE")); 
        }
        return neighbor;
    }
    
    void addNeighbor(Hexagon *hex, string dir) {
        if(dir == "N") {
            N = hex;
            hex->S = this;
        } else if(dir == "NE") {
            NE = hex;
            hex->SW = this;
        } else if(dir == "NW") {
            NW = hex;
            hex->SE = this;
        } else if(dir == "S") {
            S = hex;
            hex->N = this;
        } else if(dir == "SW") {
            SW = hex;
            hex->NE = this;
        } else if(dir == "SE") {
            SE = hex;
            hex->NW = this;
        }
    }
    
    bool neighborExist(string dir) {
        if(dir == "NE") return (NE ? true : false);
        if(dir == "NW") return (NW ? true : false);
        if(dir == "N") return (N ? true : false);
        if(dir == "SW") return (SW ? true : false);
        if(dir == "S") return (S ? true : false);
        return (SE ? true : false);
    }
    
    void determineVal() {
        vector<int> tmp_cnt(5,0);
        for(int i = 0; i < 5; ++i) tmp_cnt[i] = cnt[i];
        if(N) tmp_cnt[N->val-1] = INT_MAX;
        if(NE) tmp_cnt[NE->val-1] = INT_MAX;
        if(NW) tmp_cnt[NW->val-1] = INT_MAX;
        if(SE) tmp_cnt[SE->val-1] = INT_MAX;
        if(SW) tmp_cnt[SW->val-1] = INT_MAX;
        if(S) tmp_cnt[S->val-1] = INT_MAX;
        int min_cnt = INT_MAX;
        int min_idx = 0;
        for(int i = 0; i < 5; ++i) {
            if(tmp_cnt[i] < min_cnt) {
                min_cnt = tmp_cnt[i];
                min_idx = i+1;
            }
        }
        val = min_idx;
        cnt[val-1]++;
    }
    
};

int main() {
    
        vector<Hexagon> hex(10010,Hexagon());
        hex[0].determineVal();
        
        vector<pair<Hexagon*,string>> neigh = hex[0].neighbor("NE");
        for(auto i : neigh) {
            hex[1].addNeighbor(i.first,i.second);
        }
        hex[1].determineVal();
//         cout << hex[0].val << endl;
//         cout << hex[1].val << endl;
        
        vector<string> dir = {"NE","N","NW","SW","S","SE"};
        int cur_dir = 2;
        int i = 1;
        while(i < 10005) {
            string direction = dir[cur_dir];
//             cout << direction << endl;
            vector<pair<Hexagon*,string>> neigh = hex[i].neighbor(direction);
            for(auto a : neigh) {
//                 cout << i << ": " << a.first->val << " " << a.second << endl;
                hex[i+1].addNeighbor(a.first,a.second);
            }            
            hex[i+1].determineVal();
//             cout << hex[i+1].val << endl;
            string next_dir = dir[(cur_dir+1)%6];
//             cout << "Next dir: " << next_dir << " " << hex[i+1].neighborExist(next_dir)<< endl;
            if(!hex[i+1].neighborExist(next_dir)) cur_dir = (cur_dir+1)%6;
            i++;
        }
        
        int test; cin >> test;
        while(test--) {
            int n; cin >> n;
            n--;
            cout << hex[n].val << endl;
        }
  
	return 0;
}
