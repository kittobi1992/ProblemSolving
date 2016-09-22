 #include <bits/stdc++.h>

using namespace std;


struct node {
    int id;
    int t, b, u;
    node *left, *right;
    
    node(int id) : id(id), u(0), left(nullptr), right(nullptr) {}
    
    bool is_leaf() {
        return !(left && right);
    }
    
    int balls() {
        return b + u;
    }
    
    void printNode(int d) {
        for(int i = 0; i < d; ++i) cout << " ";
        cout << "ID: " << id << ", Twiggs: " << t << ", Balls: " << b << ", Add/Remove: " << u << endl; 
    }
    
};

string bp; int pos; int id;
node * root;
int res;

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


void applyBallChange(node *left, node *right, int u) {
    int tmp_u = u;
    int b1 = left->b;
    int b2 = right->b;
    int N = abs(b1-b2);
    while(tmp_u != 0) {
        if(tmp_u < 0) {
            if(b1 > b2) { b1 += max(-N,tmp_u); u += min(N,-tmp_u); }
            else if(b2 < b1) { b2 += max(-N,tmp_u); tmp_u += min(N,-tmp_u); }
            else { b1 += tmp_u/2 - (tmp_u % 2 == 1); b2 += tmp_u/2; tmp_u = 0; }
        } else if(tmp_u > 0) {
            if(b1 < b2) { b1 += min(N,tmp_u); u -= min(N,tmp_u); }
            else if(b1 > b2) { b2 += min(N,tmp_u); u -= min(N,tmp_u); }
            else { b1 -= tmp_u/2 + (tmp_u % 2 == 1); b2 -= tmp_u/2; tmp_u = 0;  }
        }
    }
    left->b = b1;
    right->b = b2;
}

void dfs(node *cur) {
    if(cur->is_leaf()) return;
    
    applyBallChange(cur->left,cur->right,cur->u);
    cur->printNode(0);
    cur->left->printNode(2);
    cur->right->printNode(2);
    int b = cur->b;
    int t1 = cur->left->t, b1 = cur->left->b, f1 = t1-b1;
    int t2 = cur->right->t, b2 = cur->right->b, f2 = t2-b2;
    int N = abs(b1-b2);
    
    if(N > 1) {
        int u_tmp = N/2;
        if(b1 > b2) {
            if(f2 < u_tmp) { res = -1; return; }
            cur->left->u = -u_tmp;
            cur->right->u = u_tmp;
            res += u_tmp;
        } else {
            if(f1 < u_tmp) { res = -1; return; }
            cur->left->u = u_tmp;
            cur->right->u = -u_tmp;
            res += u_tmp;
        }
    }
    
    dfs(cur->left);
    if(res == -1) return;
    dfs(cur->right);
    if(res == -1) return;
}

int main() {
     
    while(cin >> bp) {
        pos = 1; id = 0; res = 0;
        root = buildTree();
        
        printTree(root,0);
        cout << "----------------" << endl;
        
        dfs(root);
        
        if(res >= 0) cout << res << endl;
        else cout << "impossible" << endl;
    }
    
	return 0;
}
