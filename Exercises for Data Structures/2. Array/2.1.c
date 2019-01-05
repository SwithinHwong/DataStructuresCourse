#include "stdio.h"
#include "stdlib.h"

int (*newTripleTable(int n))[3]
{
    /*新建n*3数组*/
    int (*triple_table)[3] = (int (*)[3]) malloc(sizeof(int)*3*n); 
    int i,j;
    for ( i = 0; i < n; ++i)
        for ( j = 0; j < 3; ++j)
            triple_table[i][j] = 0;

    return triple_table;

}




int main(int argc, char const *argv[])
{

    int row=5, col=4;
    int ori[5][4] = {{1,2,3,0},
                     {0,0,4,0},
                     {0,5,6,0},
                     {7,0,0,8},
                     {0,9,0,0}
                    };


    //计算非零个数count
    int i,j,count=0;
    for ( i = 0; i < row; ++i)
        for ( j = 0; j < col; ++j)
            if (ori[i][j])
                count++;


    //新建三元组
    int (*triple_table)[3] = newTripleTable(count+1);

    triple_table[0][0] = row;
    triple_table[0][1] = col;
    triple_table[0][2] = count;

    for ( i = 0, count=1; i < row; ++i)
        for ( j = 0; j < col; ++j)
            if (ori[i][j])
            {
                triple_table[count][0] = i+1;
                triple_table[count][1] = j+1;
                triple_table[count][2] = ori[i][j];
                count++;
            }

    //打印原始数组
    printf("Original matrix:\n");
    for ( i = 0; i < row; ++i)
    {
        for ( j = 0; j < col; ++j)
            printf("%d ", ori[i][j]);
        printf("\n");
    }

    //打印三元组
    printf("\nTriple table:\n");
    for ( i = 0; i < count; ++i)
    {
        printf("%d %d %d\n", triple_table[i][0], triple_table[i][1], triple_table[i][2]);
    }



    return 0;
}
