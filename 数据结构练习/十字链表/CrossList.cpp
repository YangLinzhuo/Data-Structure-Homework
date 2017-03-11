#include <iostream>

using namespace std;

class OLNode
{
	public:
		int row;	//非零元行下标
		int col;	//非零元列下标
		int data;	//非零元的值
		OLNode *right;	//该非零元所在行表后继链域
		OLNode *down;	//该非零元所在列表后继链域
		OLNode ()
		{
			row = 0;
			col = 0;
			data = 0;
			right = 0;
			down = 0;
		}
};

typedef OLNode *OLink;

class  CrossList
{
	public:
		OLink *row_head;	//行链表头指针
		OLink *col_head;	//列链表头指针
		int row_num;		//矩阵行数
		int col_num;		//矩阵列数
		int not_zero_num;	//非零元个数
		CrossList ()
		{
			row_head = 0;
			col_head = 0;
			row_num = 0;
			col_num = 0;
			not_zero_num = 0;
		}
		bool Create();		//创建十字链表
		bool Insert(OLNode *);	//插入节点
		bool Delete(OLNode *);	//删除结点
		void Addition(CrossList);	//矩阵相加
};

bool CrossList::Create()
{
	cout << "Please enter the number of Row and Col:" << endl;
	cin >> row_num >> col_num;
	cout << "Please enter the number of not_zero element:" << endl;
	cin >> not_zero_num;
	row_head = new (row_num + 1) * OLink;
	col_head = new (col_num + 1) * OLink;
	for (int i = 0; i <= row_num; row_head[i] = 0, i++);
	for (int i = 0; i <= col_num; col_head[i] = 0, i++);	//指针置空
	for (int i = 1; i <= not_zero_num; i++)
	{
		OLNode *ptr = new OLNode;
		cout << "Please enter the row, col and data:" << endl;
		cin >> ptr->row >> ptr->col >> ptr->data;
		Insert(ptr);
	}
	return true;
}

void CrossList::Insert(OLNode *ptr)
{
	if (row_head[ptr->row] == 0 || row_head[ptr->row]->col > ptr->col)	//行为空或者行数在头指针所指元素之前
	{
		ptr->right = row_head[ptr->row];	//为空则 ptr->right 为空，否则 ptr->right 指向该行下一个元素
		row_head[ptr->row] = ptr;			//头指针指向 ptr
	}
	else	//否则寻找位置插入
	{
		OLNode *tmp = row_head[ptr->row];
		for (	; tmp->right && tmp->right->col < ptr->col; tmp = tmp->right);	//tmp 总是被比较元素的前指针
		ptr->right = tmp->right;
		tmp->right = ptr;
	}	//完成行插入

	if (col_head[ptr->col] == 0 || col_head[ptr->col]->row > ptr->row)	//列为空或者列数在头指针所指元素之前
	{
		ptr->down = col_head[ptr->col];		//为空则 ptr->down 为空，否则 ptr->down 指向该列下一个元素
		col_head[ptr->col] = ptr;			//头指针指向 ptr
	}
	else
	{
		OLNode *tmp = col_head[ptr->col];
		for (	; tmp->down && tmp->down->row < ptr->row; tmp = tmp->down);	//tmp 总是被比较元素的前指针
		ptr->down = tmp->down;
		tmp->down = ptr;
	}	//完成列插入
}

void CrossList::Addition(const CrossList B)
{
	OLNode *ptr = row_head[1];
	OLNode *ptr_B = B.row_head[1];
	OLNode *ptr_pre = 0;
	OLink *Chead = new (col_num + 1) * OLink;
	for (int i = 1; i <= col_num; Chead[i] = col_head[i], i++);
	int Row = 1;
	while (Row <= row_num)
	{
		ptr = row_head[Row];
		ptr_B = row_head[Row];
		ptr_pre = 0;
		while (ptr_B)
		{
			if (ptr->col != ptr_B->col)
			{
				OLNode *tmp = new OLNode;
				tmp = ptr_B;
				Insert(tmp);
			}
			else
			{
				ptr->data += ptr_B->data;
				if (ptr->data == 0)
				{
					if (ptr_pre == 0)
					{
						row_head[ptr->row] = ptr->right;
					}
					else
					{
						ptr_pre->right = ptr->right;
					}
					OLNode *tmp = ptr;
					ptr = ptr->right;
					if (col_head[tmp->col] == tmp)
					{
						col_head[tmp->col] = Chead[tmp->col] = tmp->down;
					}
					else
					{
						Chead[tmp->col]->down = tmp->down;
					}
					delete tmp;
				}
			}
			ptr_B = ptr_B->right;
			ptr = row_head[Row];
		}
		Row++;
	}
}