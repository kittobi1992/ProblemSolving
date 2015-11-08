#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <cmath>
using namespace std;

typedef pair<int,int> edge;
typedef vector<edge> graph;

bool used[25];

vector<string> split(string &s, string delim) { // zerlegt s anhand aller Zeichen in delim
    vector <string> result; char *token;
    token = strtok((char*)s.c_str(), (char*) delim.c_str());
    while (token != NULL) {
        result.push_back(string(token));
        token = strtok(NULL , (char*) delim.c_str());
    }
    return result;
}


int main() {
    
    
    string line;
    getline(cin,line);
    stringstream ss3(line);
    int test; ss3 >> test;
    bool first = true;
    while(test--) {
        
        if(!first) {
                getline(cin,line);
        }
        first = false;
        
        int n, m;  getline(cin,line);
        stringstream ss(line);
        ss >> n >> m;
        
        
        
        map<string,int> ma;
        vector<int> w(n,0);
        for(int i = 0; i < n; i++) {
                string t;
                getline(cin,t);
                vector<string> sp = split(t," ");
                string topic = "";
                for(int j = 0; j < sp.size()-2; j++)
                    topic += sp[j] + " ";
                topic += sp[sp.size()-2];
                int weight = atoi(sp[sp.size()-1].c_str());
                ma[topic] = i;
                w[i] = weight;
        }
        
        graph g;
        for(int i = 0; i < m; i++) {
                string t1, p, t2;
                getline(cin,line);
                vector<string> sp = split(line," ");
                int pos = 0;
                for(int j = 0; j < sp.size(); j++) {
                        if(sp[j] == "-->") {
                                pos = j;
                                break;
                        }
                }
                for(int j = 0; j < pos-1; j++)
                    t1 += sp[j] + " ";
                t1 += sp[pos-1];
                for(int j = pos+1; j < sp.size()-1; j++)
                    t2 += sp[j] + " ";
                t2 += sp[sp.size()-1];
                int a = ma[t1]; int b = ma[t2];
                g.push_back(make_pair(a,b));
        }

        
        vector<int> dp = vector<int>((1 << n), -1);
        dp[0] = 0;
        
        for(int i = 1; i < (1 << n); i++) {
            memset(used,0,sizeof(used));
            int k = 0;
	    for(int j = 0; j < n; j++) {
		if((i >> j) & 1) {
			used[j] = true;
			k++;
		}
	    }

	    bool invalid = false;
	    for(int j = 0; j < g.size(); j++) {
		if(!used[g[j].first] && used[g[j].second]) {
			invalid = true;
			break;
		}
	    }
		
 	    if(invalid)
		continue;

            for(int j = 0; j < n; j++) {
		if(used[j]) {
		        int val = dp[i - (1 << j)];
		        if(val != -1) {
		    	    dp[i] = max(dp[i], val + w[j]*k);
		        }
		}
            }
       }
        
        cout << dp[(1 << n) - 1] << endl;
        
    }
    
    return 0;
}
