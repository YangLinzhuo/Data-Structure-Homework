//******* intSLList.cpp

#include <iostream.h>
#include "intSLList.h"

IntSLList::~IntSLList ()	//销毁链表
{
	for (IntSLLNode *p; !isEmpty();)
	{
		p = head->next;
		delete head;
		head = p;
	}
}

void IntSLList::addToHead (int el)
{
	head = new IntSLLNode(el, head);	//分配空间给 el, 令其指向 head 然后再让 head 指向此指针
	if (tail == 0)
		tail = head;	//如果 tail 为空，令其指向 head
}

void IntSLList::addToTail (int el)
{
	if (tail != 0)	//if list is not empty
	{
		tail->next = new IntSLLNode(el);	//分配空间给 el, 其尾指针为空
		tail = tail->next;	//尾指针后移
	}
	else
		head = tail = new IntSLLNode(el);	//否则初始化链表
}

int IntSLList::deleteFromHead ()
{
	int el = head->info;
	IntSLLNode *tmp = head;
	if (head == tail)	//if only one node in the list;
		head = tail = 0;
	else
		head = head->next;
	delete tmp;
	return el;
}

int IntSLList::deleteFromTail ()
{
	int el = tail->info;
	if (head == tail)	//if only one node in the list;
	{
		delete head;
		head = tail = 0;
	}
	else	//if more than one node in the list
	{
		IntSLLNode *tmp;	//find the predecessor of tail
		for (tmp = head; tmp->next != tail; tmp = tmp->next); 
		delete tail;
		tail = tmp;	//the predecessor of tail becomes tail
		tail->next = 0;
	}
	return el;
}

void IntSLList::deleteNode (int el)
{
	if (head != 0)	//if nonempty list
		if (head == tail && el == head->info)	//if only one node in the list
		{
			delete head;
			head = tail = 0;
		}
		else if (el == head->info)	//if more than one node in the list
		{
			IntSLLNode *tmp = head;
			head = head->next;
			delete tmp;			//and old head is deleted
		}
		else
		{
			IntSLLNode *pred, *tmp;		//if more than one node in the list
			for (pred = head, tmp = head->next;	//and a nonehead node
				 tmp != 0 && !(tmp->info == el); //is deleted
				 pred = pred->next, tmp = tmp->next);
			if (tmp != 0)
			{
				pred->next = tmp->next;
				if (tmp == tail)
					tail = pred;
				delete tmp;
			}
		}
}

bool IntSLList::isInList (int el) const
{
	IntSLLNode *tmp;
	for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
	return tmp != 0;
}


