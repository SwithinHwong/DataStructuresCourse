#include "stdio.h"
#include "stdlib.h"
/*
3、编写算法，用两个大小相同的栈来模拟一个队列的操作(包括入队操作和出队操作两个算法)。
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

int solve_full_queue(char stack_push[], int *top_push, char stack_pop[], int *top_pop, int stack_len)
{
	/*栈满操作，把push栈中元素尽量挪至pop栈*/
	int i;
	char temp_value;
	int empty_num = stack_len-1 - *top_pop;	//剩余空间

	//新建两个临时缓存栈
	char *temp_push_stack, *temp_pop_stack;
	temp_push_stack = (char*) malloc(stack_len*sizeof(char));
	temp_pop_stack = (char*) malloc(stack_len*sizeof(char));
	int top_temp_push = -1;
	int top_temp_pop = -1;

	//把stack_pop栈倒入临时栈
	while(*top_pop != -1)
	{
		pop(stack_pop, top_pop, &temp_value);
		push(temp_pop_stack, stack_len, &top_temp_pop, temp_value);
	}
	//把stack_push栈倒入临时栈
	while(*top_push != -1)
	{
		pop(stack_push, top_push, &temp_value);
		push(temp_push_stack, stack_len, &top_temp_push, temp_value);
	}
	//把stack_pop的临时栈存满
	for ( i = 0; i < empty_num; ++i)
	{
		pop(temp_push_stack, &top_temp_push, &temp_value);
		push(temp_pop_stack, stack_len, &top_temp_pop, temp_value);
	}
	//把临时栈stack_pop栈倒入
	while(top_temp_pop != -1)
	{
		pop(temp_pop_stack, &top_temp_pop , &temp_value);
		push(stack_pop, stack_len, top_pop, temp_value);
	}
	//把临时栈倒入stack_push栈
	while(top_temp_push != -1)
	{
		pop(temp_push_stack , &top_temp_push , &temp_value);
		push(stack_push, stack_len, top_push , temp_value);
	}
	free(temp_push_stack);
	free(temp_pop_stack);
	return 1;
}

int add_queue(char stack_push[], int *top_push, char stack_pop[], int *top_pop, int stack_len, char in)
{
	/*入队*/
	if ((*top_push) >= stack_len-1)	//push栈满
	{
		if ((*top_pop) >= stack_len-1)
			return 0;	//栈都满了
		else
			solve_full_queue(stack_push, top_push, stack_pop, top_pop, stack_len);	//栈满操作
	}

	stack_push[++(*top_push)] = in;
	return 1;
	
}

int del_queue(char stack_push[], int *top_push, char stack_pop[], int *top_pop, int stack_len, char *out)
{
	/*出队*/
	if ((*top_pop) == -1)	//出队栈为空
	{
		if ((*top_push) == -1)
			return 0;	//栈都空
		else
		{
			char temp_value;
			while((*top_push) != -1)
			{
				//把push栈倒入pop栈
				pop(stack_push , top_push , &temp_value);
				push(stack_pop, stack_len, top_pop , temp_value);
			}
		}
	}
	*out = stack_pop[(*top_pop)--];
	return 1;

}

void print_stacks(char stack_push[], int *top_push, char stack_pop[], int *top_pop)
{
	printf("StackPush:\n");
	int i;
	for ( i = 0; i <= *top_push; ++i)
	{
		printf("%c ",stack_push[i] );
	}

	printf("\nStackPop:\n");
	for ( i = 0; i <= (*top_pop); ++i)
	{
		printf("%c ",stack_pop[i] );
	}
	printf("\n************\n");

}


int main(int argc, char const *argv[])
{
	//新建两个栈
	int stack_len = 4;
	char stack_push[4];
	char stack_pop[4];
	int top_pop = -1;
	int top_push = -1;

	int i;
	char temp_value;
	char push_queue[] = "ABCDEFGH";	//入队顺序

	for ( i = 0; i < 3; ++i)	//入队3个
	{
		add_queue(stack_push, &top_push, stack_pop, &top_pop, stack_len, push_queue[i]);
		printf("Pushed value <-- %c\n", push_queue[i]);
		print_stacks(stack_push, &top_push, stack_pop, &top_pop);
	}
	for ( i = 0; i < 2; ++i)	//出队2个
	{
		del_queue(stack_push, &top_push, stack_pop, &top_pop, stack_len, &temp_value);
		printf("Popped value --> %c\n", temp_value);
		print_stacks(stack_push, &top_push, stack_pop, &top_pop);
	}
	for ( i = 3; i < 8; ++i)	//入队5个
	{
		add_queue(stack_push, &top_push, stack_pop, &top_pop, stack_len, push_queue[i]);
		printf("Pushed value <-- %c\n", push_queue[i]);
		print_stacks(stack_push, &top_push, stack_pop, &top_pop);
	}
	for ( i = 2; i < 8; ++i)	//出队6个
	{
		del_queue(stack_push, &top_push, stack_pop, &top_pop, stack_len, &temp_value);
		printf("Popped value --> %c\n", temp_value);
		print_stacks(stack_push, &top_push, stack_pop, &top_pop);
	}
	return 0;
}


