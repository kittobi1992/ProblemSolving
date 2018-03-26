#include <iostream>
#include <string.h>
#include <climits>
#include <cmath>

using namespace std;

#define SIZE 250000
#define LOG_SIZE 22

#define UNIVERSE 1000000
#define DEBUG true

int a[SIZE];
int rmq[LOG_SIZE][SIZE];

/**
 * Build RMQ data structure.
 * rmq[i][j] stores index of the minimum value in 
 * interval [j..j+2^i) of array a.
 * => Preprocessing time and space consumption in O(n*log(n))
 */
void buildRMQ(int n) {
  memset(rmq, 0, sizeof(rmq[0][0]) * SIZE * LOG_SIZE);

  for (int i = 0; i < n; ++i)
    rmq[0][i] = i;

  int L = log2(n) + 1;
  for (int i = 1; i < L; ++i) {
    int size = 1 << i;
    for (int j = 0; j+size < n; ++j) {
      rmq[i][j] = (a[rmq[i-1][j]] <= a[rmq[i-1][j+size/2]]) ? rmq[i-1][j] : rmq[i-1][j+size/2];
    }
  }
}

/**
 * Return index with minimum value of array a in interval [l,r].
 * Time Complexity: O(1)
 */
int query(int l, int r) {
  int k = log2(r-l+1);
  int size = 1 << k;
  return (a[rmq[k][l]] <= a[rmq[k][r-size+1]]) ? rmq[k][l] : rmq[k][r-size+1];
}

/**
 * Returns index with minimum value of array a in interval [l,r].
 * NOTE: Only used, if DEBUG flag is true.
 */
int linearScan(int l, int r) {
  int idx = -1;
  int min_v = INT_MAX;
  for (int k = l; k <= r; k++) {
    if (min_v > a[k]) {
      min_v = a[k];
      idx = k;
    }
  }
  return idx;
}

int main() {
  // Generate test sequence
  memset(a, 0, sizeof(a));
  for (int i = 0; i < SIZE; i++)
    a[i] = rand() % UNIVERSE;

  // Build RMQ data structure
  buildRMQ(SIZE);

  // Generate q queries to test implementation
  int q = 10000;
  for (int i = 0; i < q; i++) {
    int l = rand() % SIZE;
    int r = rand() % SIZE;
    int rmq_i = query(min(l, r), max(l, r));

    // Compare result of rmq call against linear scan test implementation
    if (DEBUG) {
      int linear_i = linearScan(min(l, r), max(l, r));
      if (rmq_i != linear_i) {
        cout << "Searching for minimum in intervall [" << min(l, r) << "," << max(l, r) << "]" << endl;
        cout << "RMQ query = [Index: " << rmq_i << ", Value: " << a[rmq_i] << "]" << endl;
        cout << "Linear query = [Index: " << linear_i << ", Value: " << a[linear_i] << "]" << endl;
        cout << "RMQ computation failed!" << endl;
        return -1;
      }
    }
  }

  if (DEBUG) {
    cout << "All queries returned correct minimum!" << endl;
  }

  return 0;
}
