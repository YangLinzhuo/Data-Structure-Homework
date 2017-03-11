#include <iostream>
#include <cmath>
#include "Polynomial.h"
using namespace std;

int Term::compare(Term b)
{
	if (exp < b.exp)
	{
		return -1;
	}
	else if (exp == b.exp)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void Polynomial::Clear()
{
	Term *ptr = head->next;
	if (ptr == tail)
	{
		return;
	}
	while (ptr != tail)
	{
		Term *tmp = ptr;
		ptr->next->prior = ptr->prior;
		ptr->prior->next = ptr->next;
		ptr = ptr->next;
		delete tmp;
		length--;
	}
}

bool Polynomial::Locate(Term el)
{
	Term *ptr = head->next;
	while (ptr != tail)
	{
		if (!(*ptr).compare(el))
		{
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}

bool Polynomial::OrderInsert(Term *el)
{
	Term *tm = new Term;
	tm->coe = el->coe;
	tm->exp = el->exp;
	if (!tm)
	{	
		return false;
	}
	if (length == 0)	//表为空
	{
		head->next = tail->prior = tm;
		tm->prior = head, tm->next = tail;
		length++;
		return true;
	}
	
	Term *ptr = head->next;
	while (ptr != tail)
	{
		int cmp = (*ptr).compare(*tm);
		if (cmp < 0)
		{
			ptr = ptr->next;
		}
		else if (cmp > 0)
		{
			tm->next = ptr;
			tm->prior = ptr->prior;
			ptr->prior->next = tm;
			ptr->prior = tm;
			length++;
			return true;
		}
		else
		{
			if (abs(ptr->coe + tm->coe) < 1e-10)
			{
				ptr->prior->next = ptr->next;
				ptr->next->prior = ptr->prior;
				delete ptr;
				return false;
			}
			else
			{
				ptr->coe += tm->coe;
				return true;
			}
		}
	}
	tail->prior->next = tm;
	tm->prior = tail->prior;
	tm->next = tail;
	tail->prior = tm;
	length++;
	return true;
}

void Polynomial::Create(int num)
{
	Term tmp;
	for (int i = 0; i < num; ++i)
	{
		cin >> tmp.coe >> tmp.exp;
		OrderInsert(&tmp);
	}
}

void Polynomial::PrintPolyn()
{
	if (length == 0)
	{
		cout << 0 << endl;
		return;
	}
	Term *ptr = tail->prior;
	int count = 0;
	while (ptr != head)
	{
		if (ptr->coe == 0 && length != 1)
		{
			ptr = ptr->prior;
			continue;
		}
		if (count != 0 && ptr->coe > 0)
		{
			cout << '+';
		}
		
		if (ptr->exp == 0)
		{
			cout << ptr->coe;
		}
		else
		{
			if(abs(abs(ptr->coe) - 1) < 1e-10)
			{
				if (ptr->coe < 0)
				{
					cout << '-';
				}
			}
			else
			{
				cout << ptr->coe;
			}
			cout << 'x';
			if (ptr->exp > 1 || ptr->exp < 0)
			{
				cout << '^' << ptr->exp;
			}
		}
		count++;
		ptr = ptr->prior;
	}
	cout << endl;
}

void Polynomial::PrintLength()
{
	cout << length << endl;
}


Polynomial Polynomial::Addition(const Polynomial B)		//和多项式 B 相加，加完后删去 B
{
	Polynomial Result;
	Term *ptr = head->next;
	Term *ptr_B = (B.head)->next;
	Term tmp;
	double sum_coe;
	while (ptr != tail && ptr_B != B.tail)
	{
		switch((*ptr).compare(*ptr_B))
		{
			case 0:		//指数相等
				sum_coe = ptr->coe + ptr_B->coe;
				if (abs(sum_coe) > 1e-10)
				{
					tmp.coe = sum_coe;
					tmp.exp = ptr->exp;
					Result.OrderInsert(&tmp);
					Result.length++;
				}
				ptr = ptr->next;
				ptr_B = ptr_B->next;
				break;
			case -1:  //指数 小于 B
				Result.OrderInsert(ptr);
				Result.length++;
				ptr = ptr->next;
				break;
			case 1:		//指数大于 B  将 ptr_B 插入
				Result.OrderInsert(ptr_B);
				Result.length++;
				ptr_B = ptr_B->next;
				break;
		}
	}
	while (ptr != tail)
	{
		if (ptr->coe != 0)
		{
			Result.OrderInsert(ptr);
		}
		ptr = ptr->next;
	}
	while (ptr_B != B.tail)
	{
		if (ptr_B->coe != 0)
		{
			Result.OrderInsert(ptr_B);
		}
		ptr_B = ptr_B->next; 
	}
	return Result;
}

Polynomial Polynomial::operator+(const Polynomial B)
{
	return Addition(B);
}

Polynomial Polynomial::Subtraction(const Polynomial B)
{
	Polynomial Result;
	Polynomial C;
	Term *ptr_B = B.head->next;
	while (ptr_B != B.tail)
	{
		Term *tmp = new Term;
		tmp->coe = -(ptr_B->coe);
		tmp->exp = ptr_B->exp;
		ptr_B = ptr_B->next;
		C.OrderInsert(tmp);
	}
	Result = Addition(C);
	return Result;
}

Polynomial Polynomial::operator-(const Polynomial B)
{
	return Subtraction(B);
}

Polynomial Polynomial::Multiplication(const Polynomial B)
{
	Polynomial Result;
	Term *ptr = head->next;
	Term *ptr_B = (B.head)->next;
	Term *tmp = new Term;
	while (ptr_B != B.tail)
	{
		Polynomial Temp;
		while (ptr != tail)
		{
			tmp->coe = ptr->coe * ptr_B->coe;
			tmp->exp = ptr->exp + ptr_B->exp;
			Temp.OrderInsert(tmp);
			ptr = ptr->next;
		}
		Result = Result + Temp;
		ptr_B = ptr_B->next;
		ptr = head->next;
	}
	return Result;
}

Polynomial Polynomial::operator*(const Polynomial B)
{
	return Multiplication(B);
}


void Polynomial::Division(const Polynomial B)
{
	if (B.head->next->coe == 0)
	{
		cout << "ERROR" << endl;
		return;
	}
	Polynomial Quotient;	//商
	Polynomial Remainder_Numerator;		//余数分子	
	Polynomial Remainder_Denominator;	//余数分母
	Term *ptr = tail->prior;
	Term *ptr_B = B.tail->prior;
	Term *tmp;
	Polynomial Sub;
	if (ptr->exp < ptr_B->exp)
	{
		Remainder_Denominator = B;
		cout << "Quotient:" << 0 << endl;
		cout << "Remainder:"<< endl;
		PrintPolyn();
		return;
	}
	Sub = *this;
	while (ptr->exp >= ptr_B->exp) //剩余项最高项次数大于除数最高项次数
	{
		Polynomial Temp, Single;
		tmp = new Term;
		tmp->coe = ptr->coe / ptr_B->coe;
		tmp->exp = ptr->exp - ptr_B->exp;
		Quotient.OrderInsert(tmp);
		Single.OrderInsert(tmp);
		Sub = Sub - (Single * B);
		ptr = Sub.tail->prior;
	}
	Remainder_Numerator = Sub;
	Remainder_Denominator = B;
	cout << "Quotient:" << endl;
	Quotient.PrintPolyn();
	cout << "Remainder:"<< endl;
	Remainder_Numerator.PrintPolyn();
}

double Polynomial::Value(double x)
{
	double val = 0;
	Term *ptr = head->next;
	while (ptr != tail)
	{
		val += ptr->coe * pow(x, ptr->exp);
		ptr = ptr->next;
	}
	return val;
}

Polynomial Polynomial::Integrate()
{
	Polynomial Result;
	Term *ptr = head->next;
	while (ptr != tail)
	{
		Term *tmp = new Term;
		if (ptr->coe != 0)
		{
			tmp->coe = ptr->coe / (ptr->exp + 1);
			tmp->exp = ptr->exp + 1;
			Result.OrderInsert(tmp);
		}
		ptr = ptr->next;
	}
	return Result;
}

double Polynomial::Integrate(double start, double end)
{
	Polynomial Result;
	Term *ptr = head->next;
	while (ptr != tail)
	{
		Term *tmp = new Term;
		if (ptr->coe != 0)
		{
			tmp->coe = ptr->coe / (ptr->exp + 1);
			tmp->exp = ptr->exp + 1;
			Result.OrderInsert(tmp);
		}
		ptr = ptr->next;
	}
	return Result.Value(end) - Result.Value(start);
}

Polynomial Polynomial::Differentiate()
{
	Polynomial Result;
	Term *ptr = head->next;
	while (ptr != tail)
	{
		Term *tmp = new Term;
		if (ptr->exp == 0)
		{
			ptr = ptr->next;
			continue;
		}
		tmp->coe = ptr->coe * ptr->exp;
		tmp->exp = ptr->exp - 1;
		Result.OrderInsert(tmp);
		ptr = ptr->next;
	}
	return Result;
}

Polynomial Polynomial::Exponentiation(int n)
{
	Polynomial Result;
	Term *tmp = new Term;
	if (length == 1 && head->next->coe == 0)
	{
		return Result;
	}
	if (n == 0)
	{
		tmp->coe = 1;
		tmp->exp = 0;
		Result.OrderInsert(tmp);
		return Result;
	}
	
	Result = *this;
	if (n == 1)
	{
		return Result;
	}
	for (int i = 2; i <= n; i++)
	{
		Result = Result * (*this);
	}
}


