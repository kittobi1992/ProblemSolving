#include <bits/stdc++.h>

using namespace std;

string invert(string& s) {
  string t;
  for(int i = 0; i < s.size(); i++)
    t.push_back((s[i] == '+' ? '*' : '+'));
  return t;
}


int main() {
	vector<string> mat(2);
	mat[0] = "++";
	mat[1] = "+*";
	for(int i = 2; i <= 9; i++) {
	  vector<string> copy_mat(mat);
	  for(int j = 0; j < copy_mat.size(); j++)
	    mat[j] += copy_mat[j];
	  for(int j = 0; j < copy_mat.size(); j++)
	    mat.push_back(copy_mat[j] + invert(copy_mat[j]));
	}
	
	int k; cin >> k;
	int n = ((int)pow(2,k));
	for(int i = 0; i < n; i++) {
	  cout << mat[i].substr(0,n) << endl;
	}

	return 0;
}
