/*
	Main
*/

#include <stdio.h>
#include <stdlib.h>
#include "Student.h"
#include "Book.h"
#include "SaveRead.h"
#include "Search.h"
#include "Menu1.h"

#define OVERFLOW -2


int main()
{
	BookPtr book[10];
	int count = 0;
	int i = 0;
	int j;
	for(j = 0; j < 10; j++)
	{
		InitializeBook(&book[j]);
	}

	int command = 0;
	while(1) 
	{
		Menu();
		printf("请输入指令：\n");
		scanf("%d", &command);
		fflush(stdin);
		if(command == 0)
		{
			break;
		}
		else
		{
			switch(command)
			{
				case 1:
						printf("请输入操作的记录簿对象序号：\n");
						scanf("%d", &i);
						fflush(stdin);
						CreateStuInformation(book[i]);
						break;
				case 2:
						printf("请输入操作的记录簿对象序号：\n");
						scanf("%d", &i);
						fflush(stdin);
						ReadStuInfromation(&book[i]);
						break;
				case 3:	
						printf("请输入操作的记录簿对象序号：\n");
						scanf("%d", &i);
						fflush(stdin);
						SearchStu(book[i]);
						break;
				case 4:
						printf("请输入操作的记录簿对象序号：\n");
						scanf("%d", &i);
						fflush(stdin);
						Append(book[i]);
						break;
				case 5:
						printf("请输入操作的记录簿对象序号：\n");
						scanf("%d", &i);
						fflush(stdin);
						Alter(book[i]);
						break;
				case 6:
						printf("请输入操作的记录簿对象序号：\n");
						scanf("%d", &i);
						fflush(stdin);
						PrintByGrade(book[i]);
						break;
				case 7:
						for(j = 0; j < 10; j++)
						{
							if(book[j]->first_stu)
							{
								printf("book[%d]\n", j);
							}
						}
						break;
			}
		}
		fflush(stdin);
	}
	
	return 0;
}
