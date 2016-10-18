#include <bits/stdc++.h>

using namespace std;

int N;

struct Triangle {

    Triangle(int i, int a, int b, int c) : e(3,0), s(3,0) {
        idx = i;
        e[0] = a; e[1] = b; e[2] = c;
        s[0] = false; s[1] = false; s[3] = false;
    }
    
    bool set(int a) {
        if(e[0] == a && !s[0]) {
            s[0] = true; numEdges++;
        } else if(e[1] == a && !s[1]) {
            s[1] = true; numEdges++;
        } else if(e[2] == a && !s[2]) {
            s[2] = true; numEdges++;
        }
        if(numEdges == 3) return true;
        else return false;
    }
    
    void unset(int a) {
        if(e[0] == a && s[0]) {
            s[0] = false; numEdges--;
        } else if(e[1] == a && s[1]) {
            s[1] = false; numEdges--;
        } else if(e[2] == a && s[2]) {
            s[2] = false; numEdges--;
        }
    }
    
    int unsetEdge() {
        if(!s[0]) return e[0];
        else if(!s[1]) return e[1];
        else if(!s[2]) return e[2];
    }
    
    vector<int> e;
    vector<bool> s;
    int numEdges = 0;
    int idx;
};


int play(vector<Triangle> t, int A, int R, int player) {
    
    sort(t.begin(),t.end(),[&](const Triangle& t1, const Triangle& t2) {
        return t1.numEdges < t2.numEdges || (t1.numEdges == t2.numEdges && t1.idx < t2.idx);
    });
    
    int tmp_A = A;
    int tmp_R = R;
    while( t.size() > 0 && t[t.size()-1].numEdges >= 2) {
//         cout <<t[t.size()-1].numEdges << " " << t[t.size()-1].e[0] << " " << t[t.size()-1].e[1] << " " << t[t.size()-1].e[2] << endl;
        if(t[t.size()-1].numEdges == 2) {
            int e = t[t.size()-1].unsetEdge();
            for(int i = 0; i < t.size(); ++i) t[i].set(e);
        }
        if(player == 0) tmp_A++;
        else tmp_R++;
        t.pop_back();
        sort(t.begin(),t.end(),[&](const Triangle& t1, const Triangle& t2) {
            return t1.numEdges < t2.numEdges || (t1.numEdges == t2.numEdges && t1.idx < t2.idx);
        });
    }
    

    
    if(t.size() == 0) {
//            cout << t.size() << " " << tmp_A << " " << tmp_R << " " << player <<  endl;
        if(tmp_A > tmp_R) return 2;
        else if(tmp_A == tmp_R) return 1;
        else return 0;
    }
    
    int min_e = t[0].numEdges;
    int idx = 0; set<int> edges;
    while(idx < t.size()) {
        if(!t[idx].s[0]) edges.insert(t[idx].e[0]);
        if(!t[idx].s[1]) edges.insert(t[idx].e[1]);
        if(!t[idx].s[2]) edges.insert(t[idx].e[2]);
        idx++;
    }
    
    
    int ans = INT_MAX;
    if(player == 0) ans = 0;
    for(int e : edges) {
            for(int i = 0; i < t.size(); ++i) t[i].set(e);
            int res = play(t,tmp_A,tmp_R,(player+1) % 2);
            if(player == 0) ans = max(ans,res);
            else ans = min(ans,res);
            for(int i = 0; i < t.size(); ++i) t[i].unset(e); 
    }
    
//     cout << player << " " << ans << endl;
    
    return ans;
    
    
}

int main() {
    
    while(cin >> N) {
        if(N == 0) break;
        
        vector<Triangle> t = {Triangle(0,1,2,3),Triangle(1,4,5,6),Triangle(2,3,5,7),
                              Triangle(3,7,8,9),Triangle(4,10,11,12),Triangle(5,6,11,13),
                              Triangle(6,13,14,15),Triangle(7,9,14,16),Triangle(8,16,17,18)};

        for(int i = 0; i < N; ++i) {
            int e; cin >> e;
            for(int j = 0; j < t.size(); ++j) t[j].set(e);
        }
        
        sort(t.begin(),t.end(),[&](const Triangle& t1, const Triangle& t2) {
            return t1.numEdges < t2.numEdges || (t1.numEdges == t2.numEdges && t1.idx < t2.idx);
        });
        while(t[t.size()-1].numEdges == 3) t.pop_back();
        
        int res = play(t,0,0,0);
        if(res == 2) cout << "Andy wins" << endl;
        else if(res == 1) cout << "Draw" << endl;
        else cout << "Ralph wins" << endl;
                              
    }
    
    return 0;
}
