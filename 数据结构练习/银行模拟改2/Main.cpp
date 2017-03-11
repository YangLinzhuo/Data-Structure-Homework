/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#include "Bank_Simulation.h"
#include "Event_Class.h"
#include "Event_List_Class.h"
#include "Customer_Class.h"
#include "Customer_Queue_Class.h"
#include "Bank_Class.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	Bank B;
	B.OpenForDay();
	while (B.IsMoreEvent() && B.current_time <= B.close_time)
	{
		Event e;
		Customer c;
		e = B.CustomerEvent.GetFirst();
		if (e.occur_time > B.close_time)	//事件发生的时间超过关门时间
		{
			break;
		}
		B.current_time = e.occur_time;
		B.DealEvent(e);
		B.DealBusiness();
		B.CustomerEvent.DeleteFirst();
	}
	B.current_time = B.close_time;
	B.CloseForDay();
	return 0;
}

//主要问题  产生的随机数随机性不够
//指针为空的问题  向队列中添加元素的时候，和头尾指针有关的赋值语句少了一条
//银行少了一个窗口导致计算顾客停留时间不对
//在函数中生成随机数种子，导致每次调用时取的种子全部相同，最后在主程序中设置好才解决