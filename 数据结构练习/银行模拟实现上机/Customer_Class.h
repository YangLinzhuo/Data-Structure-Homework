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

void Customer::Random(int LastArriveTime)
{
	srand((int)time(NULL));
	Type = rand() % (1 + 1);
	ArriveTime = LastArriveTime + 1 + rand() % (INTERNAL_MAX_TIME + 1);  //产生1~INTERNAL_MAX_TIME之间的数 到达时间在上一个顾客到达之后若干时间
	Money = 100 + rand() % (4900 + 1);		//金额在 100~5000 之间
	CostTime = 1 + rand() % (10 + 1);	//办理业务时间在 1~10 分钟之间
	LeaveTime = ArriveTime + CostTime;	
}

int Customer::compare(Customer b)
{
	if (ArriveTime < b.ArriveTime)
	{
		return -1;
	}
	else if (ArriveTime == b.ArriveTime)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

#endif