#include <bits/stdc++.h>

using namespace std;


int main() {
	
	int TEST = 10;
	for(int j = 0; j < TEST; j++) {
	  int N = 10000, M = 10000;
	  int MAX_NUM = 1;
	  for(int i = 0; i < (rand() % N); i++) 
	    cout << ((char) (33 + rand()%MAX_NUM));
	  cout << endl;
	  for(int i = 0; i < (rand() % M); i++) 
	    cout << ((char) (33 + rand()%MAX_NUM));
	  cout << endl;
	}
  
	return 0;
}
