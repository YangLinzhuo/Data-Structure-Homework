/*
	Decompress
*/

#ifndef DECOMPRESS
#define DECOMPRESS

#define BYTELENGTH 8
#include <iostream>
#include <cstdlib> 
#include <cstring>
#include "HuffmanTree.h"
#include "HuffmanCode.h"
#include "Compress.h" 

using namespace std;

int Find(char* code, HuffmanTree tree, int node_num)	//根据code在二叉树中寻找对应的字符，返回字符所在位置序数
{
	if(!code || !tree.root)
	{
		return -1;	//-1表示错误
	}

	int len = strlen(code);
	int index = node_num - 1;	//解码时的索引
	int i;
	for(i = 0; (tree.root[index].left_child != -1 || tree.root[index].right_child != -1) && i < len; i++)	//当左右孩子不全为空时继续查找
	{
		if(code[i] == '0')
		{
			index = tree.root[index].left_child;
		}
		else
		{
			index = tree.root[index].right_child;
		}
	}
	if(tree.root[index].left_child == -1 && tree.root[index].right_child == -1)
	{
		return index;
	}
	else
	{
		return -1;
	}
}

void Decimal_to_Binary(int ch, char* code)
{
	int i;
	for(i = 0; i < BYTELENGTH; i++)
	{
		code[BYTELENGTH - i - 1] = '0' + ch % 2;
		ch /= 2;
	}
}


void Decompress(char* in_file_name, char* out_file_name, HuffmanTree tree, char* character, HuffmanCode Code, int node_num)
{
	FILE* inFile;
	FILE* outFile;
	inFile = fopen(in_file_name, "rb+");
	outFile = fopen(out_file_name, "wb+");
	if(!inFile || !outFile)
	{
		cout << "File open failed." << endl;
		exit(1);
	}
	
	int text_length = 0;
	fseek(inFile, 0L, SEEK_END);
	text_length = ftell(inFile);
	int ch;
	int complement_zero = 0;	//记录最后补零的个数
	fseek(inFile, -1L, SEEK_END);
	ch = fgetc(inFile);
	complement_zero = ch - '0';
	rewind(inFile);

	int char_type_num = 0;
	fscanf(inFile, "%d", &char_type_num);
	int num;
	char cd[BYTELENGTH + 1];
	memset(cd, 0, sizeof(cd));
	for(int i = 0; i < char_type_num; i++)
	{
		ch = fgetc(inFile);
		ch = fgetc(inFile);
		memset(Code.code[i], 0, sizeof(Code.code[i]));
		fscanf(inFile, "%c %s", &character[i], Code.code[i]);
	}
	
	ch = fgetc(inFile);
	ch = fgetc(inFile);
 	fscanf(inFile, "%c", &ch);

	
	char in_code[256 * 2 + BYTELENGTH];
	char pre_code[256 + BYTELENGTH];
	memset(pre_code, 0, sizeof(pre_code));
	memset(in_code, 0, sizeof(in_code));
	int in_len = 0;
	int pre_len = 0;
	int cur_len = 0;
	int index;

	while(ftell(inFile) <= text_length - 2)		//在文件倒数第一个字符之前终止
	{
		strncpy(in_code, pre_code, pre_len);
		memset(pre_code, 0, sizeof(pre_code));
		ch = fgetc(inFile);
		if(ftell(inFile) - 1 != text_length - 1)
		{
			Decimal_to_Binary(ch, &in_code[pre_len]);
		}
		else
		{
			for(int k = 0; k < BYTELENGTH - complement_zero; k++)
			{
				in_code[pre_len + k] = '0' + ch % 2;
				ch /= ch;
			}
			in_code[pre_len + BYTELENGTH - complement_zero] = '\0';
		}

		in_len = strlen(in_code);
		while((index = Find(in_code, tree, node_num)) != -1)	//查找二叉树，返回其索引
		{

			fputc(character[index], outFile);	//向文件内输出字符
			int len = strlen(Code.code[index]);
			for(int j = 0; j < in_len - len; j++)
			{
				in_code[j] = in_code[len + j];
			}
			in_code[in_len - len] = '\0';
			in_len = strlen(in_code);
		}

		strncpy(pre_code, in_code, in_len);	//拷贝残留序列
		pre_code[in_len] = '\0';
		pre_len = strlen(pre_code);
		memset(in_code, 0, sizeof(in_code));
	}

	fclose(inFile);
	fclose(outFile);
}

#endif 
