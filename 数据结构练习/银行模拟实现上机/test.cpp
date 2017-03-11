#define Deposit 0
#define Withdraw 1
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Customer
{
	public:
		int Type;
		double Money;
		int ArriveTime;
		Customer *next;
		Customer(int type = 0, double money = 100, Customer *nx = 0)
		{
			Type = type;
			Money = money;
			next = nx;
		}
		void Random();	//随机生成顾客的业务类型和金额总数
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
		bool GetFirst(Customer &);		//获取当前第一个事件
		bool DeleteFirst();				//删除第一个事件
		bool Add(Customer *);		//在队尾加入成员
		bool DeleteHead();	//删除队头元素
		bool Check(int);	//检查队列中成员的金额是否可以满足
};

class Bank
{
	public:
		int OpenTime;		//时间以分钟为单位
		int CloseTime;
		int TotalTime;
		int CustomerNumber;
		int CurrentTime;	//记录当前时间
		double TotalMoney;	//金钱以元为单位
		CustomerList Window1;
		CustomerList Window2;
		Bank(int open_time = 0, int close_time = 600, double total_money = 10000)
		{
			OpenTime = open_time;
			CloseTime = close_time;
			TotalMoney = total_money;
			TotalTime = 0;
			CustomerNumber = 0;
			CurrentTime = 0;
		}
		void OpenForDay();
		void CloseForDay();
		void CustomerArrive(Customer);	//处理客户到达事件
		bool IsMoreCustomer();	//
};

void Customer::Random()
{
	srand((int)time(NULL));
	Type = rand() % (1 + 1);
	ArriveTime = rand() % (10 + 1); //产生0~600之间的数
	Money = 100 + rand() % (49900 + 1);	//金额在 100~50000 之间
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

bool CustomerList::OrderInsert(Customer *e)
{
	Customer *ptr = head->next;
	Customer *ptr_pre = head;
	if (!e)
	{
		return false;
	}
	if (length == 0)
	{
		head->next = e;
		tail->next = e;
		length++;
		return true;
	}
	if (length == 1)
	{
		if ((*ptr).compare(*e) == -1)
		{
			head->next->next = e;
			tail->next = e;
		}
		else
		{
			e->next = head->next;
			head->next = e;
		}
		length++;
		return true;
	}
	while (ptr)
	{
		if ((*ptr).compare(*e) == -1)
		{
			ptr_pre = ptr;
			ptr = ptr->next;
		}
		else
		{
			e->next = ptr;
			ptr_pre->next = e;
			length++;
			return true;
		}
	}
	ptr_pre->next = e;
	e->next = 0;
	tail->next = e;
	length++;
	return true;
}

bool CustomerList::GetFirst(Customer &e)
{
	if (length == 0)
	{
		return false;
	}
	else 
	{
		e = *(head->next);
		return true;
	}
}

bool CustomerList::DeleteFirst()
{
	Customer *tmp;
	if (length == 0)
	{
		return false;
	}
	if (length == 1)
	{
		tmp = head->next;
		head->next = 0;
		tail->next = 0;
		delete tmp;
		length--;
		return true;
	}
	else
	{
		tmp = head->next;
		head->next = head->next->next;
		delete tmp;
		length--;
		return true;
	}
}


bool CustomerList::Add(Customer *customer)
{
	if (!customer)
	{
		return false;
	}
	if (length == 0)
	{
		head->next = customer;
		tail->next = customer;
		customer->next = customer;
	}
	else
	{
		tail->next->next = customer;
		customer->next = head->next;
	}
	length++;
	return true;
}

bool CustomerList::DeleteHead()
{
	if (!head->next)	//队列为空
	{
		return false;
	}
	Customer *tmp;
	if (length == 1)	//如果队列只有一个元素
	{
		tmp = head->next;
		head->next = 0;
		tail->next = 0;
		delete tmp;
	}
	else
	{
		tmp = head->next;
		head->next = head->next->next;
		tail->next->next = head->next;
		delete tmp;
	}
	length--;
	return true;
}

bool CustomerList::Check(int total_money)
{
	int len = 1;
	if (head->next == 0)
	{
		return false;
	}
	Customer *ptr = head->next;
	while (len <= length)
	{
		if (ptr->Money <= total_money)
		{
			return true;
		}
		ptr = ptr->next;
		tail->next = head->next;
		head->next = ptr;
		len++;
	}
	return false;
}

void Bank::OpenForDay()
{
	Customer *InitialEvent = new Customer;
	(*InitialEvent).Random();
	(*InitialEvent).ArriveTime = 0;
	Window1.OrderInsert(InitialEvent);
}

void Bank::CustomerArrive(Customer cus)
{
	CustomerNumber++;
	srand((int)time(NULL));
	int durtime = rand() % (5 + 1);		//逗留时间
	int intertime = rand() % (10 + 1);	//下个顾客到达间隔时间
	Customer *new_customer = new Customer;
	(*new_customer).Random();
	(*new_customer).ArriveTime = CurrentTime + intertime;
	if (cus.ArriveTime <= CloseTime)
	{
		Window1.OrderInsert(new_customer);
	}
	
	if (cus.Type == 0)	//顾客存钱
	{
		TotalMoney += cus.Money;

		TotalTime += durtime;
		if (Window2.Check(TotalMoney))
		{
			Customer tmp;
			Window2.GetFirst(tmp);
			TotalMoney -= tmp.Money;
			TotalTime += CurrentTime - tmp.ArriveTime;
			Window2.DeleteHead();
		}
	}
	else	//顾客取钱
	{
		if (cus.Money <= TotalMoney)
		{
			TotalMoney -= cus.Money;
			TotalTime += durtime;
		}
		else
		{
			Customer *tmp = new Customer;
			(*tmp) = cus;
			Window2.Add(tmp);
		}
	}
}

bool Bank::IsMoreCustomer()
{
	if (Window1.length == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Bank::CloseForDay()
{
	while (Window2.length != 0)
	{
		Customer tmp;
		Window2.GetFirst(tmp);
		TotalTime += (CurrentTime - tmp.ArriveTime);
		Window2.DeleteHead();
	}
	cout << "Customer Number:" << CustomerNumber << endl;
	cout << "Total Time:" << TotalTime << endl;
	cout << "Average Time:";
	cout << (TotalTime * 1.0) /CustomerNumber << endl;
}

int main()
{
	Bank B;
	B.OpenForDay();
	while (B.IsMoreCustomer() && B.CurrentTime <= B.CloseTime)
	{
		Customer *cus = new Customer;
		B.Window1.GetFirst(*cus);
		B.CurrentTime = cus->ArriveTime;
		B.CustomerArrive(*cus);
		B.Window1.DeleteFirst();
		while (B.Window2.Check(B.TotalMoney))
		{
			Customer tmp;
			B.Window2.GetFirst(tmp);
			B.TotalMoney -= tmp.Money;
			B.TotalTime += (B.CurrentTime - tmp.ArriveTime);
			B.Window2.DeleteHead();
		}
	}
	B.CloseForDay();
}
