/*
	多项式加法、减法、乘法
*/

#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define OVERFLOW -2

typedef int Status;
typedef struct ElemType
{
	float coef;		//系数
	int expn;		//指数
	struct ElemType *prior;
	struct ElemType *next;
} ElemType, *polynomial;

void MakeNode(ElemType *S, ElemType e)
{
	S = (polynomial)malloc(sizeof(ElemType));
	if (!S)
		exit(OVERFLOW);
	S->coef = e.coef;
	S->expn = e.expn;
	S->prior = NULL;
	S->next = NULL;
}

Status compare(int a, int b)
{
	if (a == b)
		return 1;
	else
		return 0;
}

Status LocatePolyn(polynomial P, ElemType e, Status (*compare)(int, int))
{
	polynomial q = P->next;
	if (q == NULL)
		return 0;
	while (q)
	{
		if ((*compare)(q->expn, e.expn) == 1)
			return q->expn + 1;
	}
	return 0;
}

void Insert(polynomial P, polynomial S)
{
	polynomial q = P->next;
	if (q == NULL)
	{
		P->next = S;
		return;
	}
	while (q->expn < S->expn && q->next != NULL)
	{
		q = q->next;
	}
	if (q->next == NULL && q->expn < S->expn)
	{
		q->next = S;
		S->prior = q;
	}
	else
	{
		S->next = q;
		q->prior->next = S;
		S->prior = q->prior;
	}
	
}

void CreatePolyn(ElemType *P, int m)
{
	//输入 m 项的系数和指数，建立表示一元多项式的有序链表 P
	P = (polynomial)malloc(sizeof(ElemType));
	if (!P)
		exit(OVERFLOW);
	polynomial head = P;
	polynomial S;
	head->coef = 0.0, head->expn = -1, head->next = NULL;
	ElemType e;
	int i;
	for (i = 1; i <= m; i++)
	{
		scanf("%f %d", &e.coef, &e.expn);
		if(!LocatePolyn(P, e, (*compare)))
		{
			MakeNode(S, e);
			Insert(P, S);
		}
	}
}

void PrintPolyn(polynomial P, int n)
{
	int i;
	polynomial q = P;
	for (i = 1; i <= n; i++)
	{
		q = q->next;
	}
	printf("(%d, %d)", q->coef, q->expn);
}

void Traverse(polynomial P)
{
	polynomial q = P->next;
	while (q)
	{
		printf("(%d, %d)", q->coef, q->expn);
		q = q->next;
	}
}

int main()
{
	polynomial P;
	printf("Create Polynomial:\n");
	CreatePolyn(P, 3);
	Traverse(P);
	
}


