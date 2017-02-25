#include <bits/stdc++.h>

using namespace std;

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
        if(i > idx || j < idx) return seg_tree[pos];
        else if(i == j) {
            seq[idx] = val; seq_tree[pos] = B(i,seq);
            return seq_tree[pos];
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


//############## Range Minimum Query ##############
template<typename S>
size_t min_func(const size_t& i1, const size_t& i2, const vector<S>& seq) {
    return (seq[i1] <= seq[i2] ? i1 : i2);
}

template<typename S>
size_t min_base(const size_t& i, const vector<S>& seq) {
    return i;
}

//Naive Range Minimum Query
template<typename S>
size_t naive_min(const size_t& i, const size_t& j, vector<S>& seq) {
    size_t min_idx = i;
    for(size_t t = i+1; t <= j; ++t) {
        if(seq[t] < seq[min_idx]) min_idx = t;
    }
    return min_idx;
}

template<typename S>
using RMQ_Minimum = SegmentTree<S,size_t,min_func<S>,min_base<S>>;

//##########################################


//############## Range Maximum Query ##############
template<typename S>
size_t max_func(const size_t& i1, const size_t& i2, const vector<S>& seq) {
    return (seq[i1] >= seq[i2] ? i1 : i2);
}

template<typename S>
size_t max_base(const size_t& i, const vector<S>& seq) {
    return i;
}

//Naive Range Maximum Query
template<typename S>
size_t naive_max(const size_t& i, const size_t& j, vector<S>& seq) {
    size_t max_idx = i;
    for(size_t t = i+1; t <= j; ++t) {
        if(seq[t] > seq[max_idx]) max_idx = t;
    }
    return max_idx;
}

template<typename S>
using RMQ_Maximum = SegmentTree<S,size_t,max_func<S>,max_base<S>>;

//##########################################


//############## Range Minmax Query ##############
template<typename S>
std::pair<size_t,size_t> minmax_func(const std::pair<size_t,size_t>& i1, const std::pair<size_t,size_t>& i2, const vector<S>& seq) {
    size_t min_i1 = i1.first, min_i2 = i2.first;
    size_t max_i1 = i1.second, max_i2 = i2.second;
    size_t min_i = (seq[min_i1] <= seq[min_i2] ? min_i1 : min_i2);
    size_t max_i = (seq[max_i1] >= seq[max_i2] ? max_i1 : max_i2);
    return std::make_pair(min_i,max_i);
}

template<typename S>
std::pair<size_t,size_t> minmax_base(const size_t& i, const vector<S>& seq) {
    return std::make_pair(i,i);
}

//Naive Range Maximum Query
template<typename S>
std::pair<size_t,size_t> naive_minmax(const size_t& i, const size_t& j, vector<S>& seq) {
    size_t min_idx = i;
    size_t max_idx = i;
    for(size_t t = i+1; t <= j; ++t) {
        if(seq[t] < seq[min_idx]) min_idx = t;
        if(seq[t] > seq[max_idx]) max_idx = t;
    }
    return std::make_pair(min_idx,max_idx);
}

//Overload operator for output in check_query_result
template<typename S>
std::ostream& operator<<(std::ostream& out, const std::pair<S,S>& rhs )
{
    out << "[" << rhs.first << "," << rhs.second << "]";
    return out;
}

template<typename S>
using Minmax_Tree = SegmentTree<S,std::pair<size_t,size_t>,minmax_func<S>,minmax_base<S>>;

//##########################################



//############## Interval Sum ##############
template<typename S>
S sum_func(const S& i1, const S& i2, const vector<S>& seq) {
    return i1+i2;
}

template<typename S>
S sum_base(const size_t& i, const vector<S>& seq) {
    return seq[i];
}

//Naive Range Maximum Query
template<typename S>
S naive_sum(const size_t& i, const size_t& j, vector<S>& seq) {
    int sum = 0;
    for(size_t t = i; t <= j; ++t) {
        sum += seq[t];
    }
    return sum;
}

template<typename S>
using Interval_Sum = SegmentTree<S,S,sum_func<S>,sum_base<S>>;

//##########################################


//############## Interval Product ##############
template<typename S>
S product_func(const S& i1, const S& i2, const vector<S>& seq) {
    return i1*i2;
}

template<typename S>
S product_base(const size_t& i, const vector<S>& seq) {
    return seq[i];
}

//Naive Range Maximum Query
template<typename S>
S naive_product(const size_t& i, const size_t& j, vector<S>& seq) {
    int product = seq[i];
    for(size_t t = i+1; t <= j; ++t) {
        product *= seq[t];
    }
    return product;
}

template<typename S>
using Interval_Product = SegmentTree<S,S,product_func<S>,product_base<S>>;

//##########################################


//Checks Segment Query Results against naive implementation
template<typename seq_type, typename tree_type, typename SegTree, 
         tree_type (*naive)(const size_t &, const size_t &, vector<seq_type>& seq)> 
void check_query_result(size_t N, SegTree seg_tree, vector<seq_type>& seq) {
    size_t cnt = 1;
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = i; j < N; ++j) {
            cout << "Query #" << cnt++ << endl;
            tree_type seg_tree_query = seg_tree.query(i,j);
            tree_type naive_query = naive(i,j,seq);
            cout << "SegmentTree-Query [" << i << "," << j << "] = " << seg_tree_query << endl; 
            cout << "Naive-Query [" << i << "," << j << "] = " << naive_query << endl; 
            cout << "----------------------------" << endl;
            if(seg_tree_query != naive_query) abort();
        }
    }
    cout << endl;
}

int main() {
  
    int N; cin >> N;
    vector<int> seq(N);
    for(size_t i = 0; i < N; ++i) cin >> seq[i];
    
    //Range Minimum Query
    {
        RMQ_Minimum<int> rmq(seq);
        check_query_result<int,size_t,RMQ_Minimum<int>,naive_min<int>>(N,rmq,seq);
    }
    
    //Range Maximum Query
    {
        RMQ_Maximum<int> rmq(seq);
        check_query_result<int,size_t,RMQ_Maximum<int>,naive_max<int>>(N,rmq,seq);
    }
    
    //Range Minmax Query
    {
        Minmax_Tree<int> rmq(seq);
        check_query_result<int,std::pair<size_t,size_t>,Minmax_Tree<int>,naive_minmax<int>>(N,rmq,seq);
    }
    
    //Interval Sum
    {
        Interval_Sum<int> ival_sum(seq);
        check_query_result<int,int,Interval_Sum<int>,naive_sum<int>>(N,ival_sum,seq);
    }
    
    //Interval Product
    {
        Interval_Product<int> ival_product(seq);
        check_query_result<int,int,Interval_Product<int>,naive_product<int>>(N,ival_product,seq);
    }
    
	return 0;
}
