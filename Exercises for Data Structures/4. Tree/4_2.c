#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define MAX_SIZE 100


/*
编写一个非递归算法，交换二叉树的左子树和右子树。
*/


typedef struct s_node
{
	char data;
	struct s_node *LChild,*RChild;
} BT_node;






BT_node* Create_BT(char str[])
{
	/*
	根据广义表建立二叉树
	广义表用@结尾，以字符串输入

	输出根节点地址
	*/
	BT_node* stack[MAX_SIZE];
	BT_node *p, *T=NULL;

	char ch;
	
	int flag = -1;
	int top = -1;
	int i;
	for(i=0; str[i]!='\0' && str[i]!='@'; i++)
	{
		ch = str[i];
		
		switch(ch)
		{
			case '(': 	//接下来是左子树
				stack[++top] = p;	//左括号前的节点入栈
				flag = 1;
				break;
			case ')':	//栈顶节点的左右子树处理完了，退栈
				top--;
				break;
			case ',':	//接下来是右子树
				flag = 2;	
				break;
			default:
				p = (BT_node *)malloc(sizeof(BT_node));
				p->data = ch;
				p->LChild = NULL;
				p->RChild = NULL;
				if(T == NULL)
					T = p;
				else if(flag == 1)	//节点是左子节点
					stack[top]->LChild = p;
				else
					stack[top]->RChild = p;
		}
	}
	return T;
}


int count_depth(BT_node *p)
{
	/*计算二叉树深度*/
	int l_level = 0;
	int r_level = 0;

	if (p == NULL)
		return 0;

	l_level = count_depth(p->LChild) + 1;
	r_level = count_depth(p->RChild) + 1;

	return l_level > r_level ? l_level : r_level;
}


void print_spaces(int n)
{
	/*打印n个空格*/
	int i;
	for ( i = 0; i < n; ++i)
	{
		printf(" ");
	}
	return;
}

void print_BT(BT_node *T)
{
	/*按层打印一棵树*/
	int depth = count_depth(T);
	BT_node *p = T;
	int i,j;
	BT_node **node_list = (BT_node**) malloc(sizeof(BT_node*)*pow(2,depth));
	node_list[0] = T;

	//计算每行开始有几个空格
	int *num_of_spaces = (int *) malloc(sizeof(int)*depth);
	num_of_spaces[depth-1] = 0;
	for ( i = depth-2; i >= 0; --i)
	{
		num_of_spaces[i] = num_of_spaces[i+1] + pow(2, depth-i-1);
	}

	//打印根节点
	print_spaces(num_of_spaces[0]);
	printf("%c\n",T->data );

	int seperate, last_length, length = 1;

	//一层层打印
	for ( i = 1; i < depth; ++i)
	{
		last_length = length;
		length = length*2;  // length = pow(2,i);

		//把这一层的所有节点存在node_list里，共length=2^i个
		for (j = 0; j < last_length ; ++j)
		{	
			//把上一层的每个节点展开成左右节点。如果上一层是NULL，下一层就存两个NULL
			node_list[length - 1 -2*j] = node_list[last_length-j-1] ? 
				node_list[last_length-j-1]->RChild : NULL;
			node_list[length - 1 -2*j -1] = node_list[last_length-j-1] ?
				node_list[last_length-j-1]->LChild : NULL;
		}
		seperate = pow(2, depth-i+1) -1;	//这层每两个节点间留出seperate个空格

		//打印节点与上一层的关系
		print_spaces(num_of_spaces[i]+1);
		for ( j = 0; j < length/2; ++j)
		{
			printf("%c", node_list[2*j] ? '/' : ' ');
			print_spaces(seperate - 2);
			printf("%c", node_list[2*j+1] ? '\\' : ' ');
			print_spaces(seperate + 2);
		}
		printf("\n");

		//打印这一层的节点
		print_spaces(num_of_spaces[i]);
		for ( j = 0; j < length; ++j)
		{
			//如果是空节点打印空格
			printf("%c", node_list[j] ? node_list[j]->data : ' ');
			print_spaces(seperate);
		}
		printf("\n");


	}
	
}

void exchange_BT(BT_node *T)
{
	/*交换二叉树的左子树和右子树*/
	BT_node *stack[MAX_SIZE];
	int top = -1;
	BT_node *temp, *p = T;

	while(p)
	{
		//对每个结点：交换左右子树、右节点入栈、进入左节点，结束本次循环
		temp = p->RChild;
		p->RChild = p->LChild;
		p->LChild = temp;

		if (p->LChild)
			stack[++top] = p->LChild;
		if (p->RChild)
			p = p->RChild;
		else if (top > -1)
			p = stack[top--];
		else
			p = NULL;
	}
}

int main(int argc, char const *argv[])
{
	char str[MAX_SIZE];
	printf("Enter binary tree with Generalized List ended with @\n");
	gets(str);

	BT_node *T;
	T = Create_BT(str);

	printf("Origin:\n");
	print_BT(T);
	
	exchange_BT(T);
	printf("\n\n\nExchanged:\n");
	print_BT(T);

	return 0;
}
