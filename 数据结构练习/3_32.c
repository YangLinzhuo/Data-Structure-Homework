/*
 *		循环队列实现斐波那契数列
 */

#include <stdio.h>
#include <stdlib.h>

#define OVERFLOW -2
#define OK 1
#define ERROR 0

int MAXQSIZE;

typedef int Status;
typedef int QElemtype;
typedef struct
{
	QElemtype *base;	//初始化的动态分配存储空间
	int front;	//头指针，若队列不空，指向队列头元素
	int rear;	//尾指针，若队列不空，指向队列尾元素的下一个位置
} SqQueue;

Status InitQueue(SqQueue *Q)	//构造空队列 Q
{
	Q->base = (QElemtype*)malloc(sizeof(QElemtype) * MAXQSIZE);
	if (!(Q->base))
	{
		exit(OVERFLOW);
	}
	Q->front = Q->rear = 0;
	return OK;
}

int QueueLength(SqQueue Q)	//返回 Q 的元素个数，即队列的长度
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

Status EnQueue(SqQueue *Q, QElemtype e)	//插入元素 e 为 Q 的新的队尾元素
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)
	{
		return ERROR;		//队列已满
	}
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}

Status DeQueue(SqQueue *Q, QElemtype *e)	//若队列不空，则删除 Q 的队头元素，用 e 返回其值，并返回 OK；否则返回 ERROR
{
	if (Q->front == Q->rear)
	{
		return ERROR;
	}
	*e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}

void PrintQueue(SqQueue Q)
{
	int ptr = Q.front;
	while (ptr != Q.rear)
	{
		printf("%d ",Q.base[ptr]);
		ptr = (ptr + 1) % MAXQSIZE;
	}
}

int main()
{
	SqQueue Q;
	QElemtype e;
	int max;
	int k;	// k >= 2
	printf("Please enter the max:\n");
	scanf("%d",&max);
	printf("Please enter the k:\n");
	scanf("%d",&k);
	MAXQSIZE = k + 1;
	InitQueue(&Q);
	int F = 0;
	int i = 0;
	for (i = 0; i < k - 1; i++)		//前 k - 1 项置为 0
	{
		EnQueue(&Q, 0);
	}
	EnQueue(&Q, 1);		//第 k 项置为 1
	F = Q.base[(Q.rear - 1 + MAXQSIZE) % MAXQSIZE] + Q.base[(Q.rear - 2 + MAXQSIZE) % MAXQSIZE];
	while (F <= max)
	{
		DeQueue(&Q, &e);
		EnQueue(&Q, F);
		F = Q.base[(Q.rear - 1 + MAXQSIZE) % MAXQSIZE] + Q.base[(Q.rear - 2 + MAXQSIZE) % MAXQSIZE];
	}
	PrintQueue(Q);
	return 0;
}
