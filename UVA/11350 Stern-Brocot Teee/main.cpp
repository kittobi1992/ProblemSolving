#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

struct elem {
	pll value;
	elem *prev, *next;	
};

int main() {
  
  int test; cin >> test;
  while(test--) {
		string s; cin >> s;
		
		elem e1 {{0,1},nullptr,nullptr};
		elem e2 {{1,1},nullptr,nullptr};
		elem e3 {{1,0},nullptr,nullptr};
		vector<elem> v {e1,e2,e3};
		v[0].prev = &v[0]; v[0].next = &v[1];
		v[1].prev = &v[0]; v[1].next = &v[2];
		v[2].prev = &v[1]; v[2].next = &v[2];
		
		elem *cur = &v[1];
		for(int i = 0; i < s.size(); ++i) {
			bool right = (s[i] == 'R');
			if(right) {
				ll a = cur->value.first + cur->next->value.first;
				ll b = cur->value.second + cur->next->value.second;
				elem e {{a,b},nullptr,nullptr};	int idx = v.size();
				v.push_back(e);
				v[idx].next = cur->next; v[idx].prev = cur;
				cur->next->prev = &v[idx]; cur->next = &v[idx];
				cur = &v[idx];
			}
			else {
				ll a = cur->value.first + cur->prev->value.first;
				ll b = cur->value.second + cur->prev->value.second;
				elem e {{a,b},nullptr,nullptr};	int idx = v.size();
				v.push_back(e);
				v[idx].next = cur; v[idx].prev = cur->prev;
				cur->prev->next = &v[idx]; cur->prev = &v[idx];
				cur = &v[idx];
			}
		}
		
		cout << cur->value.first << "/" << cur->value.second << endl;
		
		
  }
	
  return 0;
}
