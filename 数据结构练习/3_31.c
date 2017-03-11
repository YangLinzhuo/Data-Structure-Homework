/*
 *	判断字符串是否是回文
 */
 
#include <stdio.h>
#include <stdlib.h>

int isHuiWen(char *str)
{
	int flag = 1;
	char *head, *rear;
	head = str;
	rear = str;
	while (*rear != '@')
	{
		rear++;
	}
	rear--;
	while (head <= rear)
	{
		if (*head != *rear)
		{
			flag = 0;
			break;
		}
		head++;
		rear--;
	}
	return flag;
}

#define INIT_SIZE 100
int main()
{
	char *str = (char *)malloc(sizeof(char) * INIT_SIZE);
	scanf("%s",str);
	printf("%d",isHuiWen(str));
	return 0;
}
