#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
    int width=4;
    int ori[4][4] = {{4,2,3,1},
                     {6,0,4,5},
                     {8,5,6,9},
                     {8,2,1,7}                     
                    };

    int i,j,t;

    //打印原始数组
    printf("Original matrix:\n");
    for ( i = 0; i < width; ++i)
    {
        for ( j = 0; j < width; ++j)
            printf("%d ", ori[i][j]);
        printf("\n");
    }

    //转置
    for ( i = 0; i < width; ++i)
        for (j = i+1; j < width; ++j)
        {
            t = ori[i][j];
            ori[i][j] = ori[j][i];
            ori[j][i] = t;
        }

    //打印新数组
    printf("\nNew matrix:\n");
    for ( i = 0; i < width; ++i)
    {
        for ( j = 0; j < width; ++j)
            printf("%d ", ori[i][j]);
        printf("\n");
    }

    

    return 0;
}