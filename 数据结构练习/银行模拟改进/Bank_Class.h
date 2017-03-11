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
#include "Customer_List_Class.h"

using namespace std;
void Bank::OpenForDay()				//生成客户到达事件
{
	int time = 0;
	Customer *InitialEvent = new Customer;
	(*InitialEvent).Random(time);
	InitialEvent->arrive_time = 0;
	InitialEvent->leave_time = InitialEvent->cost_time;
	CustomerEvent.OrderInsert(InitialEvent);		//插入初始事件
	while (time < close_time)
	{
		Customer *Event = new Customer;
		(*Event).Random(time);
		time = (*Event).arrive_time;			//time 记录客户的到达时间
		CustomerEvent.OrderInsert(Event);
	}
}

void Bank::CloseForDay()			//处理还未办理业务的客户
{
	while (Window2.length != 0)
	{
		Customer tmp;
		Window2.GetFirst(tmp);
		total_time += (CurrentTime - tmp->arrive_time);
		Window2.DeleteFirst();
	}
	cout << "Customer Number:" << CustomerNumber << endl;
	cout << "Total Time:" << total_time << endl;
	cout << "Average Time:";
	cout << (total_time * 1.0) / CustomerNumber << endl;
}

void Bank::CustomerArrive(Customer &cus)	//处理客户到达事件
{
	CustomerNumber++;
	
	if (Window1.length > 0)
	{
		Customer tmp;
		Window1.GetFirst(tmp);
		Customer *person = new Customer;
		(*person).Copy(cus);
		person->leave_time += tmp.leave_time + person->cost_time;	//等候时间变长
		Window1.AddEnd(person);		//进入窗口1排队
	}
	else
	{
		Business(cus);			//否则直接处理业务
	}
}

bool Business(Customer &cus)		//处理业务
{
	if (cus.type == 0)	//顾客存钱
	{
		total_money += cus.money;
		total_time += cus.leave_time - cus.arrive_time;
		cout << "Window1\t\t" << "money: " << cus.money << "\tStayingTime: " << cus.leave_time - cus.arrive_time << endl;
		return true;
	}
	else	//顾客取钱
	{
		if (cus.money <= total_money)
		{
			total_money -= cus.money;
			total_time += cus.leave_time - cus.arrive_time;
			cout << "Window1\t\t" << "money: " << cus.money << "\tStayingTime: " << cus.leave_time - cus.arrive_time << endl;
			return true;
		}
		else	//银行存款不够，加入窗口2队列
		{
			Customer *tmp = new Customer;
			(*tmp).Copy(cus);
			Window2.AddEnd(tmp);
			return false;
		}
	}
}

bool Bank::IsMoreCustomer()			//判断是否还有顾客
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

void Bank::CheckWindow1()			//检查窗口1顾客是否办理完业务
{
	if (Window1.length == 0)
	{
		return;
	}

	Customer *ptr;
	Window1.GetFirst(*ptr);
	while (ptr->LeaveTime <= CurrentTime)
	{
		if(Business(*ptr))
		{
			Window1.DeleteFirst();
			Window1.GetFirst(*ptr);
		}
		else
		{
			ptr = ptr->next;
		}
	}
}

Customer *Bank::CheckWindow2(int total_money)			//检查队列中成员的金额是否可以满足
{
	if (Window2.length == 0)
	{
		return 0;
	}
	Customer *ptr = Window2.head->next;
	while (ptr->next != tail)
	{
		if (ptr->Money <= total_money)
		{
			return ptr;
		}
		ptr = ptr->next;
	}
	return 0;
}
#endif