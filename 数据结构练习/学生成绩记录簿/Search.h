/*
	Search
*/

#ifndef SEARCH_H
#define SEARCH_H

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

Status SortByNumber(BookPtr book)
{
	if(!book)
	{
		return ERROR;
	}

	StuPtr stu_ptr, stu_pre;
	StuPtr tmp, record, pre;
	for(stu_ptr = book->first_stu, stu_pre = NULL; stu_ptr; stu_pre = record, stu_ptr = record->next)//选择排序
	{
		record = stu_ptr;	//记录学号顺序最小的结点
		for(tmp = stu_ptr->next; tmp; tmp = tmp->next)
		{
			switch(strcmp(record->number, tmp->number))
			{
				case -1: break;	//字符串顺序小则跳过
				case  1:
						record = tmp;  
						break;
			}
		}

		if(record != stu_ptr)//调换位置
		{
			for(pre = stu_ptr; pre->next != record; pre = pre->next);//找到record的前驱
			if(stu_ptr == pre)//二者位置相邻
			{
				stu_ptr->next = record->next;
				stu_pre->next = record;
				record->next = stu_ptr;
			}
			else
			{
				pre->next = stu_ptr->next;	//record的前驱指向第一个结点的后继
				stu_ptr->next = record->next;	//第一个结点的后继指向record原来的后继
				record->next = pre->next;	//record当前的后继是第一个结点原来的后继
				pre->next = stu_ptr;
				if(stu_pre != NULL)
				{
					stu_pre->next = record;
				}	
				if(stu_ptr == book->first_stu)
				{
					book->first_stu = record;
				}
			}
		}
	}

	return OK;
}

StuPtr SearchNumber(BookPtr book, char* number)
{
	if(!book || !number)
	{
		printf("No information.\n");
		return NULL;
	}

	StuPtr stu_ptr;
	for(stu_ptr = book->first_stu; stu_ptr; stu_ptr = stu_ptr->next)
	{
		if(!strcmp(stu_ptr->number, number))//信息匹配
		{
			printf("%s\t%s\t%d\n", stu_ptr->number, stu_ptr->name, stu_ptr->grade);
			return stu_ptr;
		}
	}

	printf("No information.\n");
	return NULL;
}

Status SortByName(BookPtr book)
{
	if(!book)
	{
		return ERROR;
	}

	StuPtr stu_ptr, stu_pre;
	StuPtr tmp, record, pre;
	for(stu_ptr = book->first_stu, stu_pre = NULL; stu_ptr; stu_pre = record, stu_ptr = record->next)//选择排序,注意这里用的而是record的后继
	{															   //因为record是记录当前未比较的最小结点
		record = stu_ptr;	//记录姓名顺序最小的结点
		for(tmp = stu_ptr->next; tmp; tmp = tmp->next)
		{
			switch(strcmp(record->name, tmp->name))
			{
				case -1: break;	//字符串顺序小则跳过
				case  1:
						record = tmp;  
						break;
			}
		}

		if(record != stu_ptr)//调换位置
		{
			for(pre = stu_ptr; pre->next != record; pre = pre->next);//找到record的前驱
			if(stu_ptr == pre)//二者位置相邻
			{
				stu_ptr->next = record->next;
				stu_pre->next = record;
				record->next = stu_ptr;
			}
			else
			{
				pre->next = stu_ptr->next;	//record的前驱指向第一个结点的后继
				stu_ptr->next = record->next;	//第一个结点的后继指向record原来的后继
				record->next = pre->next;	//record当前的后继是第一个结点原来的后继
				pre->next = stu_ptr;
				if(stu_pre != NULL)
				{
					stu_pre->next = record;
				}
				if(stu_ptr == book->first_stu)
				{
					book->first_stu = record;
				}
			}
		}
	}
	return OK;
}

StuPtr SearchName(BookPtr book, char* name)
{
	if(!book || !name)
	{
		printf("No information.\n");
		return NULL;
	}

	StuPtr stu_ptr;
	for(stu_ptr = book->first_stu; stu_ptr; stu_ptr = stu_ptr->next)
	{
		if(!strcmp(stu_ptr->name, name))//信息匹配
		{
			printf("%s\t%s\t%d\n", stu_ptr->number, stu_ptr->name, stu_ptr->grade);
			return stu_ptr;
		}
	}

	printf("No information.\n");
	return NULL;
}

StuPtr SearchInformation(BookPtr book, char* information, int tag)	//tag = 0按学号搜索，tag = 1按姓名搜索
{
	switch(tag)
	{
		case 0:
				if(SortByNumber(book))
					return SearchNumber(book, information);
				else
					return NULL;
		case 1:
				if(SortByName(book))
					return SearchName(book, information);
				return NULL;
	}
}


Status ChangeInformation(BookPtr book, char* information, int tag)//tag = 0按学号搜索，tag = 1按姓名搜索
{
	if(!book || !information)
	{
		return ERROR;
	}

	StuPtr stu_ptr = SearchInformation(book, information, tag);
	printf("Please enter the new grade:\n");
	scanf("%d", &(stu_ptr->grade));
	printf("%s\t%s\t%d\n", stu_ptr->number, stu_ptr->name, stu_ptr->grade);
	return OK;
}

#endif
