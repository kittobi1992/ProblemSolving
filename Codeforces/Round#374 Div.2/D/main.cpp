#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n,k,x;

vector<ll> a;
vector<ll> sign;
int zero = 0;
int res = 0;

class RMQ {
public:
    RMQ() : rmq(4*n,-1) {
        int m_idx = buildRMQ(0,0,n-1);
        a.push_back(LLONG_MAX);
        sign.push_back(1);
    }
    
    int queryRMQ(int i, int j) {
        return rmq_recursive(0,i,j,0,n-1);
    }

    void update(int i, ll val, ll sig) {
        a[i] = val;
        sign[i] = sig;
        update_recursive(i,0,0,n-1);
    }
    
private:
    
    int update_recursive(int i, int pos, int cur_i, int cur_j) {
        if(cur_i > cur_j) return n;
        if(cur_i == i && cur_j == i) {
            return rmq[pos];
        }
        
        if(i >= cur_i && i <= cur_j) {
            int m = (cur_i+cur_j)/2;
            int m_left = update_recursive(i,2*pos+1,cur_i,m);
            int m_right = update_recursive(i,2*pos+2,m+1,cur_j);
            rmq[pos] = (a[m_left] <= a[m_right] ? m_left : m_right);
            return rmq[pos];
        }
        else
            return rmq[pos];
    }
    
    int rmq_recursive(int pos, int i, int j, int cur_i, int cur_j) {
        if(cur_i > cur_j) return n;
        if(cur_i > j || cur_j < i) return n;
        if(i <= cur_i && j >= cur_j) {
            return rmq[pos];
        }
        
        int m = (cur_i+cur_j)/2;
        int m_left = rmq_recursive(2*pos+1,i,j,cur_i,m);
        int m_right = rmq_recursive(2*pos+2,i,j,m+1,cur_j);
        
        return (a[m_left] <= a[m_right] ? m_left : m_right);
    }
    
    int buildRMQ(int pos, int i, int j) {
        if(i == j) {
            rmq[pos] = i;
            return i;
        }
        
        int m = (i+j)/2;
        int m_left = buildRMQ(2*pos+1,i,m);
        int m_right = buildRMQ(2*pos+2,m+1,j);
        rmq[pos] = (a[m_left] <= a[m_right] ? m_left : m_right);
        return rmq[pos];
    }
    
    vector<int> rmq;

};

int main() {
  
    cin >> n >> k >> x;
    a.resize(n); sign.resize(n);
    int negative = 0;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        if(res == 0 && a[i] > 0) res = 1;
        else if(res == 0 && a[i] < 0) res = -1;
        else if(a[i] == 0) zero++;
        else {
            int mul = (a[i] > 0 ? 1 : -1);
            res *= mul;
        }
        if(a[i] < 0) sign[i] = -1;
        else sign[i] = 1;
        if(sign[i] < 0) negative++;
        a[i] = abs(a[i]);
    }
    
    if(k >= zero) {
        if(negative % 2 == 0) {
            bool first = false;
            for(int i = 0; i < n; ++i) {
                if(a[i] == 0 && !first) {
                    a[i] = x;
                    sign[i] = -1;
                    res = -1;
                    first = true;
                }
                else if(a[i] == 0) {
                    a[i] = x;
                    sign[i] = 1;
                }
            }
        }
        else {
            for(int i = 0; i < n; ++i) {
                if(a[i] == 0) {
                    a[i] = x;
                    sign[i] = 1;
                }
            } 
        }
        
        RMQ rmq;
        
        for(int i = 0; i < k-zero; ++i) {
            int min_idx = rmq.queryRMQ(0,n-1);
            ll val = sign[min_idx]*a[min_idx];
            if(val < 0) {
                if(res > 0) {
                    val += x;
                    if(val > 0) res = -1;
                }
                else {
                    val -= x;
                }
                rmq.update(min_idx,abs(val),(val <= 0 ? -1 : 1));
            }
            else {
                if(res > 0) {
                    if(sign[min_idx] == -1) {
                        val += x;
                        if(val > 0) res = -1;
                    }
                    else {
                        val -= x;
                        if(val < 0) res = -1;  
                    }
                }
                else {
                    val += x;
                }
                rmq.update(min_idx,abs(val),(val >= 0 ? 1 : -1));
            }
        }
        
        a.pop_back();
        
    }
    
    for(int i = 0; i < a.size(); ++i) {
        cout << (sign[i]*a[i]) << (i == a.size()-1 ? "\n" : " ");
    }
    
    
	return 0;
}
