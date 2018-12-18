#include<stdio.h>
#include <time.h>
#include <stdlib.h>
int IntegerAdd(int n)
{
	if(n==0)/*判断输入的数字是否为零*/
	    return 0;
	if(n==1)/*判断输入的数字是否为1，并设置出口*/
        return 1;
    return(n+IntegerAdd(n-1));		
}
int Qie(int x)
{
	if(x==0)/*判断输入是否为0，并设置出口*/
	{
		return 1;
	}
	else
	{
		return(Qie(x-1)+x);
	}
}
void HanoiTower (int n, char source, char temp, char target)
{
	if (n < 1)
		return;
	if (1 == n)
	{ 
        printf ("%c->%c\n", source, target);
	    return;
	} 
	HanoiTower (n - 1, source, target, temp);
	printf ("%c->%c\n", source, target);
	HanoiTower (n - 1, temp, source, target);
    return;
}

int main()
{
	clock_t start_time, end_time;
	int n;
	double time;
    start_time=clock();
	for(int i=1;i<=1000000;i++)
	{
		n=Qie(900);
	}
	printf("%d\n",n);
	//HanoiTower(8,'a','b','c');
	end_time=clock();
	time=(double)(end_time - start_time)/CLOCKS_PER_SEC;
	printf ("%f\n", time); 
	return (0);
}