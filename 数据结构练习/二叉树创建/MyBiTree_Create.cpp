/*Binary Tree Create
Author: YangLinzhuo
Date: 2016.10.25
*/

#include <iostream>
#include <cstring>
using namespace std;

class BiNode
{
	public:
		char ch;
		BiNode *left, *right;
		BiNode(char c = 'a', BiNode *l = 0, BiNode *r = 0)
		{
			ch = c;
			left = l;
			right = r;
		}
		~BiNode()
		{
			delete left;
			delete right;
			left = right = 0;
		}
};

typedef BiNode* BiTree;

int Position(char *str, char ch)
{
	int length = strlen(str);
	for (int i = 0; i < length; i++)
	{
		if (str[i] == ch)
		{
			return i;
		}
	}
	return -1;	//return -1 表示 str 中不存在ch
}

void PreMidCreate(BiTree &Node, char *pre, char *inorder, int length)
{
	if (length <= 0)
		return;

	Node = new BiNode;
	Node->ch = *pre;
	int i = Position(inorder, *pre);
	if (i > -1)
	{
		PreMidCreate(Node->left, pre + 1, inorder, i);
		PreMidCreate(Node->right, pre + i + 1, inorder + i + 1, length - i - 1);
	}
}

void PostTraverse(BiTree T)
{
	if (!T)
	{
		return;
	}

	PostTraverse(T->left);
	PostTraverse(T->right);
	cout << T->ch << " ";
}

int main()
{
	char pre[50];        //前序序列
	char inorder[50];        //中序序列
	cout << "Enter the pre: ";
	cin >> pre;
	cout << "Enter the inorder:";
	cin >> inorder;
	BiTree root;
	PreMidCreate(root, pre, inorder, strlen(inorder));
	PostTraverse(root);
	return 0;
}
