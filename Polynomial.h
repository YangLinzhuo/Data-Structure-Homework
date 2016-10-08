#ifndef INT_LINKED_LIST
#define INT_LINKED_LIST

class Term
{
	public:
		Term(double co = 0.0, int ex = 0, Term *ptr_prior = 0, Term *ptr_next = 0)
		{
			coe = co;
			exp = ex;
			prior = ptr_prior;
			next = ptr_next;
		}
		Term *prior;
		Term *next;
		double coe;
		int exp;
		int compare(Term);
};

class Polynomial
{
	public:
		Polynomial()
		{
			head = new Term, tail = new Term;
			head->coe = 0.0, head->exp = 0;
			tail->coe = 0.0, head->exp = 0;
			head->next = tail, tail->prior = head;
			length = 0;
		}
		Term *head;
		Term *tail;
		int length;
		void Clear();
		void DelTerm(Term*);
		bool Locate(Term);
		bool OrderInsert(Term*);
		void Create(int);	//添加项
		void PrintPolyn();	//打印多项式
		void PrintLength();	//输出长度
		Polynomial Addition(const Polynomial);	//多项式加法
		Polynomial Subtraction(const Polynomial); //多项式减法
		Polynomial Multiplication(const Polynomial);	//多项式乘法
		void Division(const Polynomial);	//多项式除法
		double Value(double);	//求值
		Polynomial Integrate();	//积分
		double Integrate(double, double);	//积分求值
		Polynomial Differentiate();		//求导
		Polynomial Exponentiation(int);		//求幂
		Polynomial operator+(const Polynomial);
		Polynomial operator-(const Polynomial);
		Polynomial operator*(const Polynomial);
		Polynomial operator/(const Polynomial);
};

#endif
