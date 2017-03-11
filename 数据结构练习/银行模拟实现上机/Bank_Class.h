/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#ifndef INIT_BANK_CLASS
#define INIT_BANK_CLASS
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Bank_Simulation.h"
#include "Customer_Class.h"
#include "CustomerList_Class.h"

using namespace std;

void Bank::OpenForDay()			//一次性生成全部事件
{
	int time = 0;
	Customer *InitialEvent = new Customer;
	(*InitialEvent).Random(time);
	InitialEvent->ArriveTime = 0;
	InitialEvent->LeaveTime = InitialEvent->CostTime;
	CustomerEvent.OrderInsert(InitialEvent);		//插入初始事件
	while (time < CloseTime)
	{
		Customer *Event = new Customer;
		(*Event).Random(time);
		time = (*Event).ArriveTime;			//time 记录客户的到达时间
		CustomerEvent.OrderInsert(Event);
	}
}

bool Bank::Business(Customer &cus)
{
	if (cus.Type == 0)	//顾客存钱
	{
		TotalMoney += cus.Money;
		TotalTime += cus.LeaveTime - cus.ArriveTime;
		cout << "Window1\t\t" << "Money: " << cus.Money << "\tStayingTime: " << cus.LeaveTime - cus.ArriveTime << endl;
		return true;
	}
	else	//顾客取钱
	{
		if (cus.Money <= TotalMoney)
		{
			TotalMoney -= cus.Money;
			TotalTime += cus.LeaveTime - cus.ArriveTime;
			cout << "Window1\t\t" << "Money: " << cus.Money << "\tStayingTime: " << cus.LeaveTime - cus.ArriveTime << endl;
			return true;
		}
		else
		{
			Customer *tmp = new Customer;
			*tmp = cus;
			Window2.Add(tmp);
			return false;
		}
	}
}

/*void Bank::CustomerArrive(Customer &cus)
{
	CustomerNumber++;
	if (Window1.length > 0)
	{
		Customer *tmp = new Customer;
		Window1.GetFirst(tmp);
		cus->LeaveTime += tmp->LeaveTime + cus->CostTime;	//等候时间变长
		Window1.Add(cus);		//进入窗口1排队
	}
	else
	{
		Business(cus);			//否则直接处理业务
	}
}*/

bool Bank::IsMoreCustomer()
{
	if (CustomerEvent.length == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Bank::CloseForDay()
{
	while (Window2.length != 0)
	{
		Customer *tmp = new Customer;
		Window2.GetFirst(tmp);
		TotalTime += (CurrentTime - tmp->ArriveTime);
		Window2.DeleteFirst();
	}
	cout << "Customer Number:" << CustomerNumber << endl;
	cout << "Total Time:" << TotalTime << endl;
	cout << "Average Time:";
	cout << (TotalTime * 1.0) /CustomerNumber << endl;
}

void Bank::CheckWindow1()
{
	if (Window1.length == 0)
	{
		return;
	}
	Customer *ptr = new Customer;
	Window1.GetFirst(ptr);
	while (ptr->LeaveTime <= CurrentTime)
	{
		if(Business(*ptr))
		{
			Window1.DeleteFirst();
			Window1.GetFirst(ptr);
		}
		else
		{
			ptr = ptr->next;
		}
	}
}

bool Bank::CheckWindow2(int total_money)
{
	int len = 1;
	if (Window2.length == 0)
	{
		return false;
	}
	Customer *ptr = Window2.head->next;
	while (len <= Window2.length)
	{
		if (ptr->Money <= total_money)
		{
			return true;
		}
		ptr = ptr->next;
		Window2.tail->next = Window2.head->next;
		Window2.head->next = ptr;
		len++;
	}
	return false;
}

#endif
