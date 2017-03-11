/*
	Check
*/

#ifndef CHECK_TEXT
#define CHECK_TEXT
#include <iostream>
#include <cstdlib>

using namespace std;


void Check(char* file_name1, char* file_name2)
{
	FILE* file1;
	FILE* file2;
	file1 = fopen(file_name1, "rb");
	file2 = fopen(file_name2, "rb");
	if(!file_name1 || !file_name2)
	{
		cout << "File open failed." << endl;
		exit(1);
	}

	int c1, c2;
	int same = 0;
	int not_same = 0;
	while((c1 = fgetc(file1)) != EOF && (c2 = fgetc(file2)) != EOF)
	{
		if(c1 == c2)
		{
			same++;
		}
		else
		{
			not_same++;
		}
	}
	cout << "Same character number:" << same << endl;
	cout << "Not same character number:" << not_same << endl;
	if(not_same == 0)
	{
		cout << "Decompression Succeeded!" << endl;
	}
	else
	{
		cout << "Decompression Failed!" << endl;
	}
}

#endif
