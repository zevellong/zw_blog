#include <stdio.h>
int main(int argc, char* argv[])
{
	int a = 10;
	int b = 20;
	int result;
	result = a * b;
	asm ("nop");
	printf("The value is %d\n",result);
	return 0;
}
