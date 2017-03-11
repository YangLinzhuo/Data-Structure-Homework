/*
	Student
*/

#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;

typedef struct StuNode
{
	char number[15];	//学号
	char name[20];		//姓名
	int grade;			//成绩
	struct StuNode* next;
}Student;

typedef Student* StuPtr;

Status CreateStu(StuPtr stu)
{
	if(!stu)
	{
		return ERROR;
	}
	
	fflush(stdin);
	printf("Please enter the student's number:");
	scanf("%s", stu->number);
	printf("Please enter the student's name:");
	scanf("%s", stu->name);
	printf("Please enter the student's grade:");
	scanf("%d", &(stu->grade));
	return OK;
}


#endif
