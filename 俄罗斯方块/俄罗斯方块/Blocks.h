#pragma once

#include "DrawList.h"
#include <string.h>
#include<cstring>

const GLint MAX_NUM_BLOCK = 4;
const GLint BIG_BLOCK = 1;

const GLint MOVE_TO_IN    = 1; //向 - Z 轴 方向 移动
const GLint MOVE_TO_RIGHT = 2; //向 + X 轴 方向 移动
const GLint MOVE_TO_OUT   = 3; //向 + Z 轴 方向 移动
const GLint MOVE_TO_LEFT  = 4; //向 - X 轴 方向 移动
const GLint MOVE_TO_DOWN  = 5; //向 - Y 轴 方向 移动

const GLint R_X_CLOCK    =  6; //绕 X 轴 顺 时针 方向旋转
const GLint R_X_UNCLOCK  =  7; //绕 X 轴 逆 时针 方向旋转
const GLint R_Y_CLOCK    =  8; //绕 Y 轴 顺 时针 方向旋转
const GLint R_Y_UNCLOCK  =  9; //绕 Y 轴 逆 时针 方向旋转
const GLint R_Z_CLOCK    = 10; //绕 Z 轴 顺 时针 方向旋转
const GLint R_Z_UNCLOCK  = 11; //绕 Z 轴 逆 时针 方向旋转


//我们约定 一整块 为方块
//组成一整块 的 小格子 为方格
class Blocks
{
protected:

	//好吧，这里有点麻烦，要注意！！
	
	GLint position[3];           //position是方块的中心坐标 ， 中心就是四个方格中间那一点！！
	
	GLint num_block;             //组成一整块的 方格数
	GLint dis[MAX_NUM_BLOCK][3]; //那样 dis 就记录每一个 方格 的中点 距离方块的中心的方格数

	GLfloat color[3];            //方块颜色
public:


	void operator = (Blocks &pTextBlock)
	{
		for (int i  = 0; i < 3;i++)
		{
			position[i] = pTextBlock.position[i];
		}

		num_block = pTextBlock.num_block;

		for(int i = 0; i<num_block;i++)
		{
			for(int j = 0;j < 3;j++)
			{
				dis[i][j] = pTextBlock.dis[i][j];
			}
		}

		for (int i  = 0; i < 3;i++)
		{
			color[i] = pTextBlock.color[i];
		}
	}
	
	//各种 Get 函数
	inline GLint Get_position(int n_ijk){
		return (n_ijk < 3) ? position[n_ijk] : -1;
	}

	inline GLint Get_dis(GLint n_block,GLint n_ijk){
		return (n_block < num_block && n_ijk < 3) ? dis[n_block][n_ijk] : -1;
	}

	inline GLint Get_num_block(){
		return num_block;
	}

	//各种 Set函数 ，顾名思义
	void Set_position(GLfloat x = 0,GLfloat y= 0,GLfloat z = 0);
	void Set_color(GLfloat r = 1,GLfloat g = 1,GLfloat b = 1);
	void Set_num_block(int n = 4);
	void Set_dis(GLint n_block,GLint n_ijk,GLint num);

	Blocks Move(GLint How_To_Move);
	Blocks Revolve(GLint How_To_Revolve);

	//无脑 Draw 一个方块的函数 ， 不管位置是否合法 ， 按照位置画出方块
	//在Draw 之前要做碰撞检测
	void DrawBlocks();
};