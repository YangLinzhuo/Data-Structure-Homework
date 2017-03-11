/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#ifndef INIT_EVENT_LIST_CLASS
#define INIT_EVENT_LIST_CLASS
#include "Bank_Simulation.h"
#include "Event_Class.h"
#include <iostream>

using namespace std;

bool EventList::OrderInsert(Event *e)		//顺序插入
{
	if (!e)
	{
		return false;
	}

	if (length == 0)		//表为空
	{
		head->next = e;
		length++;
		return true;
	}

	Event *ptr = head->next;	//表不为空
	Event *ptr_pre = head;
	while(ptr)	
	{
		if ((*ptr).Compare(*e) < 0)		//比表中元素大则继续寻找
		{
			ptr_pre = ptr;
			ptr = ptr->next;
		}
		else 								//找到位置后插入
		{
			ptr_pre->next = e;
			e->next = ptr;
			length++;
			return true;
		}
	}

	//若比表中元素都大，则插入末尾
	ptr_pre->next = e;
	length++;
	return true;
}

Event EventList::GetFirst()			//获取头元素	
{
	Event e;
	if (length == 0)
	{
		return e;			//表为空返回初始值为0的事件
	}

	e = *(head->next);
	return e;
}

bool EventList::DeleteFirst()		//删除头元素
{
	if (length == 0)
	{
		return false;	//表为空返回错误
	}

	Event *tmp;
	if (length == 1)
	{
		tmp = head->next;
		head->next = 0;
		delete tmp;
		length--;
		return true;
	}
	
	tmp = head->next;
	head->next = head->next->next;
	delete tmp;
	length--;
	return true;
}

#endif
