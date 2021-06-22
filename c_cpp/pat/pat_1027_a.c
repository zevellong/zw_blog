#include <stdio.h>
#include <stdlib.h>


char trans(int a)
{
    if (a >= 0 && a <10)
        return ('0' + a);
    else
    {
        return ('A' + a - 10);
    }
    
}
int main(int argc, char* argv[])
{
    int RGB[3];
    int i,j,cmp;
    char output[8] ="#000000";
    if (scanf("%d %d %d", RGB, RGB + 1, RGB + 2) != 3)
        exit(EXIT_FAILURE);
   
   for (j=1,i=0; i < 3; i++)
   {
       cmp = RGB[i];
        output[j++] = trans(cmp / 13);
        output[j++] = trans(cmp % 13);
       
   }
    printf("%s\n", output);
    return 0;
}