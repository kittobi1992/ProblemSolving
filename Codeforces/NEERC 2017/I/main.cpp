#define ll long long int

#include <bits/stdc++.h>

using namespace std;

int x[200010], y[200010];
int a[200010];

int main()
{
    int n, i;
    
    freopen("integral.in", "r", stdin);
    freopen("integral.out", "w", stdout);
    
    scanf("%d", &n);
    
    for(i = 0; i < n; i++)
    {
        scanf("%d%d", x + i, y + i);
    }
    
    x[n] = x[0];
    y[n] = y[0];
    
    for(i = 0; i < n; i++)
    {
        if((abs(x[i] - x[i + 1]) % 2 == 1) && (abs(y[i] + y[i + 1]) % 2 == 1))
        {
            a[i] = 1;
        } else {
            a[i] = 0;
        }
    }
    
    ll res = 0LL;
    int ee = 0, eo = 0, oe = 0, oo = 0, o = 0, e = 0;
    
    for(i = 1; i < n - 1; i++)
    {
        a[i] += a[i - 1];
        a[i] %= 2;
        
        if(i % 2 == 0)
        {
            if(a[i] == 1)
            {
                oe++;
            } else {
                ee++;
            }
            
            e++;
        } else {
            if(a[i] == 1)
            {
                oo++;
            } else {
                eo++;
            }
            
            o++;
        }
    }
    
    for(i = 0; i < n - 1; i++)
    {
        if((i + 1) % 2 == 0)
        {
            if(a[i + 1] == 1)
            {
                oe--;
            } else {
                ee--;
            }
            
            e--;
        } else {
            if(a[i + 1] == 1)
            {
                oo--;
            } else {
                eo--;
            }
            
            o--;
        }
        
        if(i % 2 == 0)
        {
            if(a[i] == 0)
            {
                res += (ll)e + (ll)oe;
            } else {
                res += (ll)e + (ll)ee;
            }
        } else {
            if(a[i] == 0)
            {
                res += (ll)e + (ll)oo;
            } else {
                res += (ll)e + (ll)eo;
            }
        }
        
        if((n - 1) % 2 == 0)
        {
            if(a[n - 1] == 1)
            {
                oe++;
            } else {
                ee++;
            }
            
            e++;
        } else {
            if(a[n - 1] == 1)
            {
                oo++;
            } else {
                eo++;
            }
            
            o++;
        }
    }
    
    printf("%I64d\n", res);
    
    return 0;
}
