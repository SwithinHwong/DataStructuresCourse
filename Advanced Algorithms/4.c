#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
    int n=0;
    printf("Enter an odd length of magic matrix:");
    scanf("%d",&n);
    while( !(n&1) || n<1)
    {
        printf("Invalid length!\n");
        fflush(stdin);
        scanf("%d",&n);
    }
    
    //创建n*n数组
    int **magic_matrix, i, j;
    magic_matrix = (int **)malloc(n * sizeof(int *));   // 先分配m个指针单元，注意是指针单元 
    for(i = 0; i < n; i++)  //再分配n个字符单元，上面的m个指针单元指向这n个字符单元首地址
        magic_matrix[i] = (int *)malloc(n * sizeof(int));

    //清零
    for ( i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            magic_matrix[i][j] = 0;


    //初始位置
    int row = n-1;
    int col = n/2;

    for (int next = 1; next <= n*n; ++next) //next为下一个填入的数字
    {
        if (magic_matrix[row][col] != 0 ) //下2，左1 等同于 上n-2，右n-1
        {
            row = (row + n-2) % n;
            col = (col + n-1) % n;
        }

        magic_matrix[row][col] = next;

        row = (row + 1) % n;
        col = (col + 1) % n;

    }


    //输出

    int len,max=n*n; //计算n*n是几位数,方便对齐
    for (len = 0; max > 0; ++len,max/=10) {}

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
            printf("%*d  ", len, magic_matrix[i][j] );
        printf("\n");
    }


    return 0;
}