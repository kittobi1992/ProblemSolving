#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int sudoku[9][9];

bool checkElements(vector<int> elem) {
	sort(elem.begin(), elem.end());
	
	for (int i = 1; i <= 9; i++) {
		if (elem[i - 1] != i) return false;
	}
	return true;
}

bool checkBlock(int a, int b) {
	vector<int> elem;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			elem.push_back(sudoku[a+i][b+j]);
		}
	}
	return checkElements(elem);
}

bool checkRow(int a) {
	vector<int> elem;
	for (int i = 0; i < 9; i++) {
		elem.push_back(sudoku[a][i]);
	}
	return checkElements(elem);
}

bool checkCol(int a) {
	vector<int> elem;
	for (int i = 0; i < 9; i++) {
		elem.push_back(sudoku[i][a]);
	}
	return checkElements(elem);
}

void solve() {
	int i, j;
	string line;
	
	for (i = 0; i < 9; i++) {
		cin >> line;
		for (j = 0; j < 9; j++) {
			sudoku[i][j] = line[j] - '0';
		}
	}
	
	for (i = 0; i < 9; i += 3) {
		for (j = 0; j < 9; j += 3) {
			if (!checkBlock(i, j)) {
				cout << "Invalid" << endl;
				return;
			}
		}
	}
	
	for (i = 0; i < 9; i++) {
		if (!checkRow(i) || !checkCol(i)) {
			cout << "Invalid" << endl;
			return;
		}
	}
	
	cout << "Valid" << endl;
}

int main() {
	int cases;
	
	cin >> cases;
	while (cases--) {
		solve();
	}
	return 0;
}
