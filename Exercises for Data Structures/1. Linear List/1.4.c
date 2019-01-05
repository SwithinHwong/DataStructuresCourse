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



node *CreatEmptyList(int n)
{
    node* Head;
    Head = (node*) malloc( (n+1)*sizeof(node) );    //申请连续空间
    Head[0].data = n;
    int i;
    for ( i = 0; i < n; ++i)
    {
        Head[i+1].data = 0;
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


node* L_Twine_newList(node* A,node* B)
{   /*AB节点交叉插入新链表*/
    L_update_len(A);
    L_update_len(B);
    int min_len = A->data < B->data ? A->data : B->data;
    node *C = CreatEmptyList(A->data + B->data); //新建C
    node *pC = C->link;
    node *pA=A->link, *pB=B->link;
    int i;
    for (i = 0; i < min_len; ++i)   //AB交叉插入
    {
        pC->data = pA->data;
        pC->link->data = pB->data;
        pC = pC->link->link;
        pA = pA->link;
        pB = pB->link;
    }
    if (A->data > B->data)  // A或B剩余部分插入
        for (i*=2; i < C->data; ++i)
        {
            pC->data = pA->data;
            pC = pC->link;
            pA = pA->link;
        }
    else
        for (i*=2; i < C->data; ++i)
        {
            pC->data = pB->data;
            pC = pC->link;
            pB = pB->link;
        }
        
    return C;
}


node* L_Twine(node* A,node* B)
{   /*AB节点交叉组装新链表*/
    L_update_len(A);
    L_update_len(B);
    int min_len = A->data < B->data ? A->data : B->data;
    node *pC = A->link;
    node *pA=A->link, *pB=B->link;
    int i;
    for (i = 0; i < min_len-1; ++i)   //AB交叉
    {
        pA = pA->link;  //pC已经指向A的第一个正式节点，pA先后移
        pC = pC->link = pB;
        pB = pB->link;
        pC = pC->link = pA;
    }
    pA = pA->link;
    pC = pC->link = pB;
    pB = pB->link;
    pC->link = pA;

    if (pC->link == NULL)  // B比A长，B剩余部分插入
        pC->link=pB;
    L_update_len(A);

    return A;
}



int main(int argc, char const *argv[])
{
    int li_A[] = {1,3,5,7,9,11,13,15,17};
    node *A = CreatList(li_A,9);
    int li_B[] = {2,4,6,8,10,12};
    node *B = CreatList(li_B,6);
    
    printf("A:");
    L_print(A);
    printf("B:");
    L_print(B);

    node* C =L_Twine(A,B);

    printf("New list:\n");
    L_print(C);

    return 0;
}