/*
	Bank_Simulation
	Author: YangLinzhuo
	Found Date: 2016/10/4
	Update Date: None
 */

#ifndef INIT_BANK_SIMULATION
#define INIT_BANK_SIMULATION
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
		Customer()
		{
			type = 0;
			money = 0;
			arrive_time = 0;
			cost_time = 0;
			leave_time = 0;
			prior = 0;
			next = 0;
		}
		void Copy(Customer);	//复制
		void Random(int);		//随机生成顾客的业务类型和金额总数，传递的参数是上一个顾客的到达时间
		int compare(Customer);	//比较两个事件的先后顺序
};

class Customer_List
{
	public:
		Customer *head;
		Customer *tail;
		int length;
		Customer_List()
		{
			head = new Customer, tail = new Customer;
			head->next = tail, tail->prior = head;
			length = 0;
		}
		bool OrderInsert(Customer *);		//顺序插入
		bool GetFirst(Customer &);			//获取头元素	
		bool DeleteFirst();		//删除头元素
		bool AddEnd(Customer *);			//在尾结点后插入
};

class Bank
{
	public:
		int open_time;		//时间以分钟为单位
		int close_time;
		int total_time;
		int customer_number;	//记录办理业务的顾客总数
		int current_time;	//记录当前时间
		double total_money;	//金钱以元为单位
		Customer_List CustomerEvent;
		Customer_List Window1;
		Customer_List Window2;
		Bank(int OT = 0, int CT = 600, double TM = 1000000)
		{
			open_time = OT;
			close_time = CT;
			total_money = TM;
			total_time = 0;
			customer_number = 0;
			current_time = 0;
		}
		void OpenForDay();				//生成客户到达事件
		void CloseForDay();				//处理还未办理业务的客户
		void CustomerArrive(Customer &);	//处理客户到达事件
		bool Business(Customer &);		//处理业务
		bool IsMoreCustomer();			//判断是否还有顾客
		void CheckWindow1();			//检查窗口1顾客是否办理完业务
		Customer *CheckWindow2(int);			//检查队列中成员的金额是否可以满足
};
#endif
