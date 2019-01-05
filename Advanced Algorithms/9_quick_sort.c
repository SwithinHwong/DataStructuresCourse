#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define MAX_SIZE 100

/*
编写一个程序，应用快速排序方法对一个输入序列进行升序排序。
*/


void quick_sort(int v[], int n)
{
	//将v中存的n个元素快速排序（升序）
	if (n<2)
		return;
	int left = 0;
	int right = n-1;
	int temp;
	int left_or_right = 1; //1时right向左挪动，0时left向右移动
	while(left<right)
	{
		while(left<right && v[left]<=v[right])
			if (left_or_right)
				right--;	//从right向左寻找
			else
				left++;	//从left向右寻找
		if (left < right)
		{
			temp = v[left];
			v[left] = v[right];
			v[right] = temp;
			
			if (left_or_right)
				left++;	//交换完，从left+1开始向右寻找
			else
				right--;	//交换完，从right-1开始向右寻找
		}
		left_or_right = 1 - left_or_right;
	}

	/*
	//下面这个while和上面的while等价
	while(left<right)
	{
		while(left<right && v[left]<=v[right]) right--;
		if (left < right)
		{
			temp = v[left];
			v[left] = v[right];
			v[right] = temp;
			left++;
		}
		while(left<right && v[left]<=v[right]) left++;
		if (left < right)
		{
			temp = v[left];
			v[left] = v[right];
			v[right] = temp;
			right--;
		}
	}
	*/


	// printf("%d %d\n",left,right );
	//这时应该left==right
	quick_sort(v,left);
	quick_sort(v+right+1,n-right-1);

}



int main(int argc, char const *argv[])
{
	int n,i;
	printf("Enter the number of the array: ");
	scanf("%d", &n);
	int* v = (int*) malloc(sizeof(int)*n);
	for ( i = 0; i < n; ++i)
		scanf("%d", v+i);

	quick_sort(v, n);
	printf("Finished!\n");
	for ( i = 0; i < n; ++i)
		printf("%d ",v[i] );
	printf("\n");

	
}
