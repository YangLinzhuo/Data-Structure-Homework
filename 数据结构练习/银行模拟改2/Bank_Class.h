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
#include "Event_Class.h"
#include "Event_List_Class.h"
#include "Customer_Class.h"
#include "Customer_Queue_Class.h"

using namespace std;

void Bank::OpenForDay()				//生成客户到达事件
{
	int time = 0;
	while (time < close_time)
	{
		Event *event = new Event;
		(*event).Random(time);
		time = event->occur_time;			//time 记录客户的到达时间
		CustomerEvent.OrderInsert(event);
	}
}

void Bank::CloseForDay()				//处理还未办理业务的客户
{
	while (Window1.length != 0)
	{
		Customer tmp;
		tmp = Window1.GetFirst();
		total_time += (current_time - tmp.arrive_time);
		Window1.DeleteFirst();
	}
	
	while (Window2.length != 0)
	{
		Customer tmp;
		tmp = Window2.GetFirst();
		total_time += (current_time - tmp.arrive_time);
		Window2.DeleteFirst();
	}

	cout << "Customer Number:" << customer_number << endl;
	cout << "Total Time:" << total_time << endl;
	cout << "Average Time:";
	cout << (total_time * 1.0) / customer_number << endl;
	cout << "Customer Success Number:" << customer_success << endl;
}
		

void Bank::DealEvent(Event e)
{
	if (e.type == 0)	//客户到达事件
	{
		customer_number++;
		Customer *ptr = new Customer;
		(*ptr).Random();
		ptr->arrive_time = current_time;
		Window1.AddEnd(ptr);
	}
	else				//客户离开事件
	{
		//检查窗口删除离开客户
		Check();
	}
}

void Bank::Check()		//处理客户队列，检查是否有离开客户
{
	Customer *ptr;
	ptr = Window1.head->next;
	if (ptr && ptr->leave_time == current_time)	//队列不为空且离开时刻为当前时刻
	{
		Window1.DeleteFirst();
	}

	ptr = Window2.head->next;
	if (ptr && ptr->leave_time == current_time)	//队列不为空且离开时刻为当前时刻
	{
		Window2.DeleteFirst();
	}
}

void Bank::DealBusiness()		//处理业务
{
	if(DealWindow1())	//若窗口1办理的业务为存钱，则处理窗口2
	{	
		DealWindow2();
	}
}

bool Bank::DealWindow1()			//办理窗口1业务
{
	if (Window1.length == 0)
	{
		return false;
	}

	Customer *ptr;
	ptr = Window1.head->next;
	if (ptr->leave_time == 0)	//未办理业务
	{
		if (!Business1(ptr))	//办理业务不成功，从窗口1中离开
		{
			Window1.DeleteFirst();
			ptr = 0;
			return false;
		}
		else				//成功则插入离开事件
		{
			Event *p = new Event;
			p->type = 1;	//事件类型为离开
			p->occur_time = ptr->leave_time;
			CustomerEvent.OrderInsert(p);
			return true;
		}
	}
	return false;
}

bool Bank::DealWindow2()			//检查队列中成员的金额是否可以满足
{
	if(Window2.length == 0)
	{
		return false;
	}

	Customer *ptr = Window2.head->next;
	Customer *ptr_pre = Window2.head;
	if (ptr->leave_time == 0)	//寻找是否有金额满足条件的顾客
	{
		while (ptr->money > total_money && ptr_pre != Window2.tail->next)	//当未找到满足要求的顾客且未全部搜索完，则继续搜索
		{
			ptr_pre = ptr;
			ptr = ptr->next;
		}

		if (ptr->money <= total_money)
		{
			//头尾指针移位
			Window2.head->next = ptr;	
			Window2.tail->next = ptr->prior;
			if (Business2(ptr))
			{
				Event *p = new Event;
				p->type = 1;	//事件类型为离开
				p->occur_time = ptr->leave_time;
				CustomerEvent.OrderInsert(p);
				return true;
			}
		}
	}
}

bool Bank::Business1(Customer *ptr)		//处理窗口1的业务
{
	if (ptr->type == 0)	//顾客存钱
	{
		total_money += ptr->money;
		ptr->leave_time = current_time + ptr->cost_time;
		total_time += ptr->leave_time - ptr->arrive_time;
		cout << "Window1\t\t" << "Current_time:" << current_time << "\tType: Saving" << "\t\tMoney: " << ptr->money << "\t\tStayingTime: " << ptr->leave_time - ptr->arrive_time << endl;
		customer_success++;
		return true;
	}
	else	//顾客取钱
	{
		if (ptr->money <= total_money)
		{
			total_money -= ptr->money;
			ptr->leave_time = current_time + ptr->cost_time;
			total_time += ptr->leave_time - ptr->arrive_time;
			cout << "Window1\t\t" << "Current_time:" << current_time << "\tType: Withdrawing" << "\tMoney: " << ptr->money << "\t\tStayingTime: " << ptr->leave_time - ptr->arrive_time << endl;
			customer_success++;
			return true;
		}
		else	//银行存款不够，加入窗口2队列
		{
			Customer *tmp = new Customer;
			tmp->type = ptr->type;
			tmp->arrive_time = ptr->arrive_time;
			tmp->money = ptr->money;
			tmp->cost_time = ptr->cost_time;
			Window2.AddEnd(tmp);
			return false;
		}
	}
}

bool Bank::Business2(Customer *ptr)		//处理窗口2的业务
{
	if (!ptr)	//指针为空
	{
		return false;
	}

	total_money -= ptr->money;
	ptr->leave_time = current_time + ptr->cost_time;
	total_time += ptr->leave_time - ptr->arrive_time;
	cout << "Window2\t\t" << "Current_time:" << current_time << "\tType: Withdrawing" << "\tMoney: " << ptr->money << "\t\tStayingTime: " << ptr->leave_time - ptr->arrive_time << endl;
	return true;
}

bool Bank::IsMoreEvent()			//判断是否还有顾客
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


#endif
