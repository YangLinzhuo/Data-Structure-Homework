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
	printf("1.������Ϣ�����洢\n");
	printf("2.��ȡ�����ļ������\n");
	printf("3.��ѧ�Ż�������ѯ�ɼ�\n");
	printf("4.���ѧ���ɼ�\n");
	printf("5.�޸�ѧ���ɼ�\n");
	printf("6.��ʾ������������ε�ѧ���ɼ�\n");
	printf("7.��ʾ��ǰ���������ݵļ�¼��\n");
	printf("0.�˳�\n");
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
		printf("�ɼ���¼������ʧ��.\n");
		return ERROR;
	}
	printf("����洢�ļ���:\n");
	scanf("%s", file);
	return Save(book, file);
}

Status ReadStuInfromation(BookPtr* book)
{
	char file[20];
	printf("�����ļ���:\n");
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
	printf("����0����ѧ�Ų�ѯ������1����������ѯ:\n");
	scanf("%d", &tag);
	fflush(stdin);
	printf("����ѧ��ѧ�Ż�����:\n");
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
	printf("����0����ѧ���޸ģ�����1���������޸�\n");
	scanf("%d", &tag);
	fflush(stdin);
	printf("����ѧ�Ż�����:\n");
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
	printf("60�����£�\n");
	for(stu = book->first_stu; stu; stu = stu->next)
	{
		if(stu->grade < 60)
		{
			printf("%s\t%s\t%d\n", stu->number, stu->name, stu->grade);
		}
	}
	printf("60~79�֣�\n");
	for(stu = book->first_stu; stu; stu = stu->next)
	{
		if(stu->grade >= 60 && stu->grade <= 79)
		{
			printf("%s\t%s\t%d\n", stu->number, stu->name, stu->grade);
		}
	}
	printf("80~89�֣�\n");
	for(stu = book->first_stu; stu; stu = stu->next)
	{
		if(stu->grade >= 80 && stu->grade <= 89)
		{
			printf("%s\t%s\t%d\n", stu->number, stu->name, stu->grade);
		}
	}
	printf("90�����ϣ�\n");
	for(stu = book->first_stu; stu; stu = stu->next)
	{
		if(stu->grade >= 90)
		{
			printf("%s\t%s\t%d\n", stu->number, stu->name, stu->grade);
		}
	}
}

