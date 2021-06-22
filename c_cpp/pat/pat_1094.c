#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define OUT_FAULURE 404
void cleanHc(void)
{
    char c;
    while (1)
    {
        c = getchar();
        if ( c == '\n' || c == '\0')
            break;
    } 
}
int numGet(int numsize,char* nump)
{
    int i;
    char c;
    
    for (i=0; i < numsize; i++)
    {
        c = getchar(); 
        if ( c < '0' || c > '9')
            break;
        *nump++ = c;
    }
    *nump = '\0';
    return 0;
}

int issushu(int num)
{
    int i;
    if (num < 2)
        return -1;
    for (i = 2; i * i <= num ; i++)
    {
        if (num % i == 0)
        {
            return -1;
        }
    }
    return 0;
}
int main(int argc, char* argv[])
{
    char big_num[1000];
    char copy_big[10];
    //int pd_num;
    int bnum_size = 0;
    int constent_bit = 0;
    int i;

    scanf("%d %d",&bnum_size,&constent_bit);
    
   
     cleanHc();
    if (numGet(bnum_size, big_num) != 0)
    {
        exit(EXIT_FAILURE);
    }
    cleanHc();

    for (i = 0; i <= bnum_size - constent_bit ; i++)
    {
        strncpy(copy_big,big_num + i,constent_bit);
        if ( issushu(atoi(copy_big)) == 0)
        {
                printf("%s",copy_big);
                exit(EXIT_SUCCESS);
        }
    }
    
    printf("%d\n",OUT_FAULURE);
    exit(EXIT_SUCCESS);
}