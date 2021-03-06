#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;


int digit_value(char c) {
	int v1 = ((int) (c - 'a')) + 1;
	int v2 = ((int) (c - 'A')) + 1;
	if(v1 >= 1 && v1 <= 26)
		return v1;
	else if(v2 >= 1 && v2 <= 26)
		return v2;
	else
		return 0;
}

int quersum(int n) {
	int sum = 0;
	while(n != 0) {
		sum += n % 10;
		n /= 10;
	}
	return sum;
}

int love_sum(string s) {
	int love_sum = 0;
	for(int i = 0; i < s.size(); i++)
		love_sum += digit_value(s[i]);
	while(love_sum != (love_sum % 10))
		love_sum = quersum(love_sum);
	return love_sum;
}

int main() {
	
	string a, b;
	while(getline(cin,a)) {
		getline(cin,b);
		int sum1 = love_sum(a);
		int sum2 = love_sum(b);
		double p = (((double) min(sum1,sum2))/((double) max(sum1,sum2)))*100.0;
		if(sum1 == 0 && sum2 == 0) {
			cout << endl; continue;
		}
		cout << fixed << setprecision(2) << p << " %" << endl; 		
	}

	return 0;
}
