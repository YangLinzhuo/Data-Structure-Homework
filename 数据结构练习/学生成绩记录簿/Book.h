/*
	Book
*/

#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>
#include <stdlib.h>
#include "Student.h"

typedef int Status;

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef struct Book
{
	StuPtr first_stu;	//指向记录簿中的第一个学生
	int number;		//记录簿中记录的学生的个数
}GradeBook;

typedef GradeBook* BookPtr;

int GetNum(BookPtr book)
{
	if(!book)
	{
		return -1;
	}

	return book->number;
}

Status InitializeBook(BookPtr* book)
{
	(*book) = (BookPtr)malloc(sizeof(GradeBook));
	if(!book)
	{
		exit(OVERFLOW);
	}

	(*book)->first_stu = NULL;
	(*book)->number = 0;
	return OK;
}

Status AddStudent(BookPtr book, StuPtr stu_ptr)
{
	if(!book || !stu_ptr)
	{
		return ERROR;
	}

	if(GetNum(book) == 0)
	{
		book->first_stu = stu_ptr;
	}
	else
	{
		stu_ptr->next = book->first_stu;
		book->first_stu = stu_ptr;
	}

	book->number++;

	return OK;
}

Status CreateBook(BookPtr book)
{
	if(!book)
	{
		return ERROR;
	}

	char judgement;
	while(1) 
	{
	    printf("Do you want to continue write in ? Y/N  ");
	    scanf("%c", &judgement);
	    getchar();	//读取回车符
	    if(judgement == 'Y' || judgement == 'y')
	    {
	    	StuPtr stu_ptr = (StuPtr)malloc(sizeof(Student));
	    	if(!stu_ptr)
	    	{
	    		exit(OVERFLOW);
			}
			stu_ptr->next = NULL;

	    	CreateStu(stu_ptr);
	    	AddStudent(book, stu_ptr);
	    }
	    else
	    {
	    	break;
	    }
	    fflush(stdin);
	}

	return OK;
}


#endif
