#pragma once

#include "DrawList.h"
#include <string.h>
#include<cstring>

const GLint MAX_NUM_BLOCK = 4;
const GLint BIG_BLOCK = 1;

const GLint MOVE_TO_IN    = 1; //�� - Z �� ���� �ƶ�
const GLint MOVE_TO_RIGHT = 2; //�� + X �� ���� �ƶ�
const GLint MOVE_TO_OUT   = 3; //�� + Z �� ���� �ƶ�
const GLint MOVE_TO_LEFT  = 4; //�� - X �� ���� �ƶ�
const GLint MOVE_TO_DOWN  = 5; //�� - Y �� ���� �ƶ�

const GLint R_X_CLOCK    =  6; //�� X �� ˳ ʱ�� ������ת
const GLint R_X_UNCLOCK  =  7; //�� X �� �� ʱ�� ������ת
const GLint R_Y_CLOCK    =  8; //�� Y �� ˳ ʱ�� ������ת
const GLint R_Y_UNCLOCK  =  9; //�� Y �� �� ʱ�� ������ת
const GLint R_Z_CLOCK    = 10; //�� Z �� ˳ ʱ�� ������ת
const GLint R_Z_UNCLOCK  = 11; //�� Z �� �� ʱ�� ������ת


//����Լ�� һ���� Ϊ����
//���һ���� �� С���� Ϊ����
class Blocks
{
protected:

	//�ðɣ������е��鷳��Ҫע�⣡��
	
	GLint position[3];           //position�Ƿ������������ �� ���ľ����ĸ������м���һ�㣡��
	
	GLint num_block;             //���һ����� ������
	GLint dis[MAX_NUM_BLOCK][3]; //���� dis �ͼ�¼ÿһ�� ���� ���е� ���뷽������ĵķ�����

	GLfloat color[3];            //������ɫ
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
	
	//���� Get ����
	inline GLint Get_position(int n_ijk){
		return (n_ijk < 3) ? position[n_ijk] : -1;
	}

	inline GLint Get_dis(GLint n_block,GLint n_ijk){
		return (n_block < num_block && n_ijk < 3) ? dis[n_block][n_ijk] : -1;
	}

	inline GLint Get_num_block(){
		return num_block;
	}

	//���� Set���� ������˼��
	void Set_position(GLfloat x = 0,GLfloat y= 0,GLfloat z = 0);
	void Set_color(GLfloat r = 1,GLfloat g = 1,GLfloat b = 1);
	void Set_num_block(int n = 4);
	void Set_dis(GLint n_block,GLint n_ijk,GLint num);

	Blocks Move(GLint How_To_Move);
	Blocks Revolve(GLint How_To_Revolve);

	//���� Draw һ������ĺ��� �� ����λ���Ƿ�Ϸ� �� ����λ�û�������
	//��Draw ֮ǰҪ����ײ���
	void DrawBlocks();
};