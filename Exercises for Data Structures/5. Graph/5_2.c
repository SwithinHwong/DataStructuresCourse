#include "stdio.h"
#include "stdlib.h"

#define MAX_NUM 20


/*
广度遍历无向连通图
*/



void BFS(int matrix[][MAX_NUM] , int n)
{
    int visited[MAX_NUM] = {0};
    int visit_queue[MAX_NUM] = {0};
    int front = -1;
    int rear = -1;
    int visit_vertex; // 当前访问的点


    visit_queue[++rear] = 0; // 点0入队
    visited[0] = 1;

    int i;
    while(front < rear)
    {
        visit_vertex = visit_queue[++front];
        for ( i = 0; i < n; ++i)
        {
            if (matrix[visit_vertex][i] && !visited[i])
            {
                //点i入队
                visit_queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }

    printf("Visit_queue: \n");
    for ( i = 0; i < n; ++i)
    {
        printf("%d ", visit_queue[i]);
    }
    printf("\n");

}




int main(int argc, char const *argv[])
{
  // int a[][MAX_NUM] = {
  //   {0, 16, 20, 19, 0, 0},
  //   {16, 0, 11, 0, 6, 5},
  //   {20, 11, 0, 22, 14, 0},
  //   {19, 0, 22, 0, 18, 0},
  //   {0, 6, 14, 18, 0, 9},
  //   {0, 5, 0, 0, 9, 0}
  // };
  // int n = 6;

    int a[][MAX_NUM] = {
        {0, 0, 9, 3, 0},
        {0, 0, 0, 0, 4},
        {9, 0, 0, 6, 0},
        {3, 0, 6, 0, 2},
        {0, 4, 0, 2, 0},
    };
    int n = 5;

    BFS(a,n);


    return 0;
}
