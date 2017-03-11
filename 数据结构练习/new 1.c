#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 100
#define INCREMENT_SIZE 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status
typedef int ElemType
typedef struct
{
	ElemType *Basic_Address;
	int size;
	int length;
} SqList;

Status InitList(SqList *L)
{
	L->Basic_Address = (ElemType *)malloc(INIT_SIZE * sizeof(ElemType));
	if(!L->Basic_Address)
		return ERROR;
	L->size = INIT_SIZE;
	L->length = 0;
	return OK;
}

Status DestroyList(SqList *L)
{
	free(L->Basic_Address);
	L->Basic_Address = NULL;
	L->size = 0;
	L->length = 0;
	return OK;
}

Status ClearList(SqList *L)
{
	
	if(DestroyList(L))
		if(InitList(L))
			return OK;
	return ERROR;
}

Status ListEmpty(SqList L)
{
	if(L.length == 0)
		return TRUE;
	else
		return FALSE;
}

Status ListLength(SqList L)
{
	return L.length;
}

Status GetElem(SqList L, int i, ElemType *e)
{
	if (i < 1 || i > ListLength(L))
		return ERROR;
	*e = *(Basic_Address + i - 1);
	return OK;
}

Status LocateElem(SqList L, ElemType e, (* compare)(ElemType, ElemType))
{
	int i = 1;
	int length = ListLength(L);
	for (; i <= length; i++)
	{
		if ((* compare)(e, *(Basic_Address + i - 1)))
			return i;
	}
	return 0;
}

Status PriorElem(SqList L, ElemType cur_e, ElemType *pre_e)
{
	int location;
	location = LocateElem(L, cur_e, (* compare)(ElemType, ElemType));
	if (location != 0 && location != 1)
	{
		*(pre_e) = *(Basic_Address + location - 2);
		return OK;
	}
	else
		return ERROR;
}

Status NextElem(SqList L, ElemType cur_e, ElemType *next_e)
{
	int location;
	location = LocateElem(L, cur_e, (* compare)(ElemType, ElemType));
	if (location != 0 && location != ListLength(L))
	{
		*(next_e) = *(Basic_Address + location);
		return OK;
	}
	else
		return ERROR;
}

Status ListInsert(SqList *L, int i, ElemType e)
{
	ElemType *new, *p, *q;
	if (i < 1 || i > ListLength(L) + 1)
		return ERROR;
	if (L->length >= L-size)
	{
			new = (ElemType *)realloc(Basic_Address, (L->size + INCREMENT_SIZE) * sizeof(ElemType));
			if (!new)
				return ERROR;
			L->Basic_Address = new;
			L->size += INCREMENT_SIZE;
	}
	p = L->Basic_Address + i - 1;
	q = L->Basic_Address + L->length - 1;
	while (q >= p)
	{
		*(q + 1) = *q;
		q--;
	}
	*p = e;
	L->length++;
	return OK;
}

Status ListDelete(SqList *L, int i, ElemType *e)
{
	ElemType *p, *q;
	if (i < 1 || i > ListLength(L))
		return ERROR;
	p = L->Basic_Address + i - 1;
	q = L->Basic_Address + L->length - 1;
	while (p <= q)
	{
		*p = *(p + 1);
		p++;
	}
	L->length--;
	return OK;
}

void visit(int e)
{
	printf("%d ", e);
}

Status ListTraverse(SqList L, (* visit)(ElemType))
{
	int length = ListLength(L);
	int i = 0;
	for (i = 1; i <= length; i++)
	{
		visit(L.Basic_Address + i - 1);
	}
	return OK;
}