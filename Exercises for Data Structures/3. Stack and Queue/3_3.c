#include "stdio.h"
#include "stdlib.h"
/*
4、编写一个非递归算法，将十进制数转换成十六进制数，并输出转换后的数。      
*/





int pop(char stack[], int *top, char *out)
{
	/*出栈*/
	if (*top == -1)
		return 0;
	else
	{
		*out = stack[(*top)--];
		return 1;
	}
}

int push(char stack[], int len, int *top, char in)
{
	/*入栈*/
	if (*top >= len-1)
		return 0;
	else
	{
		stack[++(*top)] = in;
		return 1;
	}
}


int dec2hex(int dec, char stack[], int len, int *top)
{
	if (dec < 0)
		return 0;

	*top = -1;
	int temp;

	while(dec > 0)
	{
		temp = dec % 16;
		push(stack, len, top, temp<10 ? temp+'0' : temp-10+'A');
		dec /= 16;
	}

	if ((*top) == -1)
		push(stack, len, top, '0');

	return 1;
}



int main(int argc, char const *argv[])
{

	while(1)
	{
		int dec=0;
		printf("Enter a num:");
		scanf("%d", &dec);

		int len = 0;
		int i;
		for ( i = dec, len=0; i>0 ; ++len)	i/=10;
		if (!len) len = 1;
		
		//新建栈
		char *stack;
		stack = (char*) malloc(len*sizeof(char));
		int top = -1;

		dec2hex(dec, stack, len, &top);

		//打印
		char temp;
		while( pop(stack, &top, &temp) )
			putchar(temp);
		printf("\n***************\n");


		free(stack);

	}




	return 0;
}

