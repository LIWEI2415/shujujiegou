#include <stdio.h>
#include <stdlib.h>
/////////////////////////////////////////////////约瑟夫环///////////////////////////////////////////
#define SpaceSize 100
struct Aode
{
    int Element;
	int Previous;
    int Next;
};
struct Aode CursorSpace[ SpaceSize ];
void Start()
{
	int i;
	for(i=0;i<SpaceSize;i++)
	{
		CursorSpace[i].Element=-1;
		CursorSpace[i].Previous=-1;
		CursorSpace[i].Next=-1;
	}
}
void InitCursorSpace(int n)
{
    int i;
    for(i = 0; i < n; i++)
	{
        CursorSpace[i].Next = i==n-1?0:i+1;
		CursorSpace[i].Previous= i==0?n-1:i-1;
		CursorSpace[i].Element=i;
	}
}
void Josephus(int n,int m)
{
	Start();
	InitCursorSpace(n);
	int i=0;
	while(CursorSpace[i].Next!=CursorSpace[i].Element)
	{
		for(int j=0;j<m-1;j++)
		{
			i=CursorSpace[i].Next;
		}
		printf("delete number %d\n",i);
	    CursorSpace[CursorSpace[i].Next].Previous=CursorSpace[i].Previous;
	    CursorSpace[CursorSpace[i].Previous].Next=CursorSpace[CursorSpace[CursorSpace[i].Previous].Next].Next;
	    i=CursorSpace[CursorSpace[i].Previous].Next;
	}
	printf("the saved number %d",CursorSpace[i].Element);
}
/////////////////////////////////////////////////////多项式相乘/////////////////////////////////////////////
typedef struct term
{
	int coef;
	int	expn;
}ElemType;
typedef struct node
{
	ElemType data;
	struct node *next;
}Node;
void CreatPolyn( Node *P, int m )
{	
    int i;
	Node *current;
	Node *pre;
 	printf( "create a new polynomial:\n" );
	P->next = NULL;
	pre = P;
 	for( i = 0; i < m; i++ )
	{
		current = ( Node * )malloc( sizeof( Node ) );
		current->next = NULL;
		printf("please input two numbers with the follow format:int,int\n");
		scanf( "%d,%d",&( current->data.coef ),&( current->data.expn) );
		if( i == 0 )
			P->next = current;
		else
			pre->next = current;
		if( pre->data.expn == current->data.expn)
		{
			printf( "ERROR:the expn of two elements couldn't be the same\n");
			exit( EXIT_FAILURE );
		}
		pre = current;
	}
}
int PolynLength( Node * P )
{
	int count = 0;
	Node *current;
 	current = P->next;
	while( current != NULL )
	{
		current = current->next;
		count++;
	}
	return count;
} 
void Increase( Node *P1)
{
	Node *current;
	Node *nex;
	Node *pre;
	int count = PolynLength( P1 );
	int i,j;
 	for( i = 1; i < count; i++ )
	{
		current = P1->next;
		pre = P1->next;
		for( j = 0; j < count - i; j++ )
		{
			nex = current->next;
			if( current->data.expn > nex->data.expn )
			{
				current->next = nex->next;
				nex->next= current;
				if( current ==  P1->next )
				{
					P1->next = nex;
					pre = P1->next;
				}
				else
				{
					pre->next = nex;
					pre = pre->next;
				} 			
			}			
			else
			{
				pre = current;
				current = nex;
			}
		}
	}
}
void AddPolyn( Node *P1, Node *P2 )
{
 	Node *current1;
 	Node *current2;
 	Node *pre;
	Increase( P1 );
	Increase( P2 );
 	current1 = P1->next;
	current2 = P2->next;
	pre = P1;
 	while( current1 && current2 )
	{         
        if( current1->data.expn < current2->data.expn )
		{  
        	if( current1 == P1->next && current2 == P2->next )
			{ 
			    P1->next = current1;							   
			}															
			else
			{													
        		pre->next = current1;											
			}
			pre = current1;                 
			current1 = current1->next;     
			}		
			else if
			( 
			    current1->data.expn == current2->data.expn )
				{  
    				current1->data.coef += current2->data.coef;  
					if( current1 == P1->next && current2 == P2->next )
					{  
        				P1->next = current1;			
					}			
					else
					{												
				        pre->next = current1;			
					}			
					pre = current1;						
					current1 = current1->next;			
					current2 = current2->next;			
				}		
				else
				{									
        			if( current2 == P2->next && current1 == P1->next)
					{ 
        				P1->next = current2;							
					}			
					else
					{												
        				pre->next = current2;
					}			
					pre = current2;										
					current2 = current2->next;							
				}	
	} 	
	if( current1 )					
	    pre->next = current1;
    else							
		pre->next = current2;
	P2->next = NULL;             
}

void MultiplyPolyn( Node *P1, Node *P2 )
{
	Node *current1; 
	Node *current2; 	
	Node *temp;
	Node *current;
	Node *pre;
	current1 = P1->next;
	current2 = P2->next;
	temp = ( Node *)malloc( sizeof( Node ) );
	temp->next = NULL;
	for( ; current1 != NULL; current1 = current1->next )
	{      
		for( current2 = P2->next; current2 != NULL; current2 = current2->next )
		{
			current = ( Node *)malloc( sizeof( Node ) );					//创建一个新的多项式结点
			current->data.coef = current1->data.coef * current2->data.coef; //给该结点赋值，
			current->data.expn = current1->data.expn + current2->data.expn;
			current->next = NULL;
			if( current2 == P2->next )
			{
				if( current1 == P1->next )
				{
					pre = P1;
					P1->next = current;
				}
				else
				{
					pre = temp;
					temp->next = current;
				}
			}
			else{
				pre->next = current;
			}
			pre = current;
		}
		if( temp->next != NULL );
			AddPolyn( P1, temp );
	}
	temp->next = NULL;
	P2->next = NULL;
}
void PrintPolyn( Node *P )
{	
    Node *current;
	current = P->next;
	while( current != NULL )
	{		
        printf( "%5d,%5d\n", current->data.coef,current->data.expn );
		current = current->next;
	}
}
////////////////////////////////////////////////////主函数////////////////////////////////////////
int main()
{
	//Josephus(5,3);
	Node *polyn1;
	Node head1;
	Node *polyn2;
	Node head2;
	polyn1 = &head1;
	polyn2 = &head2;
	CreatPolyn( polyn1, 4 );
	CreatPolyn( polyn2, 4 );
	MultiplyPolyn( polyn1, polyn2);
	PrintPolyn( polyn1 );
}
