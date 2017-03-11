/*
	Calculate Char in C type
*/

#ifndef COMPRESS
#define COMPRESS

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "HuffmanCode.h"

#define BYTE_LENGTH 8
using namespace std;

int Calculate(int* character, char* file_name)	//统计文本中字符的总数
{
	FILE* inFile;
	inFile = fopen(file_name, "rb+");
	if(!inFile)
	{
		cout << "File open failed." << endl;
		exit(1);
	}
	int ch;
	while((ch = fgetc(inFile)) != EOF)
	{
		character[ch - '\0']++;
	}
	int space = ftell(inFile);
	fclose(inFile);
	return space;
}


int Search(char* character, char ch)	//查找指定字符的索引
{
	if(!character)
	{
		return -1;
	}

	for(int i = 0; i < 256; i++)
	{
		if(character[i] == ch)
		{
			return i;
		}
	}

	return -1;
}


int Binary_to_Decimal(char* str)	//将二进制 01 序列转换为十进制整数
{
	int len = strlen(str);
	int result = 0;
	for (int i = 0; i < len && i < BYTE_LENGTH; i++)
	{
		if(str[i] == '1')
		{
			result += pow(2, len - 1 - i);
		}
	}
	return result;
}


int Compress_to_Binary(char* in_file_name, char* out_file_name, char* character, HuffmanCode Code, int char_num, int char_type_num)	//压缩函数
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

	fprintf(outFile, "%d\r\n", char_type_num);
	for(int i = 0; i < char_type_num; i++)
	{
		fprintf(outFile, "%c %s\r\n", character[i], Code.code[i]);
	}
	fputc('#', outFile);
	 
	int ch;
	char c;
	char pre_code[256 + BYTE_LENGTH];	//存储上一个读取的序列残留的序列
	char cur_code[256 + BYTE_LENGTH];	//存储处理后的当前的序列
	char in_code[256 + BYTE_LENGTH];	//暂存当前的序列
	int pre_len = 0;
	int in_len = 0;		//对应序列的长度
	memset(pre_code, 0, sizeof(pre_code));
	memset(cur_code, 0, sizeof(cur_code));
	memset(in_code, 0, sizeof(in_code));	//数组置空

	while((ch = fgetc(inFile)) != EOF)
	{
		pre_len = strlen(pre_code);
		strncpy(in_code, pre_code, pre_len);	//将上次剩余的序列拷贝
		int position = Search(character, ch);	//查找字符的位置
		if(position >= 0)
		{
			strcpy(&in_code[pre_len], Code.code[position]);	//拷贝对应的编码
			in_len = strlen(in_code);
			memset(pre_code, 0, sizeof(pre_code));
			while(in_len >= BYTE_LENGTH)	//编码数达到8位
			{
				strncpy(cur_code, in_code, BYTE_LENGTH);
				cur_code[BYTE_LENGTH] = '\0';

				for(int b = 0; b < in_len - BYTE_LENGTH; b++)
				{
					in_code[b] = in_code[BYTE_LENGTH + b];
				}
				in_code[in_len - BYTE_LENGTH] = '\0';
				c = Binary_to_Decimal(cur_code);
				fputc(c, outFile);	//写入字符
				memset(cur_code, 0, sizeof(cur_code));
				in_len = strlen(in_code);
			}
			
			
			strncpy(pre_code, in_code, in_len);	//将剩余序列拷贝
		}

		memset(in_code, 0, sizeof(in_code));	//清空存储区域
	}

	pre_len = strlen(pre_code);	//将剩余的序列编码写入
	while(pre_len >= 8)
	{
		strncpy(cur_code, pre_code, BYTE_LENGTH);
		cur_code[BYTE_LENGTH] = '\0';

		c = Binary_to_Decimal(cur_code);
		for(int b = 0; b < pre_len - BYTE_LENGTH; b++)
		{
			pre_code[b] = pre_code[BYTE_LENGTH + b];
		}
		pre_code[pre_len - BYTE_LENGTH] = '\0';
		
		fputc(c, outFile);
		pre_len = strlen(pre_code);
	}

	for(int i = 0; i < BYTE_LENGTH - pre_len; i++)
	{
		pre_code[pre_len + i] = '0';
	}
	c = Binary_to_Decimal(pre_code);
	fputc(c, outFile);
	fputc('0' + BYTE_LENGTH - pre_len, outFile);	//写入补0的个数
	
	int space = ftell(outFile);
	fclose(inFile);
	fclose(outFile);
	return space;
}


#endif
