#include<stdio.h>
#include <time.h>
#define NO_MAJ_ELE -1
int power2 (int x, int n) 
{ 
    int t;
    if (0 == n) 
		return (1);
	if (0 == n % 2) 
		return (power2(x*x,n/2));
    return (power2(x*x,n/2)*x);
}
int power3 (int x, int n) 
{ 
    if (n == 0)
		return (1);
	if (n == 1)
		return (x);
	if (n == 2)
		return (x*x);
    if (n % 3 == 0)
		return (power3 (x*x*x, n/3));
	if (n %3 == 1)
		return (power3 (x*x*x, n/3)*x);
	return (power3 (x*x*x, n/3)*x*x);
}
static int majEle_recursive1 (int a[], int n) 
{
	int i, j , k = n/2;
	int tmp;
    if (n == 0)
		return (NO_MAJ_ELE);
    if (n == 1)
		return (a[0]);
    for (i = 0, j = 0; i < k; i++)
		{
			if (a[2*i] == a[2*i + 1])
				{
					tmp = a[j];
					a[j++] = a[2*i];
					a[2*i] = tmp; 
				}
		}
    tmp = majEle_recursive1 (a, j);
	if (n % 2 == 1)
		{
			if (tmp == NO_MAJ_ELE)
				return (a[n - 1]);
		}
    return (tmp);
}
static int majEle_recursive2 (int a[], int n)
{
	int i, count = 0;
	int tmp = NO_MAJ_ELE;
    for (i = 0; i < n; i++)
		{
			if (a[i] == tmp)
				count++;
			else if (count == 0)
				{
					tmp = a[i];
					count++;
				}
				else count--;
		}
    if (count == 0)
		return (NO_MAJ_ELE);
    return (tmp);
}
void panDuan(int n,int a[],int size)
{
	int num=0;
	for(int i=0;i<size;i++)
	{
		if(a[i]==n)
		{
			num++;
		}
	}
	if(size%2==0)
	{
		if(num>=size/2)
			printf("数组的主元为%d\n",n);
		else
			printf("数组无主元\n");
	}
	else
	{
		if(num>=size/2+1)
			printf("数组的主元为%d\n",n);
		else
			printf("数组无主元\n");
	}
}
	

int main()
{
	clock_t start_time, end_time;
	start_time=clock();
	int p;
	double time;
    int a[]={0,1,2,2,3,1,3,2};
	for(int i=0;i<1000000;i++)
	p=majEle_recursive2(a,8);
	panDuan(p,a,8);
	end_time=clock();
	time=(double)(end_time - start_time)/CLOCKS_PER_SEC;
	printf ("%f\n", time); 
	return 0;
}
