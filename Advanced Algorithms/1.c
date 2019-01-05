#include "stdio.h"
#include <stdlib.h>


typedef struct stru_node
{
    int data;
    struct stru_node *link;
} node; //定义线性链表节点


node *CreatLoopList(int n)
{   /*1,2,...,n建立无头循环链表*/
    node* Head;
    Head = (node*) malloc( (n+1)*sizeof(node) );    //申请连续空间
    int i;
    for ( i = 0; i < n-1; ++i)
    {
        Head[i].data = i+1;
        Head[i].link = Head+i+1;
    }
    Head[n-1].data = n;
    Head[n-1].link = Head;

    return Head;

}




int L_Loop_print(node* pList)
{
    /*将循环线性表打印*/
    printf("Type:Linear_list\n");

    printf("{  ");
    node *p;
    for ( p = (pList->link); p!=NULL && p!=pList; p = p->link)
    {
        printf("%d, ", p->data);
    }
    printf("\b\b }\n");

    return 0;

}



void Josephu(int n, int m, int k)
{
    //n个人，从k开始，每m个出列
    node *H = CreatLoopList(n);
    int i = 0;

    //跳到第k-1个人
    for (i = 0; i < k-2; ++i)
        H = H->link;

    while(H->link != H)
    {
        for ( i = 0; i < m-1; ++i)
        {
            H = H->link;
        }
        printf("No.%d out.\n", H->link->data);
        H->link = H->link->link; //出列，删除

    }
    printf("No.%d out.\n", H->data);
    printf("Done.\n");
}


int main(int argc, char const *argv[])
{
    int n,m,k;
    printf("Enter n m k:\n");
    while(scanf("%d %d %d",&n,&m,&k)<3)
    {
        printf("Wrong!\n");
        fflush(stdin);
    }

    Josephu(n,m,k);

    return 0;
}
