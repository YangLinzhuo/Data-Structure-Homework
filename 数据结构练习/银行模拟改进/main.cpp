/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#include <iostream>
#include "Bank_Simulation.h"
#include "Customer_Class.cpp"
#include "Bank_Class.cpp"
#include "Customer_List_Class.cpp" 

using namespace std;

int main()
{
	Bank B;
	B.OpenForDay();
	while (B.IsMoreCustomer() && B.current_time < B.close_time)
	{
		Customer *cus = new Customer;
		cus = B.CustomerEvent.head->next;
		B.current_time = cus->arrive_time;
		B.CheckWindow1();
		B.customer_number++;
		B.CustomerArrive(*cus);
		
		int pre_cost_time = 0;	//前一顾客办理业务花费时间
		Customer *ptr;
		ptr = B.CheckWindow2(B.total_money);
		while (ptr)		//存在客户的金额满足时
		{
			Customer *tmp = new Customer;
			B.Window2.GetFirst(*tmp);
			tmp->leave_time += pre_cost_time;
			B.total_money -= tmp->money;
			B.total_time += (tmp->leave_time - tmp->arrive_time);
			cout << "Window2\t\t" << "Money: " << tmp->money << "\tStayingTime: " << tmp->leave_time - tmp->arrive_time << endl;
			pre_cost_time = tmp->cost_time;
			B.Window2.DeleteFirst();
			delete tmp;
			ptr = B.CheckWindow2(B.total_money);
		}
		delete cus;
		cus = cus->next;
		B.CustomerEvent.DeleteFirst();
	}
	B.CloseForDay();
}
