#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

ld hps = 360.0L/(12.0L*60.0L*60.0L), mps = 360.0L/(60.0L*60.0L);

string time_to_string(int h, int m, int s) {
    stringstream ss;
    ss << h << ":" << (m < 10 ? "0" : "") << m << ":" << (s < 10 ? "0" : "") << s;
    string time(ss.str());
    return time;
}



int main() {
  
    int t; cin >> t;
    for(int i = 1; i <= t; ++i) {
        ld deg; int h; string c;
        cin >> deg >> c >> h;
        ld h_angle = (12-h)*30.0L;
        ld min_diff = deg - h_angle;
        if(c == "after") {
            if(min_diff <= 0) min_diff += 360.0L;
            ld mins = min_diff*(2.0L/11.0L);
            if(mins >= 60.0L) {
                h++;
                if(h == 13) h = 1; 
                mins -= 60.0L;
            }
            int secs = (int)((mins - (int)mins)*60.0L+0.5L);
            cout << "Case " << i << ": " << time_to_string(h,(int)(mins),secs) << endl;
        }
        else {
            h--;
            if(min_diff >= 0) min_diff -= 360.0L;
            ld mins = min_diff*(2.0L/11.0L);
            if(mins <= -60.0) {
                h--;
                mins += 60.0;
            }
            if(h < 1) h += 12;
            if(mins == 0.0L) {
                h++;
                if(h > 12) h -= 12;
            }
            else
                mins = 60.0L + mins;
            int secs = (int)((mins - (int)mins)*60.0L+0.5L);
            cout << "Case " << i << ": " << time_to_string(h,(int)(mins),secs) << endl;
        }
    }
    
	return 0;
}
