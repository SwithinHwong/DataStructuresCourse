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


int L_Delete(node* H,int b)
{   /*删除线性链表中所有值为ｂ的结点，链表表头为H*/
    node *p,*t;
    for (p = H; (p->link)!=NULL; )  // 遍历最后一个以外所有节点
    {
        if ( (p->link)->data == b ) // 要删除下一个节点
        {
            if (p->link->link == NULL)  //下一个节点是最后一个节点
                p->link = NULL;
            else
                p->link = (p->link)->link;  // 下一个不是最后一个节点
            continue;
        }
        p=p->link;
    }
    L_update_len(H);
    return 0;
}



int main(int argc, char const *argv[])
{
    int li[] = {5,2,3,4,5,5,7,5,9,5};
    node *H = CreatList(li,10);
    printf("Origin list:\n");
    L_print(H);

    printf("Delete 5\n");
    L_Delete(H,5);

    printf("New list:\n");
    L_print(H);

    return 0;
}