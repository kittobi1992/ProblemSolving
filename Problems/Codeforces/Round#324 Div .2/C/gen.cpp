#include <bits/stdc++.h>
#include <iostream>
using namespace std;


#define LENGTH 100000

int main() {

	cout << LENGTH << " " << (rand() % LENGTH) << endl;

	for(int i = 0; i < LENGTH; i++) {
		cout << ((char) ((rand() % 26) + 'a'));
	}
	cout << endl;

	for(int i = 0; i < LENGTH; i++) {
		cout << ((char) ((rand() % 26) + 'a'));
	}
	cout << endl;
		
		

	return 0;

}
