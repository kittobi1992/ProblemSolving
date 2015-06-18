#include <bits/stdc++.h>
#include <iostream>

using namespace std;


int distance(string median, string vote) {
	map<char,int> m_map;
	map<char,int> v_map;
	int n = median.size();
	for(int i = 0; i < n; i++) {
		m_map[median[i]] = i;
		v_map[vote[i]] = i;
	}

	int distance = 0;
	for(int i = 0; i < 5; i++) {
		char a = ((char) i+'A');
		for(int j = i+1; j < 5; j++) {
			char b = ((char) j+'A');
			if((m_map[a] < m_map[b]) != (v_map[a] < v_map[b]))
				distance++;
		}
	}
	return distance;

}

int main() {

	int n;
	while(cin >> n) {
		if(n == 0)
			break;
	
		vector<string> votes(n);
		for(int i = 0; i < n; i++) {
			cin >> votes[i];
		}
		
		int best_sum = INT_MAX;
		string best_permutation = "ABCDE";
		string current_p = "ABCDE";
		do {
			int sum = 0;
			for(int i = 0; i < n; i++) {
				sum += distance(current_p,votes[i]);
			}
			if(sum < best_sum) {
				best_sum = sum;
				best_permutation = current_p;
			}
		} while(next_permutation(current_p.begin(),current_p.end()));

		cout << best_permutation << " is the median ranking with value " << best_sum << "." << endl;
	}  

	return 0;

}
