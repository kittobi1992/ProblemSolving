#include <iostream>
#include <string>

using namespace std;

int main() {
	
	int test;
	cin >> test;
	while(test--) {
			int a, b;
			string op;
			cin >> a >> op >> b;
			bool res;
			
			if(op.compare("!=") == 0) {
					res = a != b;
			} else if(op.compare("==") == 0) {
					res = a == b;
			} else if(op.compare("<") == 0) {
					res = a < b;
			} else if(op.compare("<=") == 0) {
					res = a <= b;
			} else if(op.compare(">") == 0) {
					res = a > b;
			} else if(op.compare(">=") == 0) {
					res = a >= b;
			}
			
			if(res)
				cout << "true" << endl;
			else	
				cout << "false" << endl;
			
	}
	
	return 0;
}
