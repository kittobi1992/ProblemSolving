#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <vector>

using namespace std;

void createHotel(int n, int b, int w, bool stayHotel) {
	if(stayHotel) {
		int maxPrice = b/n;
		int price = max(1, maxPrice - (rand() % maxPrice));
		cout << price << endl;
		vector<int> weekend(w);
		for(int i = 0; i < w; i++) {
			weekend[i] = rand() % (2*n);
		}
		bool isPlace = false;
		for(int i = 0; i < w; i++) {
			if(weekend[i] >= n) {
				isPlace = true;
				break;
			}
		}
		if(!isPlace) {
			int makePlaceInWeekend = rand() % w;
			weekend[makePlaceInWeekend] = n + (rand() % n);
		}
		for(int i = 0; i < w-1; i++)
			cout << weekend[i] << " ";
		cout << weekend[w-1] << endl;
	}
	else {
		int maxPrice = b/n;
		int price = max(1, maxPrice - (rand() % maxPrice) + (rand() % maxPrice));
		cout << price << endl;
		vector<int> weekend(w);
		if(n*price > b) {
			for(int i = 0; i < w; i++) {
				weekend[i] = rand() % (2*n);
			}
		}
		else {
			for(int i = 0; i < w; i++) {
				weekend[i] = rand() % n;
			}
		}
		for(int i = 0; i < w-1; i++)
			cout << weekend[i] << " ";
		cout << weekend[w-1] << endl;
	}
}

int main() {
   
	srand(time(NULL));

	int n = 100;
	int b = 2000;
	int h = 10;
	int w = 5;
	bool stay_home = false;
	vector<bool> stayHotel(h,false);

	if(!stay_home) {
		bool change = false;
		for(int i = 0; i < h; i++) {
			int flip = rand() % 2;
			if(flip) {
				stayHotel[i] = !stayHotel[i];
				change = true;
			}
		}
		if(!change) {
			int flipHotel = rand() % h;
			stayHotel[flipHotel] = !stayHotel[flipHotel];
		}
	}
 

	cout << n << " " << b << " " << h << " " << w << endl;

	for(int i = 0; i < h; i++) {
		createHotel(n,b,w,stayHotel[i]);
	}
	
}
