#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int gr()
{
    return rand() % 256;
}

int getmax(int d)
{
    if(d == 0)
    {
        return gr();
    }
    
    return max(getmax(d - 1), getmax(d - 1));
}

int main()
{
    int c = 0;
    
    for(int i = 0; i < 100000; i++)
    {
        int x = getmax(11);
        int y = getmax(11);
        int z = getmax(11);
            
        if(z == 0)
        {
            continue;
        }
        
        if(max(x, y) / z == 1)
        {
            c++;
        }
    }
    
    printf("%d\n", c);
}
