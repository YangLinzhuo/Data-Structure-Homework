#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;

/*存储结构*/
typedef struct LNode
{
	float coef;
	int expn;
	struct LNode* next;
}LNode;			//定义LNode 数据类型  

typedef struct LNode* LNodePtr;
typedef LNodePtr *LinkList;

typedef struct polynomial
{
	LNodePtr head;
	int length;
}polynomial;

Status InitList(polynomial *P)
{
	(*P).head = (LNodePtr)malloc(sizeof(LNode));
	if (!P)
		exit(OVERFLOW);
	(*P).head->coef = 0.0;
	(*P).head->expn = -1;
	(*P).head->next = NULL;
	(*P).length = 0;
	return OK;
}

int compare(LNodePtr a, LNodePtr b)
{
	if (a->expn == b->expn)
		return 0;
	else if (a->expn < b->expn)
		return -1;
	else
		return 1;
}

Status LocateElem(polynomial P, LNodePtr e, LNodePtr location, int (*compare)(LNodePtr, LNodePtr))
{
	LNodePtr q = P.head;
	if (P.length == 0)
		return FALSE;
	while (q->next)
	{
		if (!compare(q->next, e))
		{
			location = q->next;
			return TRUE;
		}
		q = q->next;
	}

	return FALSE;
}

Status MakeNode(LinkList S, LNode e)
{
	*S = (LNodePtr)malloc(sizeof(LNode));
	if (!S)
		exit(OVERFLOW);
	(*S)->coef = e.coef;
	(*S)->expn = e.expn;
	(*S)->next = NULL;
	return OK;
}

Status OrderInsert(polynomial *P, LNodePtr e, int (*compare)(LNodePtr, LNodePtr))
{
	LNodePtr q = (*P).head;
	if ((*P).length == 0)
	{
		q->next = e;
		(*P).length++;
		return OK;
	}
	
	while (q->next)
	{
		if (compare(q->next, e) >= 0)
		{
			e->next = q->next;
			q->next = e;
			(*P).length++;
			return OK;
		}
		q = q->next;
	}
	
	q->next = e;
	(*P).length++;
	return OK;
}

Status CreatePolyn(polynomial *P, int m)
{
	int i;
	LNode e, *location, *New;
	for (i = 1; i <= m; i++)
	{
		scanf("%f %d", &e.coef, &e.expn);
		if (!LocateElem(*P, &e, location, (*compare)))
		{
			if(MakeNode(&New, e))
			{
				OrderInsert(P, New, (*compare));
			}
		}
	}
	return OK;
}

void PrintPolyn(polynomial P)
{
	LNodePtr lp = (P.head)->next;
	while (lp)
	{
		if (lp->expn == 0)
		{
			if (lp->coef > 0)
			{
				printf("+%.2f",lp->coef);
			}
			else
			{
				printf("%.2fx",lp->coef);
			}
		}
		else if (lp->expn == 1)
		{
			if (lp->coef > 0)
			{
				printf("+%.2fx",lp->coef);
			}
			else
			{
				printf("%.2fx",lp->coef);
			}
		}
		else
		{
			if (lp->coef > 0)
			{
				printf("+%.2fx^%d",lp->coef, lp->expn);
			}
			else
			{
				printf("%.2fx^%d",lp->coef, lp->expn);
			}
		}
		lp = lp->next;
	}
}


void AddPolyn(polynomial *Pa, polynomial *Pb)
{
	LNodePtr lpa = (*Pa).head->next;
	LNodePtr lpb = (*Pb).head->next;
	LNodePtr lpa_pre, lpb_pre;
	lpa_pre = (*Pa).head;
	lpb_pre = (*Pb).head;
	int sum_coef;
	while (lpa && lpb)
	{
		switch((*compare)(lpa, lpb))
		{
			case 0:
				sum_coef = lpa->coef + lpb->coef;
				if (sum_coef != 0.0)
				{
					lpa->coef = sum_coef;
					lpa_pre = lpa;
					lpa = lpa->next;
				}
				else
				{
					lpa_pre->next = lpa->next;
					free(lpa);
					lpa = lpa_pre->next;
				}
				lpb_pre->next = lpb->next;
				free(lpb);
				lpb = lpb_pre->next;
				break;
			case -1:
				lpa_pre = lpa;
				lpa = lpa->next;
				break;
			case 1:
				lpa_pre = lpb;
				lpb = lpb->next;
				lpb_pre->next->next = lpa;
				lpb_pre->next = lpb;
				break;
		}
	}
	if (lpb)
	{
		lpa_pre->next = lpb;
	}
	free((*Pb).head);
}

void SubstractPolyn(polynomial *Pa, polynomial *Pb)
{
	LNodePtr lpa = (*Pa).head->next;
	LNodePtr lpb = (*Pb).head->next;
	LNodePtr lpa_pre, lpb_pre;
	lpa_pre = (*Pa).head;
	lpb_pre = (*Pb).head;
	int sum_coef;
	while (lpa && lpb)
	{
		switch((*compare)(lpa, lpb))
		{
			case 0:
				sum_coef = lpa->coef - lpb->coef;
				if (sum_coef != 0.0)
				{
					lpa->coef = sum_coef;
					lpa_pre = lpa;
					lpa = lpa->next;
				}
				else
				{
					lpa_pre->next = lpa->next;
					free(lpa);
					lpa = lpa_pre->next;
				}
				lpb_pre->next = lpb->next;
				free(lpb);
				lpb = lpb_pre->next;
				break;
			case -1:
				lpa_pre = lpa;
				lpa = lpa->next;
				break;
			case 1:
				lpb->coef = -(lpb->coef);
				lpa_pre = lpb;
				lpb = lpb->next;
				lpb_pre->next->next = lpa;
				lpb_pre->next = lpb;
				break;
		}
	}
	if (lpb)
	{
		lpa_pre->next = lpb;
	}
	while (lpb)
	{
		lpb->coef = -(lpb->coef);
		lpb = lpb->next;
	}
	free((*Pb).head);
}

void MultiplyPolyn(polynomial *Pa, polynomial *Pb, polynomial *P)
{
	polynomial B;
	LNode e;
	LNodePtr S;
	LNodePtr lpa;
	LNodePtr lpb = (*Pb).head->next;
	while (lpb)
	{
		InitList(&B);
		lpa = (*Pa).head->next;
		while (lpa)
		{
			e.coef = (lpb->coef) * (lpa->coef);
			e.expn = (lpb->expn) + (lpa->expn);
			MakeNode(&S, e);
			OrderInsert(&B, S, (*compare));
			lpa = lpa->next;
		}
		AddPolyn(P, &B);
		lpb = lpb->next;
	}
}

int main()
{
	polynomial Pa, Pb, result;
	int num1, num2;
	char operator;
	InitList(&Pa);
	InitList(&Pb);
	InitList(&result);
	printf("Please enter the number of first polynomial's Nodes:\n");
	scanf("%d", &num1);
	CreatePolyn(&Pa,num1);
	getchar();
	printf("Please entern the operator:\n");
	scanf("%c", &operator);
	printf("Please enter the number of second polynomial's Nodes:\n");
	scanf("%d", &num2);
	CreatePolyn(&Pb,num2);
	printf("\n\n");
	switch(operator)
	{
		case '+':
			AddPolyn(&Pa, &Pb);
			PrintPolyn(Pa);
			break;
		case '-':
			SubstractPolyn(&Pa, &Pb);
			PrintPolyn(Pa);
			break;
		case '*':
			MultiplyPolyn(&Pa, &Pb, &result);
			PrintPolyn(result);
			break;
	}
	return 0;
}
