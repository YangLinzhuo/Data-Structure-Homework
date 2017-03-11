/*
	Huffman Tree
*/

#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include <iostream>
using namespace std;

class HTNode
{
	public:
		int weight;
		int parent;
		int left_child;
		int right_child;
		bool is_used;
		HTNode()
		{
			weight = 0;
			parent = left_child = right_child = -1;
			is_used = false;
		}
};


class HuffmanTree
{
	public:
		HTNode* root;
		HuffmanTree()
		{
			root = NULL;
		}
		HuffmanTree(int n)
		{
			if(n > 0)
			{
				root = new HTNode[2 * n];
			}
		}
		void Initialize(int char_type_num);
		int CreateHTree(int weight_together, int* weight, int num);
		void Select(int range, int* s1, int* s2, int weight_together);
};

void HuffmanTree::Initialize(int char_type_num)
{
	if(char_type_num > 0)
	{
		root = new HTNode[2 * char_type_num];
	}
}

int HuffmanTree::CreateHTree(int weight_together, int* weight, int num)
{
	int node_num;
	HTNode* ptr = root;
	for (int i = 1; i <= num; i++, ptr++, weight++)
	{
		ptr->weight = *weight;		//权重赋值
	}

	int* s1 = new int; 
	int* s2 = new int;
	*s2 = *s1 = -1;
	for (int i = num; i <= 2 * num - 1; i++)
	{
		(*this).Select(i - 1, s1, s2, weight_together);
		root[*s1].parent = i;
		root[*s2].parent = i;
		root[i].left_child = *s1;
		root[i].right_child = *s2;
		root[i].weight = root[*s1].weight + root[*s2].weight;
		if(root[i].weight == weight_together)
		{
			node_num = i + 1;
			break;
		}
	}
	
	return node_num;
}


void HuffmanTree::Select(int range, int* s1, int* s2, int weight_together)
{
	int minimum = weight_together;
	int number1 = 0;
	int number2 = 0;
	for(int i = 0; i <= range; i++)
	{
		if(root[i].is_used == true)
		{
			continue;
		}
		if(root[i].weight < minimum)
		{
			minimum = root[i].weight;
			number1 = i;
		}
	}

	minimum = weight_together;
	for (int i = 0; i <= range; i++)
	{
		if (i == number1 || root[i].is_used == true)
		{
			continue;
		}

		if(root[i].weight < minimum)
		{
			minimum = root[i].weight;
			number2 = i;
		}
	}
	root[number1].is_used = true;
	root[number2].is_used = true;
	*s1 = number1;
	*s2 = number2;
}

#endif
