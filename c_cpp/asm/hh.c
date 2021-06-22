#include <stdio.h>
int fun(int a,int b)
{
	a = 3;
	b = 4;
	return 9;
}
int main()
{
	int a,b;
	int c,d;
	c = fun(a,b);
	d = a + b;
	return 0;
}
