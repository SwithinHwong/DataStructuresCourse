#include "stdio.h"
#define LINEAR_MAX_LEN 32

typedef struct 
{
    int items[LINEAR_MAX_LEN];
    int len;
} linear_list; //定义线性表

int exchange(int *a, int *b)
{   /*互换ab*/
    int t = *a;
    *a = *b;
    *b = t;
    return 0;
}

int L_parity_replace(linear_list* pList)
/*使用最少的交换次数，将线性表A中所有奇数值元素保存在下标低的一端，
偶数值元素保存在下标高的一端。假定A中有n(>0)个元素，采用顺序存储结构。*/
{
    int left=0,right=0;
    int len = pList->len;
    if (len<1) return 1; // 长度有误

    for (left=0,right=len-1; left < len; ++left)
    {
        if (pList->items[left] & 1) continue;   // 找到左边下一个偶数，再执行后续代码
        for (; right>left && !(pList->items[right]&1) ; --right) // 找到从右数下一个奇数
            {}
        if (left == right) return 0; // 左右奇偶分布完成
        exchange(&pList->items[left], &pList->items[right]); //左偶右奇pair，互换

    }
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
    linear_list lis = {{1,2,3,4,5,6,7,8,9},9};
    printf("Origin list:\n");
    L_print(&lis);

    L_parity_replace(&lis);

    printf("New list:\n");
    L_print(&lis);

    return 0;
}