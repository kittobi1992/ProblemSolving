#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <sstream>
using namespace std;

#define INF 32000

typedef long long ll;

vector<char> sign {'/','*','-','+'};
ll target_num; int p;
vector<vector<bool>> visited;
vector<ll> ops;

void printEquation(vector<ll>& num, vector<ll>& ops, ll target_num) {
	cout << num[0];
	for(int i = 0; i < ops.size(); i++) {
		cout << sign[ops[i]] << "" << num[i+1];
	}
	cout << "=" << target_num << endl;
}


bool isValidOperation(vector<ll>& num, ll res, int pos, int operation) {
	if(operation == 0) {
		if(res % num[pos] != 0)
			return false;
	} else if(operation == 1) {
		if(res * num[pos] >= INF || res * num[pos] <= -INF)
			return false;
	} else if(operation == 2) {
		if(res - num[pos] <= -INF) 
			return false;
	} else if(operation == 3) {
		if(res + num[pos] >= INF) 
			return false;
	} 
	return true;	
}

ll executeOperation(ll res, ll num, int op) {
	if(op == 0)
		return res/num;
	else if(op == 1)
		return res*num;
	else if(op == 2)
		return res-num;
	else if(op == 3)
		return res+num;
	return -1;
}


bool backtrack(vector<ll>& num, ll res, int pos) {
	if(!visited[pos][INF+res]) visited[pos][INF+res] = true;
	else return false;

	if(pos == p)
		return target_num == res;

	for(int i = 0; i < 4; i++) {
		if(isValidOperation(num,res,pos,i)) {			
			ops.push_back(i);
			if(backtrack(num,executeOperation(res,num[pos],i),pos+1))
				return true;
			ops.pop_back();
		}
	}

	return false;

}

int main() {

	int test; cin >> test;
	while(test--) {
		cin >> p;
		vector<ll> num(p);
		for(int i = 0; i < p; i++)
			cin >> num[i];
		cin >> target_num;
		
		//Solution to slow => find backtrack solution

		visited.assign(105,vector<bool>(2*INF+5));
		ops.clear();

		bool find_equation = backtrack(num,num[0],1);

		if(find_equation) {
			printEquation(num,ops,target_num);
		}
		else
			cout << "NO EXPRESSION" << endl;

	}

}
