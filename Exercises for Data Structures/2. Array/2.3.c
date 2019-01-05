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


void writeTripleArray(int table[3], int i, int j, int k)
{
    //将ijk写入数组
    table[0] = i;
    table[1] = j;
    table[2] = k;
}

int main(int argc, char const *argv[])
{

    int row=5, col=4;
    int ori[5][4] = {{4,2,3,1},
                     {6,0,4,5},
                     {8,5,6,9},
                     {8,2,1,7},
                     {0,9,0,1}
                    };

    
    //新建数组
    int (*min_table)[3] = newTripleTable(row);

    int i,j=0;
    for ( i = 0; i < row; ++i)
    {
        writeTripleArray(min_table[i], i+1, 1, ori[i][0]);
        for ( j = 0; j < col; ++j)
            if (ori[i][j] < min_table[i][2])
            {
                writeTripleArray(min_table[i], i+1, j+1, ori[i][j]);
            }
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
    printf("\nMin element:\n");
    for ( i = 0; i < row; ++i)
    {
        printf("%d %d %d\n", min_table[i][0], min_table[i][1], min_table[i][2]);
    }



    return 0;
}
