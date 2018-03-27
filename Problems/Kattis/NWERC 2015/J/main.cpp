#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int get_bit(int b, int i) {
	return (b & (1 << i)) >> i;
}

int main() {

	int n; cin >> n;
	vector<int> b(n);
	for(int i = 0; i < n; i++) 
		cin >> b[i];

	for(int i = 0; i < n; i++) {
		int num = 0;
		if(get_bit(b[i],0))
			num = 1;
		int last_bit = get_bit(b[i],0);
		for(int j = 1; j < 8; j++) {
			int cur_bit = get_bit(b[i],j);
			if((cur_bit && !last_bit) || (!cur_bit && last_bit)) {
				num |= (1 << j); last_bit = 1;
			}
			else
				last_bit = 0;
		}
		b[i] = num;
	}

	for(int i = 0; i < n; i++)
		cout << (i == 0 ? "" : " ") << b[i];
	cout << endl;

	return 0;
}
