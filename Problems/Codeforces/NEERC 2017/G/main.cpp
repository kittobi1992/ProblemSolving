#define PB push_back
#define SZ size()

#include <bits/stdc++.h>

using namespace std;

int tcnt = 1;

struct node
{
    int P[17];
    vector<int> C;
    int s, e;
};

node V[100010];
int blocked[200010];

void dfs(int c)
{
    V[c].s = tcnt;
    tcnt++;
    
    for(int i = 0; i < V[c].C.SZ; i++)
    {
        dfs(V[c].C[i]);
    }
    
    V[c].e = tcnt;
    tcnt++;
}

void update(int *T, int val, int idx)
{
    while(idx <= 1000000)
    {
        T[idx] = max(T[idx], val);
        idx += (idx & -idx);
    }
}

int query(int *T, int idx)
{
    int val = 0;
    
    while(idx > 0)
    {
        val = max(T[idx], val);
        idx -= (idx & -idx);
    }
    
    return val;
}

int main()
{
    int n, q, i, j, x;
    char cmd[5];
    
    freopen("gangsters.in", "r", stdin);
    freopen("gangsters.out", "w", stdout);
    
    scanf("%d%d", &n, &q);
    
    for(i = 0; i < 17; i++)
    {
        V[1].P[i] = 0;
    }
    
    for(i = 2; i <= n; i++)
    {
        scanf("%d", &V[i].P[0]);
        V[V[i].P[0]].C.PB(i);
    }
    
    for(i = 2; i <= n; i++)
    {
        if(V[i].C.SZ == 1)
        {
            V[V[i].C[0]].P[0] = V[i].P[0];
            V[i].P[0] = 0;
        }
    }
    
    for(i = 1; i <= n; i++)
    {
        V[i].C.clear();
    }
    
    for(i = 2; i <= n; i++) 
    {
        V[V[i].P[0]].C.PB(i);
    }
    
    for(j = 1; j < 17; j++)
    {
        for(i = 2; i <= n; i++)
        {
            V[i].P[j] = V[V[i].P[j - 1]].P[j - 1];
        }
    }
    
    dfs(1);
    
    for(i = 0; i < q; i++)
    {
        scanf("%s%d", cmd, &x);
        
        if(*cmd == '+')
        {
            if(query(blocked, V[x].s) == 0)
            {
                
            }
        } else {
            
        }
    }
    
    return 0;
}
