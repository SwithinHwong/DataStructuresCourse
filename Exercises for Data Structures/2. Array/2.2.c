#include "stdio.h"
#include "stdlib.h"


int main(int argc, char const *argv[])
{

    int width = 4;
    int ori[4][4] = {{1,2,3,0},
                     {0,1,4,0},
                     {0,5,6,0},
                     {7,0,0,8}
                    };

    //打印原始数组
    printf("Original matrix:\n");
    int i,j;
    for ( i = 0; i < width; ++i)
    {
        for ( j = 0; j < width; ++j)
            printf("%d ", ori[i][j]);
        printf("\n");
    }


    int sum = 0;
    for (int i = 0; i < width; ++i)
    {
        sum += ori[i][i];
        if ((width - 1 - i) != i) //和主对角线不重复
            sum += ori[i][width-1-i];
    }

    printf("\nSUM = %d\n", sum);

    return 0;
}
