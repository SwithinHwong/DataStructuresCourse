#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define MAX_SIZE 100


/*
编写一个程序，建立一个二叉排序树并用中序遍历算法遍历该二叉排序树。要求：
二叉排序树建立时采用升序方式；数据通过键盘输入，输入-1时结束。

*/


typedef struct s_node
{
	int data;
	struct s_node *LChild,*RChild;
} BT_node;


BT_node* create_node(int n)
{
	/*
	新建一个节点，data等于n，左右子树为空

	输出节点地址
	*/
	BT_node *new = (BT_node*) malloc(sizeof(BT_node));
	new->data = n;
	new->LChild = NULL;
	new->RChild = NULL;
	return new;
}



BT_node* Create_ST(int list[], int n)
{
	/*
	根据数组元素建立二叉排序树
	
	输入：数组list，数组内元素个数n

	输出：根节点地址
	*/
	int i;
	BT_node *p = NULL;
	BT_node *q;
	BT_node *T;
	if (n <= 0)
		return NULL;

	// printf("list[0]=%d\n",list[0]);
	T = create_node(list[0]);
	

	for ( i = 1; i < n; ++i)
	{
		p = T;
		while(p)
		{
			q = p;
			if (list[i] < p->data)
				p = p->LChild;
			else
				p = p->RChild;
		}

		
		if (list[i] < q->data)
			q->LChild = create_node(list[i]);
		else
			q->RChild = create_node(list[i]);
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
	printf("%d\n",T->data );

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
			if (node_list[j])
			{
				printf("%d", node_list[j]->data);
			}
			else
				printf(" ");
			print_spaces(seperate);
		}
		printf("\n");


	}
	
}

void inorder(BT_node *T)
{
	/*中序遍历打印*/
	if (T == NULL)
		return;
	inorder(T->LChild);
	printf("%d ", T->data);
	inorder(T->RChild);
}



int main(int argc, char const *argv[])
{

	int list[MAX_SIZE] = {0};
	printf("Enter a sequence of numberes\n");
	printf("Enter -1 to stop\n");

	int n = 0;
	int new = 0;
	while( scanf("%d", &new) )
	{
		if (new == -1)
			break;
		list[n++] = new;
	}

	BT_node *T;
	T = Create_ST(list,n);

	print_BT(T);

	printf("inorder traversal:\n");
	inorder(T);
	printf("\n");
	
	
	

	return 0;
}
