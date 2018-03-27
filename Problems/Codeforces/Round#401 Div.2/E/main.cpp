#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
size_t N;

struct ring {
    ll a,b,h,nsv;
    
    void print() {
        cout << a << " " << b << " " << h << " " << nsv << endl;
    }
};

/**
 * Generic Segment Tree.
 * Construction Time O(n) and Query Time O(log(n)).
 * 
 * @tparam S Type of Sequence which the Segment Tree operates on
 * @tparam T Value Type of a node in the Segment Tree
 * @tparam A Function which compares the left and the right value of the two childs
 *           of a node and returns the value type for this node.
 * @tparam B Funtion which determines the value type for a leaf.
 * 
 */
template<typename S, typename T, 
T (*A)(const T &, const T &, const vector<S> &),
T (*B)(const size_t &, const vector<S> &)>
class SegmentTree {
    
public:
    typedef S seq_type;
    typedef T tree_type;
    
    SegmentTree(vector<seq_type>& seq) : N(seq.size()), seq(seq), seg_tree(4*N) {
        buildSegmentTree(0,0,N-1);
    }
    
    tree_type query(const size_t i, const size_t j) const {
        return query_rec(0,0,N-1,i,j);
    }
    
    void update(const size_t idx, const seq_type val) {
        update_rec(idx,val,0,0,N-1);
    }
    
private:
    
    
    tree_type query_rec(const size_t pos, const size_t cur_i, const size_t cur_j, const size_t qry_i, const size_t qry_j) const {
//         cout << pos << " " << cur_i << " " << cur_j << " " << qry_i << " " << qry_j << endl;
        if(cur_i >= qry_i && cur_j <= qry_j) return seg_tree[pos]; 
        
        size_t m = (cur_i+cur_j)/2;
        
        if(cur_i <= qry_j && m >= qry_i) {
            tree_type m_left = query_rec(2*pos+1,cur_i,m,qry_i,qry_j);
            if(m+1 <= qry_j && cur_j >= qry_i) {
                tree_type m_right = query_rec(2*pos+2,m+1,cur_j,qry_i,qry_j);
                return A(m_left,m_right,seq);
            }
            else return m_left;
        }
        else {
            tree_type m_right = query_rec(2*pos+2,m+1,cur_j,qry_i,qry_j);
            return m_right;
        }
    }
    
    tree_type update_rec(const size_t idx, const seq_type val, const size_t pos, const size_t i, const size_t j) {
//         cout << idx << " " << val << " " << pos << " " << i << " " << j << endl;
        if(i > idx || j < idx) return seg_tree[pos];
        else if(i == j) {
            seq[idx] = val; seg_tree[pos] = B(i,seq);
            return seg_tree[pos];
        }
        
        size_t m = (i+j)/2;
        tree_type m_left = update_rec(idx,val,2*pos+1,i,m);
        tree_type m_right = update_rec(idx,val,2*pos+2,m+1,j);
        seg_tree[pos] = A(m_left,m_right,seq);
        
        return seg_tree[pos];
    }
    
    tree_type buildSegmentTree(const size_t pos, const size_t i, const size_t j) {
        if(i == j) {
            seg_tree[pos] = B(i,seq);
            return seg_tree[pos];
        }
        
        size_t m = (i+j)/2;
        tree_type m_left = buildSegmentTree(2*pos+1,i,m);
        tree_type m_right = buildSegmentTree(2*pos+2,m+1,j);
        seg_tree[pos] = A(m_left,m_right,seq);
        
        return seg_tree[pos];
        
    }
    
    size_t N;
    vector<S>& seq;
    vector<T> seg_tree;
    
};

//############## Range Maximum Query ##############
template<typename S>
size_t max_func(const size_t& i1, const size_t& i2, const vector<S>& seq) {
    return (seq[i1] >= seq[i2] ? i1 : i2);
}

template<typename S>
size_t max_base(const size_t& i, const vector<S>& seq) {
    return i;
}

template<typename S>
using RMQ_Maximum = SegmentTree<S,size_t,max_func<S>,max_base<S>>;


vector<ring> R;

int main() {
    
    cin >> N;
    vector<ring> tmp(N);
    for(int i = 0; i < N; ++i) cin >> tmp[i].a >> tmp[i].b >> tmp[i].h;
    
    sort(tmp.begin(),tmp.end(),[&](const ring& r1, const ring r2) {
        return r1.b > r2.b || (r1.b == r2.b && r1.a > r2.a);
    });
    ring dummy; dummy.a = -1; dummy.b = -1; dummy.h = -1;
    tmp.push_back(dummy);
    
    ring cur = tmp[0];
    for(int i = 1; i < N+1; ++i) {
        if(cur.b != tmp[i].b) {
            R.push_back(cur); cur = tmp[i];
        }
        else {
            cur.a = tmp[i].a; cur.h += tmp[i].h;
        }
    }
    
    N = R.size();
    R[N-1].nsv = N;
    for(int i = N-2; i >= 0; --i) {
        ll a = R[i].a;
        size_t l = i+1, r = N;
        while(r-l > 0) {
            size_t m = (r+l)/2;
            if(R[m].b > a) l = m+1;
            else r = m;
        }
        R[i].nsv = l;
    }
    
    /*for(int i = 0; i < N; ++i) {
        R[i].print();
    }*/
    
    vector<ll> dp(N);
    dp[N-1] = R[N-1].h;
    RMQ_Maximum<ll> rmq(dp);
    for(int i = N-2; i >= 0; --i) {
         if(i+1 == R[i].nsv) dp[i] = R[i].h;
         else dp[i] = R[i].h + dp[rmq.query(i+1,R[i].nsv-1)];
         rmq.update(i,dp[i]);
    }
    
    ll max_h = 0;
    for(int i = 0; i < N; ++i) {
        max_h = max(max_h,dp[i]);
    }
    
    cout << max_h << endl;
    
	return 0;
}
