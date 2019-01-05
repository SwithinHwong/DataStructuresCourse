#include "stdio.h"
#include "stdlib.h"
/*
6、编写一个递归程序，解决Hanoi塔问题。要求盘数通过键盘输入控制，打印移动各盘的顺序。
*/

int *find_array(int X[], int Y[], int Z[],int value)
{
	//XYZ三个数组中，第一个元素存的是数组ID
	//找到与value匹配的数组，返回地址
	if (X[0] == value)
		return X;
	if (Y[0] == value)
		return Y;
	if (Z[0] == value)
		return Z;
	return NULL;

}



void printHanoi(int X[], int Y[], int Z[],int len)
{
	/*打印XYZ三个数组
	XYZ输入顺序随意，打印时根据数组第一个元素排序*/
	int i;
	int stick_num = 0;	//第几根杆
	int *stick = NULL;

	for (stick_num = 0; stick_num < 3; ++stick_num)
	{
		stick = find_array(X, Y, Z, stick_num);
		printf("%c: ", stick_num+'X');
		for ( i = 1; i < len && stick[i]; ++i)
			printf("%d ",stick[i] );
		printf("\n");
	}
	printf("\n********************\n");
}



void move(int X[], int Z[], int len)
{
	/*把X最后一个元素挪至Z最后
	len为数组长度*/

	//找到X、Z最后一个非零元素下标ij
	int i = len-1;
	while(i>0 && !X[i]) --i;
	int j = len-1;
	while(j>0 && !Z[j]) --j;
	// printf("%d %d\n", i,j);

	//move
	printf("Moving %d from %c to %c.\n", X[i], X[0]+'X', Z[0]+'X');
	Z[j+1] = X[i];
	X[i] = 0;

	
	

}


void Hanoi(int n, int X[], int Y[], int Z[],int len)
{
	//将X的最上面n个圆盘移至Z，len为数组长度
	if (n == 1)
	{
		move(X, Z, len);
		printHanoi(X, Y, Z, len);
	}

	else
	{
		Hanoi(n-1, X, Z, Y, len);
		move(X, Z, len);
		printHanoi(X, Y, Z, len);
		Hanoi(n-1, Y, X, Z, len);
	}
}


void test_hanoi()
{
	int i;
	int levels = 0;
	while(levels<1)
	{
		fflush(stdin);
		printf("Enter the num of levels:");
		scanf("%d",&levels);
	}

	int len = levels + 1;
	int *X,*Y,*Z;
	X = (int*) malloc(sizeof(int)*(len));
	Y = (int*) malloc(sizeof(int)*(len));
	Z = (int*) malloc(sizeof(int)*(len));
	X[0] = 0;
	Y[0] = 1;
	Z[0] = 2;


	for ( i = 1; i < len; ++i)
		X[i] = len-i;
	for ( i = 1; i < len; ++i)
		Y[i] = 0;
	for ( i = 1; i < len; ++i)
		Z[i] = 0;


	printHanoi(X,Y,Z,len);
	Hanoi( levels, X, Y, Z, len);
	
	

}


int main(int argc, char const *argv[])
{
	test_hanoi();
	return 0;
}



