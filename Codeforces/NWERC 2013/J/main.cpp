 #include <bits/stdc++.h>

using namespace std;

#define INVALID INT_MAX/3

struct node {
    int id;
    int t, b;
    node *left, *right;
    
    node(int id) : id(id), left(nullptr), right(nullptr) {}
    
    bool is_leaf() {
        return !(left && right);
    }
    
    
    void printNode(int d) {
        for(int i = 0; i < d; ++i) cout << " ";
        cout << "ID: " << id << ", Twiggs: " << t << ", Balls: " << b << endl; 
    }
    
};

string bp; int pos; int id;
node * root;

void printTree(node *cur, int d) {
    if(cur) {
        cur->printNode(d);
        printTree(cur->left,d+1);
        printTree(cur->right,d+1);
    }
}

node * buildTree() {
    node * n = new node(id++);
    if(bp[pos] == 'B') {
        n->t = 1; n->b = 1; pos += 2; return n;
    } else if(bp[pos] == ')') {
        n->t = 1; n->b = 0; pos++; return n;
    }
    
    if(bp[pos++] == '(') n->left = buildTree();
    if(bp[pos++] == '(') n->right = buildTree();
    
    n->t = n->left->t + n->right->t;
    n->b = n->left->b + n->right->b;
    pos++;
    
    
    return n;
}



int dfs(node *cur, int N) {
    if(cur->is_leaf()) { 
        if(N > 1) return INVALID;
        return cur->b == 1 && N == 0;
    }
    
    if(N % 2 == 0) {
        int res1 = dfs(cur->left,N/2), res2 = dfs(cur->right,N/2);
        if(res1+res2 >= INVALID) return INVALID;
        return res1 + res2;
    }
    else {
        int res1 = dfs(cur->left,N/2), res2 = dfs(cur->right,N/2+1);
        int res3 = dfs(cur->left,N/2+1), res4 = dfs(cur->right,N/2);
        if(res1 + res2 >= INVALID && res3 + res4 >= INVALID) return INVALID;
        return min(res1+res2,res3+res4);
    }
    
}

int main() {
     
    while(cin >> bp) {
        pos = 1; id = 0;
        root = buildTree();
        
        //printTree(root,0);
        
        int res = dfs(root, root->b);
        
        if(res >= INVALID) cout << "impossible" << endl;
        else cout << res << endl;
    }
    
	return 0;
}
