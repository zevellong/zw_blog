#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int a,b,i,j,cmp;
    char buf[9] = "0,000,000";

    if (scanf("%d %d",&a,&b) != 2)
        exit(EXIT_FAILURE);
    int sum = a + b;
    if (sum < 0)
    {
        printf("-");
        sum = -sum;
    }
    else if (sum == 0)
    {
        printf("0\n");
        exit(EXIT_SUCCESS);
    }
    for (i=8,j=0,cmp=sum; cmp > 0; i--)
    {
        if ( j == 3)
        {
            buf[i] = ',';
            j = 0;
        }
            
        else
        {
            buf[i] = '0' + cmp % 10;
            cmp /= 10;
            j++;
        }
        //printf("%s\n",buf);
    }
    printf("%s\n",buf + i + 1);
    return 0;
}
