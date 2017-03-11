/* 多项式链表存储 加、减、乘算法实现
 * Author: YangLinzhuo
 * Found Date: 2016/9/24
 * Latest Update Date: 2016/10/4
 */
 
#include <iostream>
#include <cmath>
#include <string>
#include "Polynomial.h"
#include "Polynomial_Class.h"

#define MAX 12

void InterAction()
{
	string line(25, '*');
	cout << line << endl;
	cout << "0.End." << endl;
	cout << "1.Create a Polynomial." << endl;
	cout << "2.Addition." << endl;
	cout << "3.Subtraction." << endl;
	cout << "4.Multiplication." << endl;
	cout << "5.Division." << endl;
	cout << "6.Integrate." << endl;
	cout << "7.Differentiate." << endl;
	cout << "8.Exponentiation." << endl;
	cout << "9.Print all Polynomials." << endl;
	cout << "10.Calculate Value."	<< endl;
	cout << "11.Delete Polynomial." << endl;
	cout << line << endl;	
}


Polynomial P[MAX];
int totalNum = 2;
Polynomial Result;

void Initial()
{
	int num = 10;
	for (int i = 1; i <= num; i++)
	{
		Term *tmp = new Term;
		tmp->coe = tmp->exp = i;
		P[0].OrderInsert(tmp);
	}
	for (int i = 15; i > num; i--)
	{
		Term *tmp = new Term;
		tmp->coe = tmp->exp = i;
		P[1].OrderInsert(tmp);
	}
}

void Function1(int number)
{
	int obj1, obj2;
	cout << "Please enter the objects(two int numbers):";
	cin >> obj1 >> obj2;
	switch(number)
	{
		case 2:
			Result = P[obj1] + P[obj2];
			Result.PrintPolyn();
			break;
		case 3:
			Result = P[obj1] - P[obj2];
			Result.PrintPolyn();
			break;
		case 4:
			Result = P[obj1] * P[obj2];
			Result.PrintPolyn();
			break;
		case 5:
			P[obj1].Division(P[obj2]);
			break;
	}
}

void Function2(int number)
{
	int obj;
	cout << "Please enter the object(one int number):";
	cin >> obj;
	switch(number)
	{
		case 6:
			Result = P[obj].Integrate();
			Result.PrintPolyn();
			break;
		case 7:
			Result = P[obj].Differentiate();
			Result.PrintPolyn();
			break;
		case 8:
			int n;
			cout << "Please enter the power(one int number):";
			cin >> n;
			Result = P[obj].Exponentiation(n);
			Result.PrintPolyn();
			break;
	}
}

int main()
{
	int number;
	Initial();
	InterAction();
	int obj;
	cout << "Please enter a corresponding number to do a function:";
	cin >> number;
	while (number)
	{	
		switch(number)
		{
			case 1:
				int num;
				cout << "Please enter the number of terms in this Polynomial:";
				cin >> num;
				for (int i = 0; i < MAX; i++)
				{
					if (P[i].head->next == P[i].tail)
					{	
						P[i].Create(num);
						totalNum++;
						break;
					}
				}
				break;
			case 2:
				Function1(2);
				break;
			case 3:
				Function1(3);
				break;
			case 4:
				Function1(4);
				break; 
			case 5:
				Function1(5);
				break;
			case 6:
				Function2(6);
				break;
			case 7:
				Function2(7);
				break;
			case 8:
				Function2(8);
				break;
			case 9:
				int i, count;
				if (totalNum == 0)
				{
					cout << "None" << endl;
					break;
				}
				for (i = 0, count = 0; i < MAX && count < totalNum; i++)
				{
					if (P[i].head->next != P[i].tail)
					{
						cout << "P[" << i << "]:  ";
						P[i].PrintPolyn();
						count++;
					}
				}
				break;
			case 10:
				cout << "Please enter the object:";
				cin >> obj;
				double x;
				cout << "Please enter the value of x:";
				cin >> x;
				cout << P[obj].Value(x) << endl;
				break;
			case 11:
				cout << "Please enter the object:";
				cin >> obj;
				P[obj].Clear();
				totalNum--;
				break;
		}
		InterAction();
		cout << "Please enter a corresponding number to do a function:";
		cin >> number;
	}
	return 0;
}
