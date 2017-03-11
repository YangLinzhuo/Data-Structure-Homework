/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#include <iostream>
#include "Bank_Simulation.h"
#include "Customer_Class.h"
#include "Bank_Class.h"
#include "CustomerList_Class.h" 

using namespace std;

int main()
{
	Bank B;
	B.OpenForDay();
	while (B.IsMoreCustomer() && B.CurrentTime < B.CloseTime)
	{
		Customer *cus = new Customer;
		B.CustomerEvent.GetFirst(cus);
		B.CurrentTime = cus->ArriveTime;
		B.CheckWindow1();
		B.CustomerNumber++;
		if (B.Window1.length > 0)
		{
			Customer *tmp = new Customer;
			B.Window1.GetFirst(tmp);
			cus->ArriveTime += tmp->LeaveTime + cus->CostTime;	//等候时间变长
			B.Window1.Add(cus);		//进入窗口1排队
		}
		else
		{
			B.Business(*cus);			//否则直接处理业务
		}
		
		int pre_cost_time = 0;	//前一顾客办理业务花费时间
		while (B.CheckWindow2(B.TotalMoney))
		{
			Customer *tmp = new Customer;
			B.Window2.GetFirst(tmp);
			tmp->LeaveTime += pre_cost_time;
			B.TotalMoney -= tmp->Money;
			B.TotalTime += (tmp->LeaveTime - tmp->ArriveTime);
			cout << "Window2\t\t" << "Money: " << tmp->Money << "\tStayingTime: " << tmp->LeaveTime - tmp->ArriveTime << endl;
			pre_cost_time = tmp->CostTime;
			B.Window2.DeleteFirst();
		}
		B.CustomerEvent.DeleteFirst();
	}
	B.CloseForDay();
}

//主要问题  产生的随机数随机性不够
//传递参数时候的问题
//指针为空的问题  向队列中添加元素的时候，和头尾指针有关的赋值语句少了一条
//银行少了一个窗口导致计算顾客停留时间不对
