/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#ifndef INIT_CUSTOMERLIST_CLASS
#define INIT_CUSTOMERLIST_CLASS
#include <iostream>
#include "Customer_Class.cpp"
#include "Bank_Simulation.h"
using namespace std;

bool Customer_List::OrderInsert(Customer *cus)
{
	if (!cus)
	{	
		return false;
	}

	Customer *tmp = new Customer;
	(*tmp).Copy(*cus);
	
	if (length == 0)	//表为空
	{
		head->next = tail->prior = tmp;
		tmp->prior = head, tmp->next = tail;
		length++;
		return true;
	}
	
	Customer *ptr = head->next;			//表不为空
	while (ptr != tail)
	{
		if ((*ptr).compare(*tmp) == -1)		//比表中元素大则继续寻找
		{
			ptr = ptr->next;
		}
		else 								//找到位置后插入
		{
			tmp->next = ptr;
			tmp->prior = ptr->prior;
			ptr->prior->next = tmp;
			ptr->prior = tmp;
			length++;
			return true;
		}
	}

	//若比表中元素都大，则插入末尾
	tail->prior->next = tmp;			
	tmp->prior = tail->prior;
	tmp->next = tail;
	tail->prior = tmp;
	length++;
	return true;
}

bool Customer_List::GetFirst(Customer &cus)			//获取头元素	
{
	if (length == 0)
	{
		return false;				//表为空
	}

	cus.Copy(*(head->next));		//将头元素的值复制给 cus
	return true;
}

bool Customer_List::DeleteFirst()		//删除头元素
{
	if (length == 0)	//表为空
	{
		return false;
	}

	Customer *tmp = head->next;
	head->next = tmp->next;
	head->next->prior = head;
	delete tmp;
	return true;
}

bool Customer_List::AddEnd(Customer *cus)			//在尾结点后插入
{
	if (length == 0)		//表为空
	{
		head->next = cus;
		tail->prior = cus;
		cus->prior = head;
		cus->next = tail;
		return true;
	}

	cus->prior = tail->prior;
	tail->prior->next = cus;
	cus->next = tail;
	tail->prior = cus;
	return true;
}

#endif
