#include<stdio.h>
#include<cstdlib>
#include <time.h>
#include<cstring>
#define Max_len 2
///////////////////////////////////////////桶排////////////////////////////////////////
// 打印结果
void Show(int  arr[], int n)
{
    int i;
    for ( i=0; i<n; i++ )
        printf("%d  ", arr[i]);
    printf("\n");
}
int GetMaxVal(int* arr, int len)
{
    int maxVal = arr[0]; //假设最大为arr[0]
    for(int i = 1; i < len; i++)  //遍历比较，找到大的就赋值给maxVal
    {
        if(arr[i] > maxVal)
            maxVal = arr[i];
    }
    return maxVal;  //返回最大值
}
void BucketSort(int* arr , int len)
{
    int tmpArrLen = GetMaxVal(arr , len) + 1;
    int tmpArr[tmpArrLen];  //获得空桶大小
    int i, j;
    for( i = 0; i < tmpArrLen; i++)  //空桶初始化
        tmpArr[i] = 0;
    for(i = 0; i < len; i++)   //寻访序列，并且把项目一个一个放到对应的桶子去。
        tmpArr[ arr[i] ]++;
    for(i = 0, j = 0; i < tmpArrLen; i ++)
    {
        while( tmpArr[ i ] != 0) //对每个不是空的桶子进行排序。
        {
            arr[j ] = i;  //从不是空的桶子里把项目再放回原来的序列中。
            j++;
            tmpArr[i]--;
        }
    }
}
////////////////////////////////////////基数排序//////////////////////////////////////
#define Max_ 10      //数组个数
#define RADIX_10 10    //整形排序
#define KEYNUM_31 10     //关键字个数，这里为整形位数
// 找到num的从低到高的第pos位的数据
int GetNumInPos(int num,int pos)
{
	int temp = 1;
	for (int i = 0; i < pos - 1; i++)
		temp *= 10;
	return (num / temp) % 10;
}
//基数排序  pDataArray 无序数组；iDataNum为无序数据个数
void RadixSort(int* pDataArray, int iDataNum)
{
	int *radixArrays[RADIX_10];    //分别为0~9的序列空间
	for (int i = 0; i < 10; i++)
	{
		radixArrays[i] = (int *)malloc(sizeof(int) * (iDataNum + 1));
		radixArrays[i][0] = 0;    //index为0处记录这组数据的个数
	}
	for (int pos = 1; pos <= KEYNUM_31; pos++)    //从个位开始到31位
	{
		for (int i = 0; i < iDataNum; i++)    //分配过程
		{
			int num = GetNumInPos(pDataArray[i], pos);
			int index = ++radixArrays[num][0];
			radixArrays[num][index] = pDataArray[i];
		}
		for (int i = 0, j =0; i < RADIX_10; i++)    //收集
		{
			for (int k = 1; k <= radixArrays[i][0]; k++)
				pDataArray[j++] = radixArrays[i][k];
			radixArrays[i][0] = 0;    //复位
		}
	}
}
///////////////////////////////////////////中缀变后缀//////////////////////////////////
typedef struct node
{    
    char s[310];
    int top;
}Stack;
int weight(char ch, int flag)
{    
    if(ch=='+'||ch=='-')
		return 1;
    if(ch=='*'||ch=='/')
		return 2;
    if(ch=='('&&flag==1)
		return 0;
    if(ch=='('&&flag==0) return 3;
}
void transform(char str[])
{
	Stack a;
	a.top=-1;
	int i,f=0,m=strlen(str);
	for(i=0;i<m;i++)
		{
			if(str[i]>='A'&&str[i]<'Z')
			{
				printf("%c",str[i]);
			}
			else
			{
				if(a.top==-1)
				{ 
        			a.s[++a.top]=str[i];
					continue;
				}          
				if(str[i]==')')
				{
					while(a.top!=-1&&a.s[a.top]!='(')             
                        printf("%c",a.s[a.top--]);
					--a.top;
					continue;
				}
				if(weight(str[i],0)>weight(a.s[a.top],1))
				{
					a.s[++a.top]=str[i];
					continue;
				} 
				while(a.top!=-1&&weight(str[i],0)<=weight(a.s[a.top],1))     
				{
		            printf("%c",a.s[a.top]);
	                --a.top;                                       
					f=1;                                            
				}          
				if(f==1)
				{
					a.s[++a.top]=str[i];
					f=0;
				}
			}  
		}
		while(a.top!=-1)
		{
			printf("%c",a.s[a.top--]);
		}
}

int main()
{   
    clock_t start_time, end_time;
	double time;
    start_time=clock();
    //测试数据
    int arr_test[Max_len] = {1,10000};
	//int arr_test[Max_len] = { 8, 4, 2, 3, 5, 1, 6, 9, 0, 7 };
    //排序前数组序列
    Show( arr_test, Max_len );
    //排序
	//RadixSort( arr_test, Max_);
	for(int i=1;i<=100000;i++)
        BucketSort( arr_test,  Max_len);
    //排序后数组序列
    Show( arr_test, Max_len );
	end_time=clock();
	time=(double)(end_time - start_time)/CLOCKS_PER_SEC;
	printf ("%f\n", time); 
    return 0;
}
