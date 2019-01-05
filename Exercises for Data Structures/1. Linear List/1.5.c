#include "stdio.h"
#include <stdlib.h>


typedef struct stru_node
{
    int data;
    struct stru_node *link;
} node; //定义线性链表


node *CreatList(int array[], int n)
{   /*将数组建立线性表*/
    node* Head;
    Head = (node*) malloc( (n+1)*sizeof(node) );    //申请连续空间
    Head[0].data = n;
    int i;
    for ( i = 0; i < n; ++i)
    {
        Head[i+1].data = array[i];
        Head[i].link = Head+i+1;
    }
    Head[n].link = NULL;
    return Head;

}




int L_update_len(node *H)
{   /*更新链表长度*/
    int count=0;
    node *p;
    for ( p = (H->link); p!=NULL && p!=H; p = p->link,++count)
        {}
    H->data = count;
    return 0;

}



int L_print(node* pList)
{
    /*将线性表打印*/
    printf("Type:Linear_list\n");
    printf("Length:%d\n",pList->data );
    printf("{  ");
    node *p;
    for ( p = (pList->link); p!=NULL && p!=pList; p = p->link)
    {
        printf("%d, ", p->data);
    }
    printf("\b\b }\n");

    return 0;

}





node* sort_combine_recursion(node* A,node* B)
{   /*递归将有序链表A、B中的节点合并排序
        输入：AB无表头*/
    if (A == NULL && B == NULL)
        return NULL;
    else if (A == NULL)
        return B;
    else if (B == NULL)
        return A;
    
    if (A->data < B->data)
    {
        A->link = sort_combine_recursion(A->link,B);
        return A;
    }
    else
    {
        B->link = sort_combine_recursion(A,B->link);
        return B;
    }
}


node* L_Combine(node* A, node* B)
{   /*将有序链表A和B合并成新的链表C。表A、B、C的表头指针为HA、HB和HC*/
    A->link = sort_combine_recursion(A->link,B->link);
    L_update_len(A);
    return A;
}



int main(int argc, char const *argv[])
{
    int li_A[] = {1,3,5,7,9,11,13,15,17};
    node *HA = CreatList(li_A,9);
    int li_B[] = {2,4,6,8,10,16};
    node *HB = CreatList(li_B,6);
    
    printf("A:");
    L_print(HA);
    printf("B:");
    L_print(HB);

    
    node* HC = L_Combine(HA,HB);

    printf("New list:\n");
    L_print(HC);

    return 0;
}