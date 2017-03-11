/*
	function
*/
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <graphics.h> 
/*定义按键码*/
#define VK_LEFT		0x4b00
#define VK_RIGHT	0x4d00
#define VK_DOWN		0x5000
#define VK_UP 		0x4800
#define VK_ESC		0x011b

/*定义常量*/
#define MAX_BOX		19		/*总共 19 种形态的方块*/
#define BSIZE		20		/*方块边长是 20 个像素*/
#define Sys_x		160 	/*显示方块界面的左上角 x 坐标*/
#define Sys_y		25		/*显示方块界面的左上角 y 坐标*/
#define Horizontal_boxs	10	/*水平方向以方块为单位的长度*/
#define Vertical_boxs		15	/*垂直方向以方块为单位的长度*/
#define Begin_boxs_x	Horizontal_boxes 2/*产生第一个方块出现的起始位置*/

#define FgColor	3	/*前景颜色*/
#define BgColor	0	/*背景颜色*/

#define LeftWin_x	Sys_x+Horizontal_boxs*BSIZE+46	/*右边状态栏的 x 坐标*/

#define false 0
#define true 1

/*移动方向*/
#define MoveLeft	1
#define MoveRight	2
#define MoveDown	3
#define MoveRoll	4


int S
 
void interrupt newtimer(void);	//实现新的时钟 
void SetTimer(void intertupt(*IntProc)(void)); //用于设置新时钟的处理过程 
void KillTime(); //恢复原有的时钟处理过程 
void initialize(int x, int y, int m, int n);	//初始化界面
int DelFullRow(int y);	//删除整行
void setFullRow(int t_boardy);	//查询是否满行
int MkNextBox(int box_numb);	//生成下个游戏方块
void EraseBox(int x, int y, int box_numb);	//清除以 （x , y）位置开始编号为 box_numb的方块 
void show_box(int x, int y, int box_numb, int color);	//显示方块
int MoveAble(int x, int y, int box_numb, int direction); //判断方块是否可以移动
 
