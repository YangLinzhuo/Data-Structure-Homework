/*
	function
*/
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <graphics.h> 
/*���尴����*/
#define VK_LEFT		0x4b00
#define VK_RIGHT	0x4d00
#define VK_DOWN		0x5000
#define VK_UP 		0x4800
#define VK_ESC		0x011b

/*���峣��*/
#define MAX_BOX		19		/*�ܹ� 19 ����̬�ķ���*/
#define BSIZE		20		/*����߳��� 20 ������*/
#define Sys_x		160 	/*��ʾ�����������Ͻ� x ����*/
#define Sys_y		25		/*��ʾ�����������Ͻ� y ����*/
#define Horizontal_boxs	10	/*ˮƽ�����Է���Ϊ��λ�ĳ���*/
#define Vertical_boxs		15	/*��ֱ�����Է���Ϊ��λ�ĳ���*/
#define Begin_boxs_x	Horizontal_boxes 2/*������һ��������ֵ���ʼλ��*/

#define FgColor	3	/*ǰ����ɫ*/
#define BgColor	0	/*������ɫ*/

#define LeftWin_x	Sys_x+Horizontal_boxs*BSIZE+46	/*�ұ�״̬���� x ����*/

#define false 0
#define true 1

/*�ƶ�����*/
#define MoveLeft	1
#define MoveRight	2
#define MoveDown	3
#define MoveRoll	4


int S
 
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
 
