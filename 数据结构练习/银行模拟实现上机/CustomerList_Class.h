/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#ifndef INIT_CUSTOMERLIST_CLASS
#define INIT_CUSTOMERLIST_CLASS
#include <iostream>
#include "Bank_Simulation.h"

using namespace std;

bool CustomerList::OrderInsert(Customer *e)
{
	Customer *ptr = head->next;
	Customer *ptr_pre = head;
	if (!e)
	{
		return false;
	}
	if (length == 0)
	{
		head->next = e;
		tail->next = e;
		length++;
		return true;
	}
	if (length == 1)
	{
		if ((*ptr).compare(*e) == -1)
		{
			head->next->next = e;
			tail->next = e;
		}
		else
		{
			e->next = head->next;
			head->next = e;
		}
		length++;
		return true;
	}
	while (ptr)
	{
		if ((*ptr).compare(*e) == -1)
		{
			ptr_pre = ptr;
			ptr = ptr->next;
		}
		else
		{
			e->next = ptr;
			ptr_pre->next = e;
			length++;
			return true;
		}
	}
	ptr_pre->next = e;
	e->next = 0;
	tail->next = e;
	length++;
	return true;
}

bool CustomerList::GetFirst(Customer *e)
{
	if (length == 0)
	{
		return false;
	}
	else 
	{
		e = head->next;
		return true;
	}
}

bool CustomerList::Add(Customer *customer)
{
	if (!customer)
	{
		return false;
	}
	if (length == 0)
	{
		head->next = customer;
		tail->next = customer;
		customer->next = customer;
	}
	else
	{
		tail->next->next = customer;
		customer->next = head->next;
	}
	length++;
	return true;
}

bool CustomerList::DeleteFirst()
{
	if (!head->next)	//队列为空
	{
		return false;
	}
	Customer *tmp;
	if (length == 1)	//如果队列只有一个元素
	{
		tmp = head->next;
		head->next = 0;
		tail->next = 0;
		delete tmp;
	}
	else
	{
		tmp = head->next;
		head->next = head->next->next;
		tail->next->next = head->next;
		delete tmp;
	}
	length--;
	return true;
}

#endif
