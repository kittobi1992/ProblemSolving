#include <iostream>
#include <cmath>
using namespace std;

int main() {
	/* BEGIN_SOL */
	int n, b, h, w;
	while(cin >> n >> b >> h >> w) {
		bool foundHotel = false; int price = b+1;
		for(int i = 0; i < h; i++) {
			int p; cin >> p;
			bool foundSpace = false;
			for(int j = 0; j < w; j++) {
				int a; cin >> a;
				if(a >= n)
					foundSpace = true;
			}
			if(foundSpace && p*n <= b)
				price = min(price,p*n);
		}
		if(price <= b)
			cout << price << endl;
		else
			cout << "stay home" << endl;
	}
	/* END_SOL */
}
