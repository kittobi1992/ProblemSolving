#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <sstream>
using namespace std;

typedef long long ll;


int main() {

	string toy;
	while(getline(cin,toy)) {
		stringstream str(toy);
		ll first; str >> first;
		vector<ll> ts, ss;
		ts.push_back(abs(first)); ss.push_back(0);
		bool isMatri = true;
		ll t = 0;
		while(abs(first) != t) {
			str >> t;
			if(t < 0) {
				ss[ss.size()-1] -= t;
				if(ss[ss.size()-1] >= ts[ts.size()-1]) {
					isMatri = false;
					break;
				}
				ts.push_back(abs(t)); ss.push_back(0);
			}
			else {
				if(ts[ts.size()-1] != t) {
					isMatri = false;
					break;
				}
				ts.pop_back(); ss.pop_back();
			}
		}

		if(isMatri)
			cout << ":-) Matrioshka!" << endl;
		else {
			cout << ":-( Try again." << endl;
		}
	}

}
