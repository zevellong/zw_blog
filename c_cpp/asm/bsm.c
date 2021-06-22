#include <stdio.h>
	int a = 10;
	int b = 20;
	int result;
int main(int argc, char* argv[])
{
	__asm__ __volatile__ (	"pusha\n\t"
			"movl a, %eax\n\t"
			"movl b, %ebx\n\t"
			"imull %ebx, %eax\n\t"
			"movl %eax, result\n\t"
			"popa"
		    );
	printf("The value is %d\n",result);
	return 0;
}
