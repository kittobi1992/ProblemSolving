#include <bits/stdc++.h>

using namespace std;

class UnionFind {

public:
  UnionFind(int N) {
    uf.assign(N,-1);
  }
  
  int findSet(int i) {
    if(uf[i] < 0) return i;
    uf[i] = findSet(uf[i]);
    return uf[i];
  }
  
  void linkSets(int i, int j) {
    if(abs(uf[i]) < abs(uf[j])) { 
      uf[j] += uf[i]; uf[i] = j; 
    } else {
      uf[i] += uf[j]; uf[j] = i; 
    }
  }
  
  void unionSets(int i, int j) {
    if(findSet(i) != findSet(j)) linkSets(findSet(i),findSet(j));
  } 
  
private:
  vector<int> uf;
};

int main() {
  
  return 0;
}