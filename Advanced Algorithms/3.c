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

int ( *initial_triple() )[3]
{
    /*根据输入创建三元组*/

    int row,col,len;
    printf("Enter the triple table:\n");  
    printf("First line should be width, length, and number of elements. \n");
    scanf("%d %d %d",&row, &col, &len);

    //创建(len+1)*3数组
    int (*triple_table)[3] = newTripleTable(len+1);

    //输入元素
    triple_table[0][0] = row;
    triple_table[0][1] = col;
    triple_table[0][2] = len;
    int i;
    for ( i = 1; i < len+1; ++i)
    {
        scanf("%d %d %d", triple_table[i] ,triple_table[i]+1 , triple_table[i]+2 );
    }

    return triple_table;
}



int ( *transpose_triple(int triple_table[][3]) )[3]
{
    /*快速转置三元组*/

    int col = triple_table[0][0];//转置后新矩阵的row,col
    int row = triple_table[0][1];
    int len = triple_table[0][2];
    

    //创建(len+1)*3数组
    int (*new_triple_table)[3] = newTripleTable(len+1);

    //赋值第一行
    new_triple_table[0][0] = row;
    new_triple_table[0][1] = col;
    new_triple_table[0][2] = len;
    
    //申请长度为row的数组
    int *pos = (int *) malloc(row*sizeof(int)); //数组pos先是存放各列元素个数，再存放各列在新三元组的位置
    int i,j;
    for ( i = 0; i < row; ++i)
        pos[i] = 0;

    //计算原矩阵第i列元素个数
    for ( i = 1; i <= len; ++i)
        pos[ triple_table[i][1] - 1 ]++;

    //计算原矩阵第i列首个非零元素在新三元组中位置，从第1行开始数
    pos[row-1] = len+1 - pos[row-1];
    for ( i = row-2; i >= 0; --i)
        pos[i] = pos[i+1] - pos[i];

    //转置
    for ( i = 1; i <= len; ++i)
    {
        j = pos[triple_table[i][1]-1];
        new_triple_table[j][0] = triple_table[i][1];
        new_triple_table[j][1] = triple_table[i][0];
        new_triple_table[j][2] = triple_table[i][2];
        pos[triple_table[i][1]-1]++;
    }



    return new_triple_table;
}

void print_triple(int triple_table[][3])
{
    /*打印三元组*/
    int num = triple_table[0][2];
    int i;
    for ( i = 0; i < num+1; ++i)
        printf("%d %d %d\n", triple_table[i][0], triple_table[i][1], triple_table[i][2]);
}


void print_matrix(int triple_table[][3])
{
    /*打印三元组的矩阵形式*/
    int row = triple_table[0][0];
    int col = triple_table[0][1];
    int num = triple_table[0][2];
    int next = 1;//下一个打印的元素序号
    int i,j;
    for ( i = 0; i < row; ++i)
    {
        for (j = 0; j < col; ++j)
        {
            if (next<num+2 && triple_table[next][0]==i+1 && triple_table[next][1]==j+1)
            {
                printf("%d ",triple_table[next][2] );
                ++next;
            }
            else
                printf("0 ");
        }
        printf("\n");
    }
}



int main(int argc, char const *argv[])
{
    //创建三元组
    int (*triple_table)[3] = initial_triple();
    //打印原始矩阵
    printf("\nOriginal Matrix:\n");
    print_triple(triple_table);
    printf("\n");
    print_matrix(triple_table);

    //转置
    int (*new_triple_table)[3] = transpose_triple(triple_table);
    printf("\nTransposed matrix:\n");
    print_triple(new_triple_table);
    printf("\n");
    print_matrix(new_triple_table);

    return 0;
}