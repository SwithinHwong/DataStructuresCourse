#include "stdio.h"
/*
7、
编写一个程序，实现中缀表达式向后缀表达式的转换。要求：
键盘输入一个表达式，并以字符#表示结束；
输出为后缀表达式形式。
*/

#define MAX_LEN 50



int pop(char stack[], int *top, char *out)
{
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
	if (*top >= len-1)
		return 0;
	else
	{
		stack[++(*top)] = in;
		return 1;
	}
}


int isp(char x) /* 栈内优先级 */
{
	int isp = 0;
	switch(x) 
	{
		case '+': case '-': isp = 1;  break;
		case '*': case '/': case '%': isp = 2; break;
		case '^': isp = 3; break;
		case '(': isp = 0; break;
		case ')': isp = 0; break;
		default: isp = 0; break; 
	}
	return isp;
}


int icp(char x) /* 栈外优先级 */
{ 
	int icp = 0;
	switch(x) 
	{
		case '+': case '-': icp = 1; break;
		case '*': case '/': case '%': icp = 2; break;
		case '^': icp = 4; break;
		case '(': icp = 5; break;
		case ')': icp = 0; break;
		default: icp = 0; break; 
	}
	return icp;
}

void toPostFix(char nifix[], char postfix[])
{	
	char token_stack[MAX_LEN];
	int top_token = -1;

	int i,j=0;
	for ( i = 0; nifix[i]!='#'; ++i)	//遍历所有中缀字符
	{
		// printf("Processing %c\n",nifix[i] );
		if ((nifix[i]>='0' && nifix[i]<='9') || (nifix[i]>='A' && nifix[i]<='Z') ||
			(nifix[i]>='a' && nifix[i]<='z') )	//字符是操作数，直接输出
		{
			postfix[j++] = nifix[i];
		}
		else if (nifix[i] == ')')	
		{
			//如果是右括号，栈中运算符出栈，直到左括号出栈为止，然后消去左右括号，读入下一个单词
			while(top_token > -1 && j>0 && postfix[j-1]!='(')
				pop(token_stack, &top_token, postfix + j++);
			if (j>0 && postfix[j-1] == '(' ) 
				j--;	//删去左括号
		}
		else
		{
			//如果是运算符，与栈内运算符进行优先级比较
			//若栈外高于栈内，栈外运算符入栈；
			//否则，栈内运算符出栈，继续进行比较，直到栈外运算符入栈为止
			while(top_token > -1 && icp(nifix[i])<=isp(token_stack[top_token]))
				pop(token_stack, &top_token, postfix + j++);
			if( top_token<0 || icp(nifix[i])>isp(token_stack[top_token]) )
				push(token_stack, MAX_LEN, &top_token, nifix[i]);
		}
	}

	//如果是表达式结束定界符，将栈内的所有运算符出栈，直到栈空为止
	while(top_token > -1)
		pop(token_stack, &top_token, postfix + j++);
	postfix[j] = '#';
	postfix[j+1] = '\0';
}


int main(int argc, char const *argv[])
{
	char nifix[MAX_LEN] = "";
	char postfix[MAX_LEN] = "";
	
	printf("Enter a nifix, ending with '#'\n");
	// gets(nifix);
	scanf("%s", nifix);

	toPostFix(nifix, postfix);
	printf("%s\n", postfix);
	return 0;
}
