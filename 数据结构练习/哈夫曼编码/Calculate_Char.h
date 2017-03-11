/*
	Calculate	Char
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include "HuffmanCode.h"
using namespace std;

void Calculate(int* character, char* file_name)
{
	ifstream inFile;
	inFile.open(file_name, ios::in);
	char* ch = new char;
	while(inFile.read(ch, sizeof(char)))
	{
		character[*ch - '\0']++;
	}
	inFile.close();
}

void Depress_to_Binary(HuffmanCode code, char* in_file_name, char* out_file_name)
{
	ifstream inFile;
	ofstream outFile;
	inFile.open(in_file_name, ios::in);
	outFile.open(out_file_name, ios::out | ios::trunc);
	inFile.clear();
	inFile.seekg(0, ios::beg);
	char* ch = new char;
	while(inFile.read(ch, sizeof(char))); 
	{
		outFile.write(code.code[(int)(*ch - '\0')], strlen(code.code[(int)(*ch - '\0')]));/*sizeof(code.code[(int)(*ch - '\0')])*/
	}
	inFile.close();
	outFile.close();
}

int Binary_to_Decimal(char* str)
{
	int len = strlen(str);
	int result = 0;
	for (int i = 0; i < len; i++)
	{
		result += pow((int)(str[i] - '0'), len - 1 - i);
	}
	return result;
}

void Depress(char* in_file_name, char* out_file_name)
{
	ifstream inFile;
	ofstream outFile;
	inFile.open(in_file_name);
	outFile.open(out_file_name);
	char ch[8 + 1];
	ch[8] = '\0';
	char* c = new char;
	while(inFile.read(ch, sizeof(char) * 8))
	{
		int len = strlen(ch);
		if(len != 8)
		{
			for (int i = 0; i < 8 - len; i++)
			{
				ch[len + i + 1] = '0';
			}
		}

		int number = Binary_to_Decimal(ch);
		*c = '\0' + number;
		outFile.write(c, sizeof(char));
		if(len != 8)
		{
			*c = '0' + len;
			outFile.write(c, sizeof(char));
		}
	}
}
