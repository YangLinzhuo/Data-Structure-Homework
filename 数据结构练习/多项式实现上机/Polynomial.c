/* 多项式链表存储 加、减、乘算法实现
 * Author: YangLinzhuo
 * Found Date: 2016/9/24
 * Update Date: None
 */
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status; 

typedef struct  //项的表示，多项式作为 Polynomial 的数据元素
{
    float coe;  //系数
    int exp;    //指数
    struct Term *prior, *next;
}Term;  

typedef Term *Link, *Position;

typedef struct  //链表类型
{
    Term *head, *tail;    //分别指向线性链表中的头结点和尾结点
    int length;     //指示线性链表中数据元素的个数
} Polynomial;

Status MakeNode (Link *ptr, Term el)	// 分配由 ptr 指向的值为 el 的结点，并返回 OK；分配失败则返回 ERROR
{
	(*ptr) = (Term *)malloc(sizeof(Term));
	if (!ptr)
		return ERROR;
	(*ptr)->coe = el.coe;
	(*ptr)->exp = el.exp;
	(*ptr)->prior = (*ptr)->next = NULL;
	return OK;
}

void FreeTerm(Term *ptr)	//释放 ptr 所指结点
{
	free(ptr);
	ptr = NULL;	
}

Status InitPolyn (Polynomial *P)	//构造一个空的多项式线性链表 P
{
	P = (Polynomial *)malloc(sizeof(Polynomial));
	if (!P)
		return ERROR;
	P->head = P->tail = NULL;
	P->length = 0;
	return OK;
}

Status DestroyPolyn(Polynomial *P)	//销毁多项式线性链表 P，P 不在存在
{
	if (!P)		
	{
		return ERROR;
	}
	Term *tmp;
	tmp = P->tail;
	while (P->tail != P->head && P->tail != NULL && P->head != NULL)	//从表尾向前删除，直到尾结点、头结点重合
	{
		P->tail = P->tail->prior;
		FreeTerm (&tmp);
		tmp = P->tail;
	}
	FreeTerm(&(P->head));
	FreeTerm(&(P->tail));	//删除头结点、尾结点
	free(P);	//删除链表结点
	tmp = NULL;
	return OK;
}

Status ClearPolyn(Polynomial *P)	//将多项式链表置为空表，释放原链表的结点空间
{
	if (!P)
	{
		return ERROR;
	}
	Term *tmp;
	tmp = P->tail;
	while (P->tail != P->head && P->tail != NULL && P->head != NULL)
	{
		P->tail = P->tail->prior;
		FreeTerm(&tmp);
		tmp = P->tail;
	}
	FreeTerm(&(P->tail));
	FreeTerm(&(P->head));
	tmp = NULL;
	return OK;
}

Status InsFirst(Term *head, Term *el)	//将结点 s 插入到头结点 head 之前
{
	if (head == NULL || el == NULL)
	{	
		return ERROR;
	}
	el->next = head;
	head->prior = el;
	head = el;
	return OK;
}

Status DelFirst(Term *head, Link *el)	//将头结点删去，用 el 返回
{
	if (head == NULL || el == NULL)
	{
		return ERROR;
	}
	Term *tmp = head->next;
	tmp->prior = NULL;
	(*el) = head;
	FreeTerm(head);
	head = tmp;
	return OK;
}

Status Append(Polynomial *P, Term *el)	//将 el 连接到 多项式链表的末尾，el 可能后接多个结点
{
	if (P == NULL || el == NULL)
	{
		return ERROR;
	}
	P->tail->next = el;
	Term *ptr = el;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	P->tail = ptr;
	return OK;
}



int main()
{
	return 0;
}
