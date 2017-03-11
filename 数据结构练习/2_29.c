/*
	删去元素
*/

#define OK 1
#define ERROR 0
#define INIT_SIZE 100
#define INCREMENT_SIZE 10
typedef int Status;
typedef int ElemType;

Status Merge(SqList A, SqList B, SqList *C)
{
	ElemType a, b;
	int aLength, bLength;
	aLength = ListLength(A), bLength = ListLength(B);
	int i, j, k;
	for (i = 1, j = 1, k = 1; i <= aLength && b <= bLength;)
	{
		GetElem(A, i, &a), GetElem(B, j, &b);
		if (a < b)
			i++;
		else if (a > b)
			j++;
		else
		{
			ListInsert(C, k, a);
			k++;
		}
	}
	return OK;
}

Status nDelete(SqList *L, int i, int num)
{
	ElemType *p, *q;
	if (i < 1 || i > ListLength(*L) || num < 0 || i + num > ListLength(*L) + 1)
		return ERROR;
	p = &(*L)[i];
	q = &(*L)[i + num - 1];
	int j = i;
	while (p <= q && j + num <= ListLength(*L))
	{
		*p = (*L)[j + num];
		p++;
		j++;
	}
	L->length -= num;
	return OK;
}

int Check(SqList L, int i)	//检查从第i个起有多少个重复元素
{
	ElemType elem, a;
	int temp = i;
	GetElem(L, temp++, &a);
	GetElem(L, temp, &elem);
	while (elem == a)
	{
		temp++;
		GetElem(*L, temp, &elem);
	}
	return temp - i - 1;
}

Status DeleteRe(SqList *L)//删除重复元素
{
	ElemType a, b;
	int i = 1;
	int length = ListLength(*L);
	while (i <= length)
	{
		GetElem(*L, i, &a), GetElem(*L, i + 1; &b);
		if (a != b)
		{
			i++;
		}
		else
		{
			int temp = i;
			temp = Check(*L, temp);
			nDelete(L, i + 1, temp - 1);
			i += temp;
		}
	}
	return OK;
}

Status Delete(SqList *A, SqList B, SqList C)
{
	SqList temp;
	Merge(B, C, &temp);
	Delete(&temp);
	int a, b;
	int i, j;
	int aLength = ListLength(*A);
	int tempLength = ListLength(temp);
	for (i = 1, j = 1; i <= aLength && j < tempLengthp;)
	{
		GetElem(*A, i, &a), GetElem(temp, j, &b);
		if (a == b)
		{
			int count; 
			count = Check(*A, i);
			nDelete(A, i, count);
			i += count;
			j++;
		}
		else if (a > b)
			j++;
		else
			i++;
	}
	return OK;
}