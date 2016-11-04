#define F first
#define S second

#include <bits/stdc++.h>
using namespace std;

pair<pair<int,int>, int> inp[100010];
int fen[1000010];
int res[100010];

void update(int val, int idx)
{
    while(idx <= 1000000)
    {
        fen[idx] = max(fen[idx], val);
        idx += (idx & -idx);
    }
}

int query(int idx)
{
    int val = 0;
    
    while(idx > 0)
    {
        val = max(fen[idx], val);
        idx -= (idx & -idx);
    }
    
    return val;
}

int main()
{
    int n, i, curmaxS = 0, cur = 0;
    
    freopen("codecoder.in", "r", stdin);
    freopen("codecoder.out", "w", stdout);
    
    scanf("%d", &n);
    
    for(i = 0; i < n; i++)
    {
        scanf("%d%d", &inp[i].F.F, &inp[i].F.S);
        fen[inp[i].F.S] = inp[i].F.F;
        inp[i].S = i;
    }
    
    for(i = 1; i <= 1000000; i++)
    {
        fen[i] = max(fen[i], fen[i - 1]);
    }
    
    sort(inp, inp + n);
    
    for(i = 0; i < n; i++)
    {
        curmaxS = max(curmaxS, inp[i].F.S);
        cur = max(cur, i);
        
        while(inp[cur + 1].F.F <= fen[curmaxS] && cur < n - 1)
        {
            cur++;
            curmaxS = max(curmaxS, inp[cur].F.S);
        }
        
        res[inp[i].S] = cur;
    }
    
    for(i = 0; i < n; i++)
    {
        printf("%d\n", res[i]);
    }
    
    return 0;
}
