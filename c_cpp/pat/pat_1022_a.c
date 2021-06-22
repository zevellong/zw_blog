#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _NOT_FOUND_ "Not Found\n"

typedef struct {
    int ID;
    char tilte[81];
    char author[81];
    char keyword[81];
    char publisher[81];
    int rep_year;

} bookInfo;

int main(int argc, char* argv[])
{
    int i,j,bookNum,findNum;
    char buf[96];
    if (scanf("%d",&bookNum) != 1)
    {
        exit(EXIT_FAILURE);
    }
    bookInfo* bp = (bookInfo*) malloc(sizeof(bookInfo) * bookNum);
    if (bp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while (getchar()!='\n') continue;
    for (j = 0; j < bookNum; j++)
    {
        if (fgets(buf,82,stdin) == NULL)
            exit(EXIT_FAILURE);
        bp[j].ID = atoi(buf);

        if (fgets(bp[j].tilte,82,stdin) == NULL)
            exit(EXIT_FAILURE);

        if (fgets(bp[j].author,82,stdin) == NULL)
            exit(EXIT_FAILURE);

        if (fgets(bp[j].keyword,82,stdin) == NULL)
            exit(EXIT_FAILURE);
        
        if (fgets(bp[j].publisher,82,stdin) == NULL)
            exit(EXIT_FAILURE);

        if (fgets(buf,82,stdin) == NULL)
            exit(EXIT_FAILURE);
        bp[j].rep_year = atoi(buf);
    }

    if (scanf("%d",&findNum) != 1)
    {
        exit(EXIT_FAILURE);
    }
    while (getchar()!='\n') continue;
    char find_query_buf[1000 * findNum + 1];

    return 0;
}