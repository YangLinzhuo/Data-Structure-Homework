/*
	求两个集合的交集
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