#include "stdio.h"
#include "stdlib.h"

#define MAX_NUM 20
#define BREAK 999

/*
用prim方法生成带权无向连通图的最小代价生成树

*/


void min_span_tree(int matrix[][MAX_NUM] , int n)
{
	int minWeight2Tree[MAX_NUM] = {0};	//记录每个点到生成树的最小距离，已划入树的距离为0
	int nearestVertexInTree[MAX_NUM] = {0};	//记录离每个节点最近的生成树中的节点
	int i,j;

	int nearestVertex = 1; //生成树外所有点中离生成树最近的点
	minWeight2Tree[1] = matrix[0][1];
	for ( i = 2; i < n; ++i)
	{
		minWeight2Tree[i] = matrix[0][i];
		if (minWeight2Tree[nearestVertex] > minWeight2Tree[i])
			nearestVertex = i;	//寻找最近的点
	}

	for ( i = 0; i < n-2; ++i)
	{
		printf("Edge: v[%d]--v[%d]\n", nearestVertexInTree[nearestVertex] , nearestVertex);
		minWeight2Tree[nearestVertex] = 0;
		for ( j = 0; j < n; ++j)
		{
			if (matrix[nearestVertex][j] < minWeight2Tree[j])	//点nearestVertex进入生成树，更新最小距离
			{
				minWeight2Tree[j] = matrix[nearestVertex][j];
				nearestVertexInTree[j] = nearestVertex;	//寻找最近的点
			}

		}

		nearestVertex = 0;

		for ( j = 1; j < n; ++j)
		{
			if (minWeight2Tree[j] != 0)
			{
				if (nearestVertex == 0 || minWeight2Tree[j] < minWeight2Tree[nearestVertex])
				{
					nearestVertex = j;	//nearestVertex初始值为第一个非零距离的点，再依次往后比较寻找更近的点
				}
			}
		}
	}
	printf("Edge: v[%d]--v[%d]\n", nearestVertexInTree[nearestVertex] , nearestVertex);
	
}



int main(int argc, char const *argv[])
{
	int a[][MAX_NUM] = {
		{BREAK, 16, 20, 19, BREAK, BREAK},
		{16, BREAK, 11, BREAK, 6, 5},
		{20, 11, BREAK, 22, 14, BREAK},
		{19, BREAK, 22, BREAK, 18, BREAK},
		{BREAK, 6, 14, 18, BREAK, 9},
		{BREAK, 5, BREAK, BREAK, 9, BREAK}
	};
	int n = 6;

	min_span_tree(a,n);

	return 0;
}
