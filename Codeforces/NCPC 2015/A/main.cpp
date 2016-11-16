#define PB push_back

#include <bits/stdc++.h>

using namespace std;

struct node
{
    vector<int> C;
    int d1, d2;
    bool v1, v2;
};

node V[100010];
vector<int> store;
int optLen, optNode;

bool cmp(const int &a, const int &b)
{
    return a > b;
}

void dfs1(int c, int d)
{
    if(V[c].v1 == 1)
    {
        return;
    }
    
    V[c].v1 = 1;
    
    if(optLen < d)
    {
        optLen = d;
        optNode = c;
    }
    
    V[c].d1 = d;
    
    for(int i = 0; i < V[c].C.size(); i++)
    {
        dfs1(V[c].C[i], d + 1);
    }
}

void dfs2(int c, int d)
{
    if(V[c].v2 == 1)
    {
        return;
    }
    
    V[c].v2 = 1;
    
    if(optLen < d)
    {
        optLen = d;
        optNode = c;
    }
    
    V[c].d2 = d;
    
    for(int i = 0; i < V[c].C.size(); i++)
    {
        dfs2(V[c].C[i], d + 1);
    }
}

int main() {
//     freopen("f.in", "r",stdin);
//     freopen("f.out", "w",stdout);
    
    int n, l, res = 0;
    cin >> n >> l;
        
    for(int i = 0; i < l; i++){
        int x, y;
        cin >> x >> y;
        V[x].C.PB(y);
        V[y].C.PB(x);
    }
        
    for(int i = 0; i < n; i++){
        if(V[i].v1) continue;
        
        optLen = 0;
        optNode = i;
        dfs1(i, 0);
        
        optLen = 0;
        dfs2(optNode, 0);
        
        store.push_back((optLen + 1) / 2);
        res = max(res, optLen);
    }
    
    sort(store.begin(), store.end(), cmp);
    
    if(store.size() >= 1)
    {
        res = max(store[0], res);
    }
    
    if(store.size() >= 2)
    {
        res = max(store[0] + store[1] + 1, res);
    }
    
    if(store.size() >= 3)
    {
        res = max(store[2] + store[1] + 2, res);
    }
    
    printf("%d", res);
    
    return 0;
}
