/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#ifndef INIT_BANK_SIMULATION
#define INIT_BANK_SIMULATION
#define DEPOSIT 0
#define WITHDRAW 1
#define DEPARTURE -1
 
class Customer
{
	public:
		int Type;
		double Money;
		int ArriveTime;
		int CostTime;		//办理业务所需时间
		int LeaveTime;
		Customer *next;
		Customer(int type = 0, double money = 100, Customer *nx = 0)
		{
			Type = type;
			Money = money;
			next = nx;
			ArriveTime = 0;
			CostTime = 0;
			LeaveTime = 0;
		}
		void Random(int);		//随机生成顾客的业务类型和金额总数，传递的参数是上一个顾客的到达时间
		int compare(Customer);	//比较两个事件的先后顺序
};

class CustomerList
{
	public:
		Customer *head, *tail;
		int length;
		CustomerList()
		{
			head = new Customer;
			tail = new Customer;
			head->next = 0;
			tail->next = 0;
			length = 0;
		}
		bool OrderInsert(Customer *);		//顺序插入事件
		bool GetFirst(Customer *);		//获取当前第一个事件
		bool DeleteFirst();				//删除第一个事件
		bool Add(Customer *);			//在队尾加入成员
};

class Bank
{
	public:
		int OpenTime;		//时间以分钟为单位
		int CloseTime;
		int TotalTime;
		int CustomerNumber;	//记录办理业务的顾客总数
		int CurrentTime;	//记录当前时间
		double TotalMoney;	//金钱以元为单位
		CustomerList CustomerEvent;
		CustomerList Window1;
		CustomerList Window2;
		Bank(int open_time = 0, int close_time = 600, double total_money = 1000000)
		{
			OpenTime = open_time;
			CloseTime = close_time;
			TotalMoney = total_money;
			TotalTime = 0;
			CustomerNumber = 0;
			CurrentTime = 0;
		}
		void OpenForDay();				//生成客户到达事件
		void CloseForDay();				//处理还未办理业务的客户
		void CustomerArrive(Customer &);	//处理客户到达事件
		bool Business(Customer &);		//处理业务
		bool IsMoreCustomer();			//判断是否还有顾客
		void CheckWindow1();			//检查窗口1顾客是否办理完业务
		bool CheckWindow2(int);			//检查队列中成员的金额是否可以满足
};

#endif
