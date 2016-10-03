#include <bits/stdc++.h>

using namespace std;

double k,l,s,w;
double g = 9.81, delta = 0.001;


int main() {
  
    while(cin >> k >> l >> s >> w) {
        if(k == 0 && l == 0 && s == 0 && w == 0) break;
        //19.8093 20.0015 2.0192
        
        double cur_v = 0.0, cur_x = 0.0, cur_t = 0.0, a = g;
        while(cur_v >= 0.0 && cur_x < s) {
            if(cur_x > l) a = (g*w - k*(cur_x-l))/w;
            else a = g;
            cur_v += delta*a;
            cur_x += cur_v*delta;
            //cout << cur_v << " " << cur_x << " " << cur_t << endl;
            cur_t += delta;
        }
        
        if(cur_x >= s && cur_v > 10.0) cout << "Killed by the impact." << endl;
        else if(cur_x >= s && cur_v <= 10.0) cout << "James Bond survives." << endl;
        else cout << "Stuck in the air." << endl;
        
    }
    
	return 0;
}
