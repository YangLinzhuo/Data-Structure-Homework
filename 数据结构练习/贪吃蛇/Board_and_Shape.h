/*
	Board and Shape
*/

struct	BOARD		/*游戏底板结构，表示每个点具有的属性*/
{
	int var;		/*当前状态只有 0 和 1 两种，1 表示该点已经被占用*/
	int color;		/*颜色，游戏底板的每个点可以拥有不同的颜色，增强美观性*/
}Table_board[Vertical_boxes][Horizontal_boxes];

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
