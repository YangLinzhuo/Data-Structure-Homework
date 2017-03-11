/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#ifndef INIT_CUSTOMERLIST_CLASS
#define INIT_CUSTOMERLIST_CLASS
#include <iostream>
#include "Customer_Class.h"
#include "Bank_Simulation.h"

using namespace std;

Customer CustomerQueue::GetFirst()			//获取头元素	
{
	Customer c;
	if (length == 0)
	{
		return c;		//返回初始值
	}

	c = *(head->next);
	return c;
}
		
bool CustomerQueue::DeleteFirst()				//删除头元素
{
	if (length == 0)
	{
		return false;
	}
	Customer *tmp;
	if (length == 1)
	{
		tmp = head->next;
		head->next = 0;
		tail->next = 0;
		length--;
		delete tmp;
		return true;
	}

	tmp = head->next;
	head->next = head->next->next;
	head->next->prior = tail->next;
	tail->next->next = head->next;
	delete tmp;
	length--;
	return true;
}

bool CustomerQueue::AddEnd(Customer *ptr)		//在尾结点后插入
{
	if (length == 0)	//表为空
	{
		head->next = ptr;
		tail->next = ptr;
		ptr->next = ptr;
		ptr->prior = ptr;
		length++;
		return true;
	}

	tail->next->next = ptr;
	ptr->prior = tail->next;
	tail->next = ptr;
	ptr->next = head->next;
	head->next->prior = ptr;	//首尾相连循环队列
	length++;
	return true;
}

#endif
