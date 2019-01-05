#include "stdio.h"
#define LINEAR_MAX_LEN 32

typedef struct 
{
    int items[LINEAR_MAX_LEN];
    int len;
} linear_list; //定义线性表

int L_Delete_sorted(linear_list* pList, int del_num)
{
    /*删除线性表*pList中所有值为del_num的元素*/
    int i,j,k;
    int len = pList->len;
    if (len < 1) return 1;   //线性表长度非正，直接return

    for (i = 0; i<len && (pList->items[i])<del_num; ++i) //尝试找第一个要删除的del_num
        {} 

    if (i == len || (pList->items[i])>del_num) //没有要删除的元素
    {
        return 0; 
    }

    for (j=k=i; k<len; ++k)
    {
        if (pList->items[k] == del_num) //直到j指向移动到的位置，k指向要移动的变量
        {
            continue; 
        }
        pList->items[j]  = pList->items[k]; //然后开始移动
        ++j;
    }
    pList->len = j;
    return 0;
}


int L_print(linear_list* pList)
{
    /*将线性表打印为数组格式*/
    printf("Type:Linear_list\n");
    printf("Length:%d\n",pList->len );
    printf("{  ");
    int i;
    for (i = 0; i < pList->len; ++i)
    {
        printf("%d, ", pList->items[i]);
    }
    printf("\b\b }\n");

    return 0;

}



int main(int argc, char const *argv[])
{
    linear_list lis = {{1,2,3,4,4,4,5,5,7},9};
    int del_num = 4;
    printf("Origin list:\n");
    L_print(&lis);

    printf("Delete: %d\n", del_num );
    L_Delete_sorted(&lis, del_num);

    printf("New list:\n");
    L_print(&lis);

    return 0;
}