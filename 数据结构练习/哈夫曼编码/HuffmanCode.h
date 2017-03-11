/*
	Huffman Code
*/

#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H

#include <iostream>
#include <cstring>
#include "HuffmanTree.h"
using namespace std;

class HuffmanCode
{
	public:
		char** code;
		HuffmanCode()
		{
			code = NULL;
		}
		HuffmanCode(int n)
		{
			code = new char*[n + 1];
		}

		void Initialize(int char_type_num);
		void Coding(HuffmanTree HT, int num);
};

void HuffmanCode::Initialize(int char_type_num)
{
	code = new char*[char_type_num + 1];
}

void HuffmanCode::Coding(HuffmanTree HT, int num)
{
	char* cd = new char[num];
	cd[num - 1] = '\0';
	for (int i = 0; i < num; i++)
	{
		int start = num - 1;
		int child, father;
		for (child = i, father = HT.root[i].parent; father != -1; child = father, father = HT.root[father].parent)
		{
			if(HT.root[father].left_child == child)
			{
				cd[--start] = '0';
			}
			else
			{
				cd[--start] = '1';
			}
		}

		code[i] = new char[num - start];
		strcpy(code[i], &cd[start]);
	}
	delete cd;
}

#endif
