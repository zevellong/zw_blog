#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIR_SZIE 10001


int main(int argc,char* argv[])
{
    int dir[128];
    int i,j;
    char s1[DIR_SZIE], s2[DIR_SZIE];
    char c;
    gets(s1);
    gets(s2);
    int len2 = strlen(s2);

    for (i =0; i < 128; i++)
        dir[i] = 0;
    for (i = 0; i< len2;i++)
    {
        dir[(*(s2+i))] = 1;
    }
    
    for (i=0,j=0;i<strlen(s1);i++)
    {
        c = *(s1+i);
        if (dir[c] == 0)
        {
            s2[j] = c;
            j++;
        }
    }
    s2[j] = '\0';
    printf("%s\n",s2);
    exit(EXIT_SUCCESS);
}


