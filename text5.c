#include<stdio.h>
#include<malloc.h>
struct TreeNode;
struct QueueRecord;
typedef struct QueueRecord* Queue;
typedef struct TreeNode* SearchTree;
SearchTree CreateTree1(char* pre,char* in);
void PostOrder(SearchTree T);
int IsFull(Queue Q);
void MakeEmpty(Queue Q);
static int Succ(int Value,Queue Q);
void Enqueue(int x,Queue Q);
struct TreeNode
{
	char Element;
	SearchTree Left;
	SearchTree Right;
};
struct QueueRecord
{
	int Capacity=100;
	int Front;
	int Rear;
	int Size;
	int* Array;
};
SearchTree CreateTree1(char* pre,char* in)
{
	int num_pre=0,num_in=0;
	num_pre=sizeof(pre);
	num_in=sizeof(in);
	if(num_pre==0||num_in==0)
		return NULL;
	SearchTree T=(SearchTree)malloc(sizeof(TreeNode));
	T->Element=pre[0];
	int index=0;
	for(int i=0;i<(int)sizeof(in);i++)
	{
		if(in[i]==T->Element)
			index=i;
	}
	char left_pre[index],right_pre[num_pre-index-1],left_in[index],right_in[num_in-index-1];
	for(int i=0;i<index;i++)
	{
		left_pre[i]=pre[i+1];//根节点左子树的前序遍历
		left_in[i]=in[i];//根节点左子树的中序遍历
	}
	for(int i=index+1;i<num_pre;i++)
	{
		right_pre[i]=pre[i];//根节点右子树的前序遍历
		right_in[i]=in[i];//根节点右子树的中序遍历
	}
	T->Left=CreateTree1(left_pre,left_in);
	T->Right=CreateTree1(right_pre,right_in);
	return T;
}
//判断数组是否已满
int IsFull(Queue Q)
{
	return Q->Size==Q->Capacity;
}
void MakeEmpty(Queue Q)
{
	Q->Size=0;
	Q->Front=1;
	Q->Rear=0;
}
//判断是否到达数组末尾
static int Succ(int Value,Queue Q)
{
	if(++Value==Q->Capacity)
		Value=0;
	return Value;
}
//入对操作
void Enqueue(int x,Queue Q)
{
	if(IsFull(Q))
		printf("Full queue!!!");
	else
	{
		Q->Size++;
		Q->Rear=Succ(Q->Rear,Q);
		Q->Array[Q->Rear]=x;
	}
}
void preOrder(SearchTree T,Queue Q)
{
	if(T)
	{
		Enqueue(T->Element,Q);
		PostOrder(T->Left);
		PostOrder(T->Right);
	}
}