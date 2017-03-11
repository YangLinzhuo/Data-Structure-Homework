
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <graphics.h> 
/*���尴����*/
#define LEFT		0x4b00
#define RIGHT	0x4d00
#define DOWN		0x5000
#define UP 		0x4800
#define ESC		0x011b

/*���峣��*/
#define MAX_BOX		19		/*�ܹ� 19 ����̬�ķ���*/
#define BSIZE		20		/*����߳��� 20 ������*/
#define Sys_x		160 	/*��ʾ�����������Ͻ� x ����*/
#define Sys_y		25		/*��ʾ�����������Ͻ� y ����*/
#define Horizontal_boxs	10	/*ˮƽ�����Է���Ϊ��λ�ĳ���*/
#define Vertical_boxs		15	/*��ֱ�����Է���Ϊ��λ�ĳ���*/
#define Begin_boxs_x	Horizontal_boxs/2/*������һ��������ֵ���ʼλ��*/

#define FgColor	3	/*ǰ����ɫ*/
#define BgColor	0	/*������ɫ*/

#define LeftWin_x	Sys_x+Horizontal_boxs*BSIZE+46	/*�ұ�״̬���� x ����*/

#define False 0
#define True 1

/*�ƶ�����*/
#define MoveLeft	1
#define MoveRight	2
#define MoveDown	3
#define MoveRoll	4

/*
	Board and Shape
*/

struct	BOARD		/*��Ϸ�װ�ṹ����ʾÿ������е�����*/
{
	int var;		/*��ǰ״ֻ̬�� 0 �� 1 ���֣�1 ��ʾ�õ��Ѿ���ռ��*/
	int color;		/*��ɫ����Ϸ�װ��ÿ�������ӵ�в�ͬ����ɫ����ǿ������*/
}Table_board[Vertical_boxs][Horizontal_boxs];

struct SHAPE
{
	/*һ���ֽ��� 8 λ���� 4 λ��ʾ��Ϸ�����е�һ��*/
	char box[2];
	int color;		/*ÿ���������ɫ*/
	int next;		/*�¸�����ı��*/
};


struct SHAPE shapes[MAX_BOX] = 
{
	/*  �� 		�ڿڿ� 		�ڿ� 			�� 
	 *  ��      �� 			  �� 		�ڿڿ� 
	 *  �ڿ�				  �� 
	 */
	 {0x88,	0xC0, CYAN, 1},
	 {0xe8, 0x0,  CYAN, 2},
	 {0xc4, 0x40, CYAN, 3},
	 {0x2e, 0x0,  CYAN, 0},
	 
	/*    �� 				�ڿ�		�ڿڿ� 
	 *	  �� 	�� 			�� 				�� 
	 *  �ڿ�    �ڿڿ� 		�� 
	 */
	 {0x44, 0xc0, MAGENTA, 5}, 
	 {0x8e,	0x0,  MAGENTA, 6},
	 {0xc8, 0x80, MAGENTA, 7},
	 {0xe2, 0x0,  MAGENTA, 4}, 
	 
	 /*		�� 
	  *		�ڿ�		�ڿ� 
	  *		  �� 	  �ڿ� 
	  */
	  {0x8c, 0x40, YELLOW, 9},
	  {0x6c, 0x0,  YELLOW, 8},
	  
	  /*	��		�ڿ� 
	   *  �ڿ� 		  �ڿ� 
	   *  �� 
	   */ 
	   {0x4c, 0x80, BROWN, 11},
	   {0xc6, 0x0,  BROWN, 10},
	   
	   /*		�� 			�� 					  �� 
	    *	  �ڿڿ� 		�ڿ�	�ڿڿ� 		�ڿ� 
		*					�� 		  �� 		  �� 
		*/ 
		{0x4e, 0x0,  WHITE, 13},
		{0x8c, 0x80, WHITE, 14},
		{0xe4, 0x0,  WHITE, 15},
		{0x4c, 0x40, WHITE, 12},
		
		
	 	/*		��	
		 *		�� 		�ڿڿڿ� 
		 *		��		 
		 *		�� 
		 */ 
		 {0x88, 0x88, RED, 17},
		 {0xf0, 0xf0, RED, 16},
		 
		 /*
		  *		�ڿ� 
		  *		�ڿ� 
		  */
		  {0xcc, 0x0, BLUE, 18} 
};

int current_box_numb;	//���浱ǰ������

int Curbox_x = Sys_x + Begin_boxs * BSIZE;
int Curbox_y = Sys_y; 
int flag_newbox = False;	//�Ƿ�����·���ı��
int speed = 0;	//�����ٶ�
int score = 0;	//�ܷ�
int speed_step = 30;	//ÿ�ȼ���Ҫ�ķ���
 
void interrupt (*oldtimer)(void);	/*ָ��ԭ��ʱ���жϴ��������ڵ��жϴ�����ָ��*/ 

 
void interrupt newtimer(void);	//ʵ���µ�ʱ�� 
void SetTimer(void intertupt(*IntProc)(void)); //����������ʱ�ӵĴ������ 
void KillTime(); //�ָ�ԭ�е�ʱ�Ӵ������ 
void initialize(int x, int y, int m, int n);	//��ʼ������
int DelFullRow(int y);	//ɾ������
void setFullRow(int t_boardy);	//��ѯ�Ƿ�����
int MkNextBox(int box_numb);	//�����¸���Ϸ����
void EraseBox(int x, int y, int box_numb);	//����� ��x , y��λ�ÿ�ʼ���Ϊ box_numb�ķ��� 
void show_box(int x, int y, int box_numb, int color);	//��ʾ����
int MoveAble(int x, int y, int box_numb, int direction); //�жϷ����Ƿ�����ƶ�

int main()
{
	return 0;
}
