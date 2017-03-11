
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <graphics.h> 
/*定义按键码*/
#define LEFT		0x4b00
#define RIGHT	0x4d00
#define DOWN		0x5000
#define UP 		0x4800
#define ESC		0x011b

/*定义常量*/
#define MAX_BOX		19		/*总共 19 种形态的方块*/
#define BSIZE		20		/*方块边长是 20 个像素*/
#define Sys_x		160 	/*显示方块界面的左上角 x 坐标*/
#define Sys_y		25		/*显示方块界面的左上角 y 坐标*/
#define Horizontal_boxs	10	/*水平方向以方块为单位的长度*/
#define Vertical_boxs		15	/*垂直方向以方块为单位的长度*/
#define Begin_boxs_x	Horizontal_boxs/2/*产生第一个方块出现的起始位置*/

#define FgColor	3	/*前景颜色*/
#define BgColor	0	/*背景颜色*/

#define LeftWin_x	Sys_x+Horizontal_boxs*BSIZE+46	/*右边状态栏的 x 坐标*/

#define False 0
#define True 1

/*移动方向*/
#define MoveLeft	1
#define MoveRight	2
#define MoveDown	3
#define MoveRoll	4

/*
	Board and Shape
*/

struct	BOARD		/*游戏底板结构，表示每个点具有的属性*/
{
	int var;		/*当前状态只有 0 和 1 两种，1 表示该点已经被占用*/
	int color;		/*颜色，游戏底板的每个点可以拥有不同的颜色，增强美观性*/
}Table_board[Vertical_boxs][Horizontal_boxs];

struct SHAPE
{
	/*一个字节是 8 位，用 4 位表示游戏方块中的一行*/
	char box[2];
	int color;		/*每个方块的颜色*/
	int next;		/*下个方块的编号*/
};


struct SHAPE shapes[MAX_BOX] = 
{
	/*  口 		口口口 		口口 			口 
	 *  口      口 			  口 		口口口 
	 *  口口				  口 
	 */
	 {0x88,	0xC0, CYAN, 1},
	 {0xe8, 0x0,  CYAN, 2},
	 {0xc4, 0x40, CYAN, 3},
	 {0x2e, 0x0,  CYAN, 0},
	 
	/*    口 				口口		口口口 
	 *	  口 	口 			口 				口 
	 *  口口    口口口 		口 
	 */
	 {0x44, 0xc0, MAGENTA, 5}, 
	 {0x8e,	0x0,  MAGENTA, 6},
	 {0xc8, 0x80, MAGENTA, 7},
	 {0xe2, 0x0,  MAGENTA, 4}, 
	 
	 /*		口 
	  *		口口		口口 
	  *		  口 	  口口 
	  */
	  {0x8c, 0x40, YELLOW, 9},
	  {0x6c, 0x0,  YELLOW, 8},
	  
	  /*	口		口口 
	   *  口口 		  口口 
	   *  口 
	   */ 
	   {0x4c, 0x80, BROWN, 11},
	   {0xc6, 0x0,  BROWN, 10},
	   
	   /*		口 			口 					  口 
	    *	  口口口 		口口	口口口 		口口 
		*					口 		  口 		  口 
		*/ 
		{0x4e, 0x0,  WHITE, 13},
		{0x8c, 0x80, WHITE, 14},
		{0xe4, 0x0,  WHITE, 15},
		{0x4c, 0x40, WHITE, 12},
		
		
	 	/*		口	
		 *		口 		口口口口 
		 *		口		 
		 *		口 
		 */ 
		 {0x88, 0x88, RED, 17},
		 {0xf0, 0xf0, RED, 16},
		 
		 /*
		  *		口口 
		  *		口口 
		  */
		  {0xcc, 0x0, BLUE, 18} 
};

int current_box_numb;	//保存当前方块编号

int Curbox_x = Sys_x + Begin_boxs * BSIZE;
int Curbox_y = Sys_y; 
int flag_newbox = False;	//是否产生新方块的标记
int speed = 0;	//下落速度
int score = 0;	//总分
int speed_step = 30;	//每等级需要的分数
 
void interrupt (*oldtimer)(void);	/*指向原来时钟中断处理过程入口的中断处理函数指针*/ 

 
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

int main()
{
	return 0;
}
