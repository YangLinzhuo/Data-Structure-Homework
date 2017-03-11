/*
	Menu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Student.h"
#include "Book.h"
#include "SaveRead.h"


typedef int Status;

#define OK 1
#define ERROR 0
#define OVERFLOW -2

void Menu()
{
	printf("\n\n\n");
	printf("----------------------------------------------\n");
	printf("1.创建信息链表并存储\n");
	printf("2.读取磁盘文件并输出\n");
	printf("3.按学号或姓名查询成绩\n");
	printf("4.添加学生成绩\n");
	printf("5.修改学生成绩\n");
	printf("6.显示输出各个分数段的学生成绩\n");
	printf("7.显示当前储存了内容的记录簿\n");
	printf("0.退出\n");
	printf("----------------------------------------------\n");

}

void Print(BookPtr book)
{
	if(!book)
	{
		printf("No information.\n");
		return;
	}
	StuPtr stu = book->first_stu;
	while(stu)
	{
		printf("%s\t%s\t%d\n", stu->number, stu->name, stu->grade);
		stu = stu->next;
	}
}


Status CreateStuInformation(BookPtr book)
{
	char file[20];
	if(!CreateBook(book))
	{
		printf("成绩记录簿创建失败.\n");
		return ERROR;
	}
	printf("输入存储文件名:\n");
	scanf("%s", file);
	return Save(book, file);
}

Status ReadStuInfromation(BookPtr* book)
{
	char file[20];
	printf("输入文件名:\n");
	scanf("%s", file);
	if(*book = Read(file))
	{
		Print(*book);
	}
	else
		return ERROR;
}

Status SearchStu(BookPtr book)
{
	int tag = 0;
	char information[20];
	printf("输入0根据学号查询，输入1根据姓名查询:\n");
	scanf("%d", &tag);
	fflush(stdin);
	printf("输入学生学号或姓名:\n");
	scanf("%s", information);
	return SearchInformation(book, information, tag) != NULL;
}


Status Append(BookPtr book)
{
	StuPtr stu = (StuPtr)malloc(sizeof(Student));
	if(!stu)
	{
		exit(OVERFLOW);
	}
	stu->next = NULL;

	CreateStu(stu);
	AddStudent(book, stu);
	printf("%s\t%s\t%d\n", stu->number, stu->name, stu->grade);
	return OK;
}

Status Alter(BookPtr book)
{
	int tag = 0;
	char information[20]; 
	printf("输入0根据学号修改，输入1根据姓名修改\n");
	scanf("%d", &tag);
	fflush(stdin);
	printf("输入学号或姓名:\n");
	scanf("%s", &information);
	return ChangeInformation(book, information, tag);
}

void PrintByGrade(BookPtr book)
{
	StuPtr stu;
	if(!book)
	{
		printf("No Information.\n");
		return;
	}
	printf("60分以下：\n");
	for(stu = book->first_stu; stu; stu = stu->next)
	{
		if(stu->grade < 60)
		{
			printf("%s\t%s\t%d\n", stu->number, stu->name, stu->grade);
		}
	}
	printf("60~79分：\n");
	for(stu = book->first_stu; stu; stu = stu->next)
	{
		if(stu->grade >= 60 && stu->grade <= 79)
		{
			printf("%s\t%s\t%d\n", stu->number, stu->name, stu->grade);
		}
	}
	printf("80~89分：\n");
	for(stu = book->first_stu; stu; stu = stu->next)
	{
		if(stu->grade >= 80 && stu->grade <= 89)
		{
			printf("%s\t%s\t%d\n", stu->number, stu->name, stu->grade);
		}
	}
	printf("90分以上：\n");
	for(stu = book->first_stu; stu; stu = stu->next)
	{
		if(stu->grade >= 90)
		{
			printf("%s\t%s\t%d\n", stu->number, stu->name, stu->grade);
		}
	}
}

