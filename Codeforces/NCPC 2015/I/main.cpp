#include <bits/stdc++.h>

using namespace std;


int main() {
    int n, i;
    double res = (double)2 * sqrt(500.0), t, g, r, curvel = 1.0;
    
    scanf("%d", &n);
    
    for(i = 1; i < n; i++)
    {
        if(isGreen(res, t, g, r) == 1)
        {
            res += sqrt(curvel) + sqrt(curvel + 2000)
        }
    }
    
    return 0;
}
