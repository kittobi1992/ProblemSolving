#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	while(cin >> n) {
	  if(n == 0)
	    break;
	  
	  vector<string> v(n);
	  for(int i = 0; i < n; i++)
	    cin >> v[i];
	  
	  sort(v.begin(),v.end(),[&](string i1, string i2) {
	    string v1 = i1+i2, v2 = i2+i1;
	    if(v1 > v2) return true;
	    else return false;
	  });
	  for(int i = 0; i < v.size(); i++)
	    cout << v[i];
	  cout << endl;
	  
	}
	
	return 0;
}
