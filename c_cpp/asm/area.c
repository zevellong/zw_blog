#include <stdio.h>

double area(int r)
{
	return (3.1415926 * r * r);
}
int main()
{
	int i,j,k;
	double ii,jj,kk;
	i = 3;
	j = 4;
	k = 5;
	ii = area(i);
	jj = area(j);
	kk = area(k);
	printf("ii=%lf,jj=%lf,kk=%lf\n",ii,jj,kk);
	return 0;
}
