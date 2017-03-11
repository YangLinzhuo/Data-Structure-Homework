/*
	双向链表
*/

#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;

typedef struct DuLNode
{
	ElemType data;
	struct DuLNode *prior;
	struct DuLNode *next;
	int freq;
}DuLNode, *DuLinkList;

typedef struct LinkList
{
	DuLinkList Head, Tail;
	int length;
} LinkList;

Status Init_DuLLinkList(LinkList &L)	//创建头结点
{
	L.Head = L.Tail = NULL;
	L.length = 0;
	return OK;
}

Status Make_Node(DuLinkList &N, ElemType e)	//创建值为 e 的一个结点
{
	N = (DuLinkList)malloc(sizeof(DuLNode));
	if (!N)
		return ERROR;
	N->data = e;
	N->prior = N->next = NULL;
	N->freq = 0;
	return OK;
}

Status Insert_Node(LinkList &L, DuLinkList &N)	//将结点 N 插入到尾节点之后
{
	if (L->length == 0)
	{
		L->Head = L->Tail = N;
		L->length++;
		N->prior = N->next = N;
	}
	else
	{
		N->prior = L->Tail;
		N->next = L->Head;
		L->Head->prior = N;
		L->Tail->next = N;
		L->Tail = N;
		L->length++;
	}
	return OK;
}

void Freq_Sort(LinkList &L, DuLinkList &p)
{
	DuLinkList q, r;
	q = L->Head;
	r = L->Tail;
	while (p->freq < q->freq && q != p)
	{
		q = q->next;
	}
	if (q == p)
		return;
	else
	{
		p->prior = q->prior;
		p->next = q;
		q->prior = p;
	}
	return;
}

Status Locate(LinkList &L, ElemType e)	//访问数据值为 e 的结点
{
	DuLinkList p,q;
	p = L->Head;
	q = L->Tail;
	while (p->data != e && p != q)
	{
		p = p->next;
	}
	if (p->data != e)
		return ERROR;
	else
	{
		p->freq++;
		Freq_Sort(L, p);
		return OK;
	}
}

