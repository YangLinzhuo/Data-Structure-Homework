/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#ifndef INIT_CUSTOMER_CLASS
#define INIT_CUSTOMER_CLASS
#include <ctime>
#include <cstdlib>
#include "Bank_Simulation.h"

void Customer::Random()		//随机生成顾客的业务类型和金额总数
{
	int min_money = 100;
	int max_money = 5000;
	int min_cost_time = 1;
	int max_cost_time = 10;
	type = rand() % (1 + 1);
	money = min_money + (int) (max_money - min_money) * rand() / (RAND_MAX + 1);		//金额在 100~5000 之间
	cost_time = min_cost_time + (int) (max_cost_time - min_cost_time) * rand() / (RAND_MAX + 1);	//办理业务时间在 1~10 分钟之间	
}

#endif
