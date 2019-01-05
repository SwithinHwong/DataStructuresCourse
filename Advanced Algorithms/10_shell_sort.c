#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define MAX_SIZE 100
#define DEBUG 1


/*
编写一个程序，应用谢尔排序方法对一个输入序列进行降序排序。

*/

void _step_bubble_sort(int v[], int n, int step)
{
	/*
	输入：数组V，数组长度n，间隔步长step
	将v从第一个元素起，每step个元素作为子序列
	将子序列泡排序（降序）
	例如step=3，排序第1、4、7、10...个元素
	*/
	int i,temp;
	int isSorted = 0;
	int num_sorted = 0;	//已经排序完成的元素个数
	int num_seq = (n+step-1)/step; //需要排序的元素个数为ceil(n/step)
	for (num_sorted = 0; num_sorted < num_seq && (!isSorted); ++num_sorted)
	{
		isSorted = 1;
		//第num_sorted次循环，所以两两比较的元素中，前一个的序号一定小于 n - (num_sorted+1)*step
		for (i = 0; i < n - (num_sorted+1)*step; i+=step)
			if (v[i] < v[i+step])
			{
				isSorted = 0;
				temp = v[i];
				v[i] = v[i+step];
				v[i+step] = temp;
			}
	}

}

void shell_sort(int v[], int n)
{
	int d, start_index;
	int i;
	
	for (d = n/2; d>0 ; d/=2)
	{
		for (start_index = 0; start_index < d; ++start_index)
			_step_bubble_sort(v + start_index, n - start_index, d);
		if (DEBUG)
		{
			printf("d=%d, array= ", d);
			for ( i = 0; i < n; ++i)
				printf("%d ",v[i] );
			printf("\n");
		}
	}

}


int main(int argc, char const *argv[])
{
	int n,i;
	printf("Enter the number of the array: ");
	scanf("%d", &n);
	int* v = (int*) malloc(sizeof(int)*n);
	for ( i = 0; i < n; ++i)
		scanf("%d", v+i);

	// _step_bubble_sort(v, n, 2);

	shell_sort(v,n);

	printf("Finished!\n");
	for ( i = 0; i < n; ++i)
		printf("%d ",v[i] );
	printf("\n");

	
}
