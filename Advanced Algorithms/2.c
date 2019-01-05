#include "stdio.h"
#include <stdlib.h>


typedef struct stru_node
{
    int coefficient;
    int power;
    struct stru_node *link;
} node; //定义线性链表节点

node *CreatNode(int coefficient, int power)
{
    /*建立一个空节点*/
    node* P;
    P = (node*) malloc( sizeof(node) );
    P->link = NULL;
    P->coefficient = coefficient;
    P->power = power;
    return P;
}


node *CreatPolynomial()
{   /*从键盘接受多个系数、指数，创建链表*/
    node *Head = CreatNode(0,0);
    node *P = Head;
    int i,power,coefficient;
    printf("Enter every coefficient and power.\n");
    printf("Enter any letter to continue.\n");
    while(scanf("%d",&coefficient) && scanf("%d",&power))
    {
        P->link = CreatNode(coefficient,power);
        P = P->link;
    }
    fflush(stdin);

    return Head;

}

void SortPolynomial(node *Head)
{
    /*冒泡排序，按指数升序排列*/
    node *end = NULL;
    node *p = Head;
    node *t;
    for (; p->link!=end ; p = Head)
    {
        for (; (p->link != end) && (p->link->link!=end); p = p->link)
        {
            if (p->link->power > p->link->link->power) //交换p之后两个节点
            {
                t = p->link;
                p->link = p->link->link;
                t->link = p->link->link;
                p->link->link = t;
            }
            else if (p->link->power == p->link->link->power) // 指数相等的两项: 系数相加，合并
            {
                p->link->coefficient += p->link->link->coefficient;
                //删除重复节点
                t = p->link->link;
                p->link->link = t->link;
                free(t);
                // printf("delete done");
                // Print_Polynomial(Head);
            }
            
        }
        end = p->link;

    }
    //Print_Polynomial(Head);
}



int Print_Polynomial(node* pList)
{
    /*格式化打印一元多项式*/
    node *p = (pList->link);
    printf("%d*X^%d ", p->coefficient, p->power);
    for ( p = (p->link); p!=NULL && p!=pList; p = p->link)
    {
        if(p->coefficient == 0)
            continue;
        else if (p->coefficient > 0)
        {
            printf("+ %d*X^%d ", p->coefficient, p->power);
        }
        else
            printf("- %d*X^%d ", (-1)*(p->coefficient), p->power);
        
    }
    printf("\n");

    return 0;

}

node *AddPolynomial(node *A, node *B)
{   /*多项式相加*/
    node *Head = CreatNode(0,0);
    node *P = Head;
    A = A->link;
    B = B->link;
    int i,power,coefficient;
    while(A && B)
    {
        if (A->power == B->power)
        {
            P->link = CreatNode(A->coefficient + B->coefficient, A->power);
            P = P->link;
            A = A->link;
            B = B->link;
        }
        else if (A->power < B->power)
        {
            P->link = CreatNode(A->coefficient,A->power);
            P = P->link;
            A = A->link;
        }
        else
        {
            P->link = CreatNode(B->coefficient,B->power);
            P = P->link;
            B = B->link;
        }
        
    }
    while (A)
    {
        P->link = CreatNode(A->coefficient,A->power);
        P = P->link;
        A = A->link;
    }
    while (B)
    {
        P->link = CreatNode(B->coefficient,B->power);
        P = P->link;
        B = B->link;
    }

    return Head;

}


int main(int argc, char const *argv[])
{
    node *A = CreatPolynomial();
    SortPolynomial(A);
    Print_Polynomial(A);
    node *B = CreatPolynomial();
    SortPolynomial(B);
    Print_Polynomial(B);
    node *C = AddPolynomial(A,B);
    Print_Polynomial(C);


    return 0;
}