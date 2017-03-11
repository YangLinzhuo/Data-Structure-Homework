/*
	Depress
*/

#include <iostream>
#include <cstdlib>
#include "HuffmanTree.h"
#include "HuffmanCode.h"
#include "Compress.h" 
#include "Decompress.h"
#include "Check_Text.h"

int Initialization(char* CH, int* weight)
{
	char save_file_name[50] = "hfmTree.txt";
	FILE* file_ptr;
	file_ptr = fopen(save_file_name, "wb");
	if(!file_ptr)
	{
		cout << "File open failed." <<endl;
		exit(1);
	}

	int char_type_num;
	cout << "Enter the number of character's types: ";
	cin >> char_type_num;
	for(int i = 0; i < char_type_num; i++)
	{
		cout << "No." << i << ": ";
		cin >> CH[i];
		cin >> weight[i];
		fprintf(file_ptr, "%c %d \n", CH[i], weight[i]);
	}

	fclose(file_ptr);
	return char_type_num;
}

void Print(HuffmanTree tree, int index, int level)	//第一次调用level为0
{
	if(tree.root[index].right_child != -1)
	{
		Print(tree, tree.root[index].right_child, level + 1);
	}

	for(int i = 0; i < level; i++)
	{
		cout << "	";
	}
	cout << tree.root[index].weight << endl;
	
	if(tree.root[index].left_child != -1)
	{
		Print(tree, tree.root[index].left_child, level + 1);
	}

}


void SystemShow()
{
	system("pause");
	system("cls");
	cout << "--------------------------------------" << endl;
	cout << "1: " << "Write in code." << endl;
	cout << "2: " << "Calculate file's character." << endl;
	cout << "3: " << "Encode and compress." << endl;
	cout << "4: " << "Decompress." << endl;
	cout << "0: " << "Quit." << endl;
	cout << "--------------------------------------" << endl;
}

int main()
{
	char in_file_name[50] = "1.mp4";
	char out_file_name[50] = "2.dat";
	char decompressed_file_name[50] = "3.mp4";

	int char_type_num = 0;	//字符的种类数
	int char_num = 0;	//字符总数
	char CH[256];	//统计权重不为 0 的字符
	int  weight[256];	//对应的权重
	memset(CH, 0, sizeof(CH));
	memset(weight, 0, sizeof(weight));
	int character[256];
	memset(character, 0, sizeof(character));

	
	int node_num; 
	int compressed_file_space;
	int file_space;

	HuffmanTree tree;
	HuffmanCode code;

	int command = 'Q';

	while(command != 0)
	{
		SystemShow();
		cout << "Enter your command: ";
		cin >> command;
		switch(command)
		{
			case 1:	
						char_type_num = Initialization(CH, weight);
						for(int i = 0; weight[i] != 0; i++)
						{
							char_num += weight[i];
						}
						break;
			
			case 2:		
						file_space = Calculate(character, in_file_name);
						char_type_num = 0;
						for (int i = 0; i < 256; i++)
						{
							if(character[i] != 0)
							{
								char_num += character[i];
								CH[char_type_num] = '\0' + i;
								weight[char_type_num] = character[i];
								char_type_num++;
							}
						}
						break;
			case 3:	
						tree.Initialize(char_type_num);
						code.Initialize(char_type_num);
						node_num = tree.CreateHTree(char_num, weight, char_type_num);
						code.Coding(tree, char_type_num);
						
						compressed_file_space = Compress_to_Binary(in_file_name, out_file_name, CH, code, char_type_num, char_type_num);
						
						cout << "file_space: " << "\t" << file_space << "Kb" << endl;
						cout << "compressed file space: " << compressed_file_space << "Kb" << endl;
						cout << "rate: " << "\t" << file_space / compressed_file_space << '%' << endl;
						break;
			case 4:	
						Decompress(out_file_name, decompressed_file_name, tree, CH, code, node_num);
						Check(in_file_name, decompressed_file_name);
						break;
		}
	}

	return 0;
}
