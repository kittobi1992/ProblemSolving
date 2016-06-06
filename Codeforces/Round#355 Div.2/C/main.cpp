#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007

typedef unsigned long long ll;

map<char, int> m;
vector<int> zero(64);

void createMap() {
  m['0'] = 0; m['1'] = 1; m['2'] = 2; m['3'] = 3; m['4'] = 4; m['5'] = 5; m['6'] = 6; m['7'] = 7; m['8'] = 8; m['9'] = 9;
  m['A'] = 10; m['B'] = 11; m['C'] = 12; m['D'] = 13; m['E'] = 14; m['F'] = 15; m['G'] = 16; m['H'] = 17; m['I'] = 18; m['J'] = 19;
  m['K'] = 20; m['L'] = 21; m['M'] = 22; m['N'] = 23; m['O'] = 24; m['P'] = 25; m['Q'] = 26; m['R'] = 27; m['S'] = 28; m['T'] = 29;
  m['U'] = 30; m['V'] = 31; m['W'] = 32; m['X'] = 33; m['Y'] = 34; m['Z'] = 35;
  m['a'] = 36; m['b'] = 37; m['c'] = 38; m['d'] = 39; m['e'] = 40; m['f'] = 41; m['g'] = 42; m['h'] = 43; m['i'] = 44; m['j'] = 45;
  m['k'] = 46; m['l'] = 47; m['m'] = 48; m['n'] = 49; m['o'] = 50; m['p'] = 51; m['q'] = 52; m['r'] = 53; m['s'] = 54; m['t'] = 55;
  m['u'] = 56; m['v'] = 57; m['w'] = 58; m['x'] = 59; m['y'] = 60; m['z'] = 61;
  m['-'] = 62; m['_'] = 63;
}

ll magic_f(ll i) {
  if(i == 0)
    return 1;
  return 2*magic_f(i-1) + magic_f(i-1);
}

bitset<8> in;

void increment () {
    for ( size_t i = 0; i < 8; ++i ) {
        if ( in[i] == 0 ) {  
            in[i] = 1;
            break;
            }
        in[i] = 0;  
     }
}

int main() {
  
  createMap();
  for(; in.to_ulong() < 64; increment()) {
    zero[in.to_ulong()] = 6 - in.count();
  }
  
  string s; cin >> s;
  ll res = 1;
  for(int i = 0; i < s.size(); ++i) {
    ll possibilities = magic_f(zero[m[s[i]]]);
    res = (res*possibilities) % MOD;
  }
  
  cout << res << endl;
  
  return 0;
}
