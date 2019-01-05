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

void copy_array(int A[3], int B[3])
{
    /*把A的元素复制到B中*/
    B[0] = A[0];
    B[1] = A[1];
    B[2] = A[2];
}

int ( *add_triple(int A[][3], int B[][3]) )[3]
{
    int i=1,j=1,k=1;
    if (A[0][0]!=B[0][0] || A[0][1]!=B[0][1])   //AB维数不同
    {
        printf("Not same dimension!\n");
        return NULL;
    }

    //新建三元组
    int (*C)[3] = newTripleTable(A[0][2]+B[0][2]);
    copy_array(A[0],C[0]);  //复制第一行

    //开始相加
    while (i<=A[0][2] && j<=B[0][2])
    {
        if (A[i][0] < B[j][0]) //A行号小
            copy_array(A[i++], C[k++]);

        else if (A[i][0] > B[j][0]) //B行号小
            copy_array(B[j++], C[k++]);

        else //AB行号相同
        {
            if (A[i][1] < B[j][1]) //A列号小
                copy_array(A[i++], C[k++]);

            else if (A[i][1] > B[j][1]) //B列号小
                copy_array(B[j++], C[k++]);   

            else
            {
                copy_array(A[i++], C[k]); //行列相同，相加
                C[k++][2] += B[j++][2];
            }         
        }            
    }
    for (; i<=A[0][2] ; ++i)    //某一个三元组全部比较完，把另一个剩下的元素添加到C
        copy_array(A[i],C[k++]);
    for (; j<=B[0][2] ; ++j)
        copy_array(B[j],C[k++]);
    C[0][2] = k-1;  //k-1为三元组实际长度

    //释放多余空间
    for ( i = k; i < A[0][2]+B[0][2]; ++i)
        free(C[k]);


    return C;
}



void print_triple(int triple_table[][3])
{
    
    int num = triple_table[0][2];
    int i;
    for ( i = 0; i < num+1; ++i)
        printf("%d %d %d\n", triple_table[i][0], triple_table[i][1], triple_table[i][2]);
}


void print_matrix(int triple_table[][3])
{
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
    printf("Enter the triple table.");   //将输入n个元素
    printf("First line should be width, length, and number of elements. \n");
    printf("Triple table A:\n");
    int (*triple_table_A)[3] = initial_triple();
    printf("Triple table B:\n");
    int (*triple_table_B)[3] = initial_triple();

    //打印原始矩阵
    printf("\nMatrix A:\n");
    print_matrix(triple_table_A);
    printf("\nMatrix A:\n");
    print_matrix(triple_table_B);
    // print_matrix(triple_table);

    //相加
    int (*new_triple_table)[3] = add_triple(triple_table_A,triple_table_B);
    printf("\nSum matrix:\n");
    print_triple(new_triple_table);
    printf("\n");
    print_matrix(new_triple_table);


    return 0;
}