/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#ifndef INIT_CUSTOMER_CLASS
#define INIT_CUSTOMER_CLASS
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Bank_Simulation.h"
#define INTERNAL_MAX_TIME 10
using namespace std;

void Customer::Copy(Customer cus)
{
	type = cus.type;
	money = cus.money;
	arrive_time = cus.arrive_time;
	cost_time = cus.cost_time;
	leave_time = cus.leave_time;
}

void Customer::Random(int Lastarrive_time)
{
	srand((int)time(NULL));
	type = rand() % (1 + 1);
	arrive_time = Lastarrive_time + 1 + rand() % (INTERNAL_MAX_TIME + 1);  //产生1~INTERNAL_MAX_TIME之间的数 到达时间在上一个顾客到达之后若干时间
	money = 100 + rand() % (4900 + 1);		//金额在 100~5000 之间
	cost_time = 1 + rand() % (10 + 1);	//办理业务时间在 1~10 分钟之间
	leave_time = arrive_time + cost_time;	
}

int Customer::compare(Customer b)
{
	if (arrive_time < b.arrive_time)
	{
		return -1;
	}
	else if (arrive_time == b.arrive_time)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
#endif
