#include "stdio.h"
#include "stdlib.h"

#define MAX_NUM 20


/*
统计有向图中各个顶点的出度和入度
有向图用邻接表表示
*/

typedef struct stru_node
{
    int vertex;
    struct stru_node *link;
} node;


void adjmat_to_adjlist(int matrix[][MAX_NUM], node adjlist[], int n)
{
    /*
    邻接矩阵 转 邻接表
    */
    int i,j;
    node *p;
    for ( i = 0; i < n; ++i)
    {
        //初始化adjlist
        adjlist[i].vertex = i;
        adjlist[i].link = NULL;
    }

    for ( i = 0; i < n; ++i)
    {
        p = adjlist + i;
        for ( j = 0; j < n; ++j)
        {
            if (matrix[i][j])
            {
                //添加新节点
                p->link = (node*) malloc(sizeof(node));
                p = p->link;
                p->vertex = j;
                p->link = NULL;
            }
        }
    }
}



void count_degree(node adjlist[], int n)
{
    /*
    计算邻接矩阵的入度、出度
    */
    int *in_degree = (int *) malloc(n*sizeof(int));
    int *out_degree = (int *) malloc(n*sizeof(int));
    int i;
    node* p;

    for ( i = 0; i < n; ++i)
    {
        in_degree[i] = 0;
        out_degree[i] = 0;
    }


    for ( i = 0; i < n; ++i)
    {
        p = (adjlist + i)->link;
        while(p)
        {
            out_degree[i]++;
            in_degree[p->vertex]++;
            p = p->link;
        }
    }

    printf("Node In-degree Out-degree\n");
    for ( i = 0; i < n; ++i)
    {
        printf("%4d %9d %10d\n", i, in_degree[i], out_degree[i]);
    }

}

int main(int argc, char const *argv[])
{
    int a[][MAX_NUM] = {
        {0, 4, 0, 10, 0},
        {0, 0, 0, 0, 0},
        {9, 0, 0, 6, 0},
        {0, 7, 0, 0, 0},
        {0, 0, 15, 0, 0},
    };
    int n = 5;

    node adjlist[MAX_NUM];
    adjmat_to_adjlist(a, adjlist, n);

    
    count_degree(adjlist, n);

    return 0;
}

