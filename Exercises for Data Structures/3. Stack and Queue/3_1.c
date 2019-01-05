#include "stdio.h"
#include "stdlib.h"
/*编写一个算法，对题1中元素的任意排列顺序进行判断，检查出不可能的出栈顺序。
*/

char* Permutation(char* pStr, char* pBegin, char* pPrint);   

char* permutation(char* pStr)  
{  
	/*
	返回输入字符串中所有字符的全排列
	输出格式为各种排列结果拼接成的长字符串
	长字符串用\0分割
	eg：输入"AB"
	输出 "AB\0BA"
	*/
	int i;
	int len = 0;
	for ( i = 0; i < 1000; ++i)
	{
		if (pStr[i])
			len++;
		else
			break;
	}


	int size; 	//全排列个数
	for (size=1,i = 1; i < len+1; ++i)
		size *= i;


	char *out_temp; 	//新建长字符串
	out_temp = (char*) malloc( sizeof(char) * (len+1) * size );

    Permutation(pStr, pStr, out_temp); 
    // printf("%s",out_temp ); 
    return out_temp;

}

char* Permutation(char* pStr, char* pBegin, char* pPrint)  
{  
	/*
	修改自
	http://blog.csdn.net/fanzitao/article/details/7879027
	http://blog.chinaunix.net/uid-12947273-id-2910156.html
	把printf修改成了输出至pPrint
	*/
    if(!pStr || !pBegin)  
        return NULL;  
      
    if(*pBegin == '\0')  
    {  
    	char *t = pStr;
    	while(*t!='\0')
    	{
    		*pPrint = *t;
    		pPrint++;
    		t++;
    	}
    	*pPrint = '\n';
    	pPrint++;
        // printf("%s\n", pStr);  
    }  
    else  
    {  
    	char* pCh;
        for( pCh = pBegin; *pCh != '\0'; ++ pCh)  
        {  
            // swap pCh and pBegin  
            char temp = *pCh;  
            *pCh = *pBegin;  
            *pBegin = temp;  
              
            pPrint = Permutation(pStr, pBegin + 1, pPrint);    
            // restore pCh and pBegin  
            temp = *pCh;  
            *pCh = *pBegin;  
            *pBegin = temp;  
        }  
    }  
    return pPrint;
} 



int pop(char stack[], int *top, char *out)
{
	if (*top == -1)
		return 0;
	else
	{
		*out = stack[(*top)--];
		return 1;
	}
}

int push(char stack[], int len, int *top, char in)
{
	if (*top >= len-1)
		return 0;
	else
	{
		stack[++(*top)] = in;
		return 1;
	}
}

int isValid_Pop(char pop_conseq[], char push_queue[])
{
	/*
	入栈顺序为push_queue
	出栈结果为pop_conseq
	通过真实入栈判断出栈结果是否可行
	一、重复入栈，直到栈顶元素和题目中下一个出栈元素相同
	二、若相同，出栈
	重复一、二两步
	*/
	int i;
	int len = 0;
	for ( i = 0; i < 1000; ++i)
	{
		if (push_queue[i])
			len++;
		else
			break;
	}

	char temp;
	char *test_stack;
	test_stack = (char*) malloc(sizeof(char)*(len));
	int top = -1;

	int next_push = 0;	//下一个入栈序号
	int next_queue = 0;	//下一个判断的出栈结果序号
	int times = 0;//进出栈一共2*len次
	for ( ; times<(2*len); ++times)
	{
		if(top==-1 || test_stack[top]!=pop_conseq[next_queue])	//当前栈不符合出栈条件
		{
			//继续入栈
			if (next_push >= len)	//没有可入栈的
				return 0;
			push(test_stack, len, &top, push_queue[next_push++]);

		}
		else 
		{
			//栈顶元素和下一个需要出战的元素相同，出栈
			pop(test_stack, &top, &temp);
			next_queue++;
			if (next_queue >= len)
			{
				return 1;	//所有元素出入栈完毕
			}

		}

	}
	return -1;	//正常情况跳出for循环之前都会return
}




int main(int argc, char const *argv[])
{
	int n = 4;	//共n
	char push_queue[] = {'A','B','C','D','\0'};

	int i,j;
	// int size = 1;
	// for (i = 1; i < n+1; ++i)
	// 	size *= i;

	char pop_conseq[24][5];
	char *line;
	line = permutation(push_queue);
	for ( i = 0; i < 24; ++i)
	{
		for ( j = 0; j < n; ++j)
		{
			pop_conseq[i][j] = line[ (n+1)*i + j ];
		}
		pop_conseq[i][n] = '\0';
	}

	printf("All possible sequences:\n");
	for ( i = 0; i < 24; ++i)
	{
		for ( j = 0; j < 4; ++j)
		{
			printf("%c", pop_conseq[i][j]);
		}
		printf("\n");
	}
	printf("*************************\n");



	printf("Invalid sequences:\n");
	int result;
	for ( i = 0; i < 24; ++i)
	{

		result = isValid_Pop(pop_conseq[i], push_queue);
		if (!result)
		{
			puts(pop_conseq[i]);
		}
	}



	// int (*p)[10];
	// p=(int(*)[10])malloc(sizeof(int)*20);

	
	

	return 0;
}

// int main(int argc, char const *argv[])
// {
// 	char consq[] = "DABC";
// 	char push_queue[] = "ABCD";
// 	int result;
// 	result = isValid_Pop(consq, push_queue);
// 	printf("%d\n",result );
// 	return 0;
// }
