#include <iostream>
#include <cstring>
using namespace std;

char pre[50] = "ABDGEHIJCFK";        //前序序列
char mid[50] = "DGBIHJEFKCA";        //中序序列
/*char post[50] = "LHDKEBFGCA";        //后序序列*/
 
typedef struct _Node
{
    char v;
    struct _Node *left;
    struct _Node *right;
}Node, *PNode;

int Position(char c)
{
	return strchr(mid, c) - mid;
}

void PreMidCreateTree(PNode &pn, int i, int j, int len)
{
	if (len <= 0)
		return;

	pn = new Node;
	pn->v = pre[i];
	int m = Position(pre[i]);
	PreMidCreateTree(pn->left, i + 1, j, m - j);
	PreMidCreateTree(pn->right, i + (m - j) + 1, m + 1, len - 1 - (m - j));
}

//*void PostMidCreateTree(PNode &pn, int i, int j, int len)	// i, j 从len 开始减小
/*{
	if (len <= 0)
		return;

	pn = new Node;
	pn->v = post[i];
	int m = Position[post[i]];
	PostMidCreateTree(pn->left, i - 1 - (len - 1 - (m - j)), j, m - j);
	PostMidCreateTree(pn->right, i - 1, m + 1, len - 1 - (m - j));
}*/

void PostTraverse(PNode pn)
{
	if (pn)
	{
		cout << pn->v << " " <<;
		PostTraverse(pn->left);
		PostTraverse(pn->right);
	}
}

int main()
{
	PNode root1 = NULL;
	PNode root2 = NULL;

	PreMidCreateTree(root1, 0, 0, strlen(pre));
	PostTraverse(root);
	PostMidCreateTree(root2, strlen(post)-1, 0, strlen(mid));
}

/*
BTree trans(char *pre,char *inorder,int len)
{
 char *p,*q;
 BTree root;
 int i;
 if(len<=0)
  return NULL;
 root = (BTree)malloc(sizeof(BNode));
 root->data = pre[0];    //根节点
 root->lch = NULL;
 root->rch = NULL;
    i = 0;                 //i表示根节点在中序中的位置
 while(i<len)
 {
  if(inorder[i]==pre[0])
   break;
  i++;
 }
 p = pre+1;                 //确定左子树的先序序列指针
 q = inorder;               //确定左子树的中序序列指针
 root->lch = trans(p,q,i);  //递归生成左子树
 p = pre+i+1;               //确定右子树的先序序列指针
 q = inorder+i+1;           //确定右子树的中序序列指针
 root->rch = trans(p,q,len-i-1);//递归生成右子树
   return root;
}
*/
