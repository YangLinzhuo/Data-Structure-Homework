/*
	Save and Read
*/

#ifndef SAVE_READ_H
#define SAVE_READ_H
#include <stdio.h>
#include <stdlib.h>
#include "Student.h"
#include "Book.h"

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;

Status Save(BookPtr book, char* fileName)	//filename是写入目标文件名
{
	StuPtr stu_ptr = book->first_stu;	//学生结点指针
	FILE* file_ptr;	//文件指针
	file_ptr = fopen(fileName, "wb+");
	if(!file_ptr)	//文件打开失败
	{
		printf("File open failed.\n");
		return ERROR;
	}
	while(stu_ptr)
	{
		fprintf(file_ptr, "%s\t%s\t%d\r\n", stu_ptr->number, stu_ptr->name, stu_ptr->grade);
		stu_ptr = stu_ptr->next;
	}

	fclose(file_ptr); //关闭文件
	return OK;
}

BookPtr Read(char* fileName)	//filename是读取目标文件名
{
	BookPtr book = (BookPtr)malloc(sizeof(GradeBook));
	if(!book)	//内存分配失败
	{
		exit(OVERFLOW);
	}
	InitializeBook(&book);

	StuPtr stu_ptr;	//学生指针
	FILE* file_ptr;	//文件指针
	file_ptr = fopen(fileName, "rb+");
	if(!file_ptr)	//文件打开失败
	{
		printf("File open failed.\n");
		return ERROR;
	}
	while(!feof(file_ptr))	//未读到文件末尾
	{
		stu_ptr = (StuPtr)malloc(sizeof(Student));
		if(!stu_ptr)	//内存分配失败
		{
			exit(OVERFLOW);
		}
		stu_ptr->next = NULL;

		fscanf(file_ptr, "%s\t%s\t%d\r\n", stu_ptr->number, stu_ptr->name, &(stu_ptr->grade));
		AddStudent(book, stu_ptr);	//添加学生结点
		stu_ptr = stu_ptr->next;
	}

	fclose(file_ptr); //关闭文件
	return book;
}


#endif
