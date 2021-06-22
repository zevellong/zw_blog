#include <stdio.h>

int fun1(int a,int b, int c,int d, int e, int f, int g)
{
	
	int yy = 7;
	int y3 = 8;
	int y4 = 9;
	int y5 = 10;
	int y6 = 11;
	int h = a + b * c + d - e + f * g;
	return h;
}

int fun2(int a, int b)
{
	return a * b;
}
int main(int argc, char* argv[])
{
	int a;
	a = fun1(1,2,3,4,5,6,7);
	a = fun2(1,2);
	a = 4 * a;
	a = argc + 3;
	printf("argv=%s\n",argv[2]);
	return 0;
}
