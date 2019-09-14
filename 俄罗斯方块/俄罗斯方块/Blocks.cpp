#include "Blocks.h"

void Blocks ::Set_position(GLfloat x ,GLfloat y ,GLfloat z )
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void Blocks ::Set_color(GLfloat r ,GLfloat g , GLfloat b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Blocks :: Set_num_block(int n)
{
	num_block = n;
}

void Blocks :: Set_dis(GLint n_block,GLint n_ijk,GLint num)
{
	if (n_block < num_block && n_ijk < 3)
	{
		dis[n_block][n_ijk] = num;
	}
}

void Blocks :: DrawBlocks()
{
	for(int i= 0;i<num_block;i++)
	{
		glPushMatrix();
			glTranslatef(position[0]+dis[i][0]*BIG_BLOCK/2 , position[1]+dis[i][1]*BIG_BLOCK/2 ,position[2]+dis[i][2]*BIG_BLOCK/2);
			glScalef(BIG_BLOCK*0.99,BIG_BLOCK*0.99,BIG_BLOCK*0.99);
			DrawOneBlock(DrawList_1);
		glPopMatrix();
	}
}

Blocks Blocks ::Move(GLint How_To_Move)
{
	Blocks pTempBlocks;
	GLint Move_dis[6][3] = { {0,0,0} ,{0,0,-1} , {1,0,0}, /*分别是 无 ， IN ， 右*/
							 {0,0,1} ,{-1,0,0} ,{0,-1,0} };//分别是 OUT ， 左 ， 下
	pTempBlocks = *this;
	pTempBlocks.Set_position(this->Get_position(0)+Move_dis[How_To_Move][0]*BIG_BLOCK,
		this->Get_position(1)+Move_dis[How_To_Move][1]*BIG_BLOCK,
		this->Get_position(2)+Move_dis[How_To_Move][2]*BIG_BLOCK);
	return pTempBlocks;
}

Blocks Blocks::Revolve(GLint How_To_Revolve)
{
	Blocks pTempBlocks;
	GLint Revolve_dis1[7][3] = { {0,0,0} ,{0,2,1} , {0,2,1}, /*分别是  无， X顺 ， X逆*/
								 {2,1,0} ,{2,1,0} , {1,0,2},{1,0,2} };//分别是 Y顺 ， Y逆 ， Z顺，Z逆

	GLint Revolve_dis2[7][3] = { {0,0,0} ,{1,-1,1} , {1,1,-1}, /*分别是  无， X顺 ， X逆*/
								 {-1,1,1} ,{1,1,-1} , {-1,1,1},{1,-1,1} };//分别是 Y顺 ， Y逆 ， Z顺，Z逆

	pTempBlocks = *this;
	for(int i = 0;i<num_block;i++)
	{
		pTempBlocks.Set_dis(i,0,this->Get_dis(i,Revolve_dis1[i][0])*Revolve_dis2[i][0]);
		pTempBlocks.Set_dis(i,1,this->Get_dis(i,Revolve_dis1[i][1])*Revolve_dis2[i][1]);
		pTempBlocks.Set_dis(i,2,this->Get_dis(i,Revolve_dis1[i][2])*Revolve_dis2[i][2]);
	}
	return pTempBlocks;
}
