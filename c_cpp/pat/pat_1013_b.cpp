#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>
static int buf[1500];
bool issu(int n)
{
    int cut = sqrt(n);
    for (int i=2; i <= cut; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
int main()
{
    int i=0, j=1;
    buf[0] = 2;
    int st, ed;
    std::cin >> st >> ed;
    for (i=3; i < 10000; i++)
    {
        if (issu(i))
            buf[j++] = i;
    }
    
    for (i = st - 1,j = 0; i < ed; i++)
    {
        j++;
        if (j == 10)
        {
            printf("%d\n", buf[i]);
            j = 0;
        }else
        {
            printf("%d ", buf[i]);
        }
    }
    return 0;
}