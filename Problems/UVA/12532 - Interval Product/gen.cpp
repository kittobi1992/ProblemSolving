#include <bits/stdc++.h>

using namespace std;

int generateValue() {
    int tmp = rand() % 100 + 1;
    int negative = rand() % 2;
    if(negative)
      tmp *= -1;
    return tmp;
}

int main() {
  
  int n = 100000;
  int k = 100000;
  cout << n << " " << k << endl;
  for(int i = 0; i < n; i++) {
    cout << generateValue() << " ";
  }
  
  for(int i = 0; i < k; ++i) {
    int command = rand() % 2;
    if(command) {
      //Change command
      cout << "C " << (rand() % n) << " " << generateValue() << endl;
    }
    else {
      int i1 = rand() % n, i2 = rand() % n;
      if(i1 > i2) swap(i1,i2);
      cout << "P " << i1 << " " << i2 << endl;
    }
  }
  
  
  return 0;
}
