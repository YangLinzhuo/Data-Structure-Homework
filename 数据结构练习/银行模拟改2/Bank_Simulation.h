/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#ifndef INIT_BANK_SIMULATION
#define INIT_BANK_SIMULATION

class Event
{
	public:
		int type;	//事件类型 0表示到达，1表示离开
		int occur_time;		//事件发生时间
		Event *next;	//指向下一个事件
		Event()
		{
			type = 0;
			occur_time = 0;
			next = 0;
		}
		void Random(int);		//随机生成顾客的到达时间
		int Compare(Event);		//比较两个事件的先后顺序
};

class EventList
{
	public:
		Event *head;	//指向链表头元素
		int length;		//链表长度
		EventList()
		{
			head = new Event;
			head->next = 0;
			head->type = 0;
			head->occur_time = 0;
		}
		bool OrderInsert(Event *);		//顺序插入
		Event GetFirst();			//获取头元素	
		bool DeleteFirst();		//删除头元素
		bool IsEmpty();			//判断是否为空
};

class Customer
{
	public:
		int type;
		int money;
		int arrive_time;
		int cost_time;
		int leave_time;
		Customer *prior;
		Customer *next;
		Customer(int ArriveTime = 0)
		{
			type = 0;
			money = 0;
			arrive_time = 0;
			cost_time = 0;
			leave_time = 0;		//初始值为0，若为0，说明未办理业务，否则成功办理了业务
			prior = 0;
			next = 0;
		}
		void Random();		//随机生成顾客的业务类型和金额总数
};

class CustomerQueue
{
	public:
		Customer *head;		//指向队列头元素
		Customer *tail;		//指向队列尾元素
		int length;			//队列长度
		CustomerQueue()
		{
			head = new Customer;
			tail = new Customer;
			head->prior = 0;
			head->next = tail;
			tail->prior = 0;
			tail->next = head;
			length = 0;
		}
		Customer GetFirst();			//获取头元素	
		bool DeleteFirst();				//删除头元素
		bool AddEnd(Customer *);		//在尾结点后插入
};

class Bank
{
	public:
		int open_time;		//时间以分钟为单位
		int close_time;
		int total_time;
		int customer_number;	//记录办理业务的顾客总数
		int customer_success;	//记录成功办理业务的顾客
		int current_time;		//记录当前时间
		double total_money;		//金钱以元为单位
		EventList CustomerEvent;	//顾客时间链表
		CustomerQueue Window1;		//窗口1
		CustomerQueue Window2;		//窗口2
		Bank(int OpenTime = 0, int CloseTime = 600, double TotalMoney = 10000)
		{
			open_time = OpenTime;
			close_time = CloseTime;
			total_money = TotalMoney;
			total_time = 0;
			customer_number = 0;
			customer_success = 0;
			current_time = 0;
		}
		void OpenForDay();				//生成客户到达事件
		void CloseForDay();				//处理还未办理业务的客户
		void DealEvent(Event);				//处理客户事件
		void Check();
		void DealBusiness();		//处理业务
		bool DealWindow1();			//检查窗口1顾客是否办理完业务
		bool DealWindow2();			//检查队列中成员的金额是否可以满足
		bool Business1(Customer *);	//处理窗口1的业务
		bool Business2(Customer *);	//处理窗口2的业务
		bool IsMoreEvent();
};

#endif
