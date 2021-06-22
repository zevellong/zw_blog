#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char buf[81];
    int len = 0;
    if (scanf("%s", buf) != 1)
    {
        exit(EXIT_FAILURE);
    }
    len = strlen(buf);
    if (len < 5 || len > 80)
        exit(EXIT_FAILURE);
    
    int n1 = len / 3 ;
    if (len % 3 == 0)
        n1--;
    int n2 = len - 2*n1;
    int i;
    char* p;
    char  ch_space[30];
    p = ch_space;
    for (i = 0; i < n2 - 2; i++)
        *p++ = ' ';
    *p = '\0';
    
    p = buf;
    for (i = 0; i < n1; i++)
    {
        //printf("i=%d n1=%d\n",i,n1);        
        printf("%c%s%c\n",*(p+i),ch_space,*(p+len - i - 1));
    }
    strncpy(ch_space,buf+i,n2);
    printf("%s\n",ch_space);
   
    exit(EXIT_SUCCESS);
}


