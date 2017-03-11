/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#ifndef INIT_EVENT_CLASS
#define INIT_EVENT_CLASS
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Bank_Simulation.h"

void Event::Random(int last_arrive_time)		//随机生成顾客的到达时间
{
	int min_time = 1;
	int max_time = 10;
	type = 0;	//事件类型为顾客到达
	occur_time = last_arrive_time + min_time + (int) (max_time - min_time) * rand() / (RAND_MAX  + 1);  //产生1~max_time之间的数 到达时间在上一个顾客到达之后若干时间
}

int Event::Compare(Event b)		//比较两个事件的先后顺序
{
	if (occur_time < b.occur_time)
	{
		return -1;
	}
	else if (occur_time == b.occur_time)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
#endif
