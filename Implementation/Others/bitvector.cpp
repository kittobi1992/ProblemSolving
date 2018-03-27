#include <bits/stdc++.h>

using namespace std;

//Bit-Vector datastructure
//Supports rank operation in O(1) with an o(n) additional bit datastructure
class bit_vector {
  typedef unsigned long long ll;
  #define DATA_SIZE ((ll)sizeof(ll)*8)
  
public:
  //Bit-Vector for N elements and every element is a K bit number
  bit_vector(size_t N, size_t K) : N(N), K(K), L(ceil(log2(N)*log2(N))), S(ceil(log2(N)/2)) {
    MASK = ~(ULONG_MAX << K);
    bit.assign(ceil(((double)(K*N))/DATA_SIZE)+1,0);
    if(K == 1) {
      sup = new bit_vector(ceil(N/L),ceil(log2(N)));
      sub = new bit_vector(ceil(N/L)*ceil(L/S),ceil(log2(L)));
      lookup.assign(((size_t) pow(2,S)),0);
    }
  }
  
  size_t operator[](size_t i) {
    return extractBits(i*K,K);
  }
  
  size_t set(size_t i, size_t v) {
    size_t pos = (i*K)/DATA_SIZE; size_t bit_pos = (i*K) % DATA_SIZE;
    size_t shift = (bit_pos + K >= DATA_SIZE ? bit_pos + K - DATA_SIZE : 0);
    bit[pos] &= ~(MASK << bit_pos); bit[pos+1] &= ~(MASK >> (K-shift)); // set all bits of index i to 0
    bit[pos] |= v << bit_pos; bit[pos+1] |= v >> (K-shift); // set all bits of index i to v
  }
  
  //Return the amount of '1' in bit_vector bit in range [0,i). Time Complexity O(1)
  size_t rank(size_t i) {
    if(K > 1) return 0;
    size_t sup_idx = floor(i/L), sub_idx = floor(i/L)*ceil(L/S)+floor((i%((size_t)L))/S);
    size_t sup_sub_idx = sup_idx*((size_t) L) + ((i - sup_idx*((size_t) L))/((size_t) S))*S;
    return (*sup)[sup_idx] + (*sub)[sub_idx] +
	     lookup[extractBits(sup_sub_idx,i-(sup_sub_idx))];
  }
  
  //Return the position of the i-th's '1' in bit_vector. Time Complexity O(log(N))
  size_t select(size_t i) {
    if(K > 1) return 0;
    size_t l = 0, r = N;
    while(l < r-1) {
      size_t m = (l+r)/2; size_t rank_m = rank(m);
      if(rank_m < i) l = m; else r = m;
    }
    return l; 
  }
  
  void initRankSupport() {
	if(K > 1)
	  return;
	size_t sum = 0;
	for(size_t i = 0; i < sup->size(); i++) { //Initialize Superblocks and those Subblock.
	  sup->set(i,sum); size_t sum_s = 0;
	  for(size_t k = 1; k <= ceil(L/S); k++) {
	    sub->set(i*ceil(L/S)+(k-1),sum_s);
	    for(size_t j = i*L+(k-1)*S; j < min(i*((size_t) L) + k*((size_t) S),min((i+1)*((size_t)L),N)); j++)
	      sum_s += (*this)[j];
	  }
	  sum += sum_s;
	}
	//Initialize lookup table for every number in range [0,S)
	for(size_t i = 0; i < lookup.size(); i++) {
	    size_t num = 0, count = 0, j = 0;
	    while(i >> j) if((i >> j++) & 1) count++;
	    lookup[i] = count;
	}
  }
  
  size_t size() {
    return N;
  }

private:
  //Returns from position i in bit_vector bit the following k bits. Time Complexity O(1)
  size_t extractBits(size_t i, size_t k) {
    size_t pos = i/DATA_SIZE; size_t bit_pos = i % DATA_SIZE;
    size_t shift = (bit_pos + k >= DATA_SIZE ? bit_pos + k - DATA_SIZE : 0);
    ll MASK_K = ~(ULONG_MAX << k);
    return ((bit[pos] & (MASK_K << bit_pos)) >> bit_pos) | ((bit[pos+1] & (MASK_K >> (k-shift))) << (k-shift));   
  }
  
  vector<ll> bit;
  size_t K, N;
  double L, S;
  ll MASK;
  bit_vector* sup; bit_vector* sub;
  vector<ll> lookup;
};


vector<int> nrank;
vector<int> nselect;

void naive_rank(bit_vector& b) {
  size_t sum = 0;
  nrank.assign(b.size()+1,0);
  for(size_t j = 0; j < b.size(); j++) {
    sum += b[j]; nrank[j+1] = sum;
  }
}
void naive_select(bit_vector& b) {
  size_t sum = 0;
  nselect.push_back(0);
  for(size_t j = 0; j < b.size(); j++) {
    if(b[j] == 1)
      nselect.push_back(j);
  }
}

int main() {
  
  const size_t N = 1000000;
  const size_t K = 1;
  vector<int> v(N);
  bit_vector b(N,K);
  for(int i = 0; i < N; i++)
    v[i] = rand() % ((int)pow(2,K));
  
  for(int i = 0; i < N; i++)
    b.set(i,v[i]);
  
  b.initRankSupport();
  naive_rank(b);
  naive_select(b);

  //Test access operator
  for(size_t i = 0; i < N; i++) {
    if(b[i] != v[i]) {
      cout << "Error: b[" << i << "] = " << b[i] << " !=  v["<<i<<"] = " << v[i] << endl;
      return 0;
    }
  }
 
  //Test rank operation
  for(int i = 0; i <= N; i++) {
    if((K == 1 ? nrank[i] : 0) != b.rank(i)) {
      cout << "Error: Rank(" << i << ") != " << b.rank(i) << endl;
      return 0;
    }
  }
  
  //Test select operation
  for(int i = 1; i < nselect.size(); i++) {
    size_t select = b.select(i);
    if((K == 1 ? nselect[i] : 0) != select && b[select] == 1) {
      cout << "Error: Select(" << i << ") != " << b.select(i) << endl;
      return 0;
    }
  }
 
  cout << "Accepted!" << endl;
  
    
  
  return 0;
}