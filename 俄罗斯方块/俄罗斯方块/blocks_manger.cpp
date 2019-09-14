#include "blocks_manger.h"

int Map[MAX_MAP_width + 3][MAX_MAP_hight + 3][MAX_MAP_width + 3];

Blocks now_block;
Blocks next_block;

int CheckCollision(Blocks* pTextBlock)
{
	GLint ti = pTextBlock->Get_position(0)/BIG_BLOCK;
	GLint tj = pTextBlock->Get_position(1)/BIG_BLOCK;
	GLint tk = pTextBlock->Get_position(2)/BIG_BLOCK;
	//这样得出距离中心位置为(1,1,1)的方格，在地图Map的位置

	GLint tti,ttj,ttk;
	for(int i = 0;i<pTextBlock->Get_num_block();i++)
	{
		tti = ti + (pTextBlock->Get_dis(i,0) - 1);
		ttj = tj + (pTextBlock->Get_dis(i,1) - 1);
		ttk = tk + (pTextBlock->Get_dis(i,2) - 1);
		if(ttk >MAX_MAP_width)
		{
			return 1;//超过了前面;
		}
		else if(tti <= 0)
		{
			return 2;//超过了左面
		}
		else if(ttk <= 0)
		{
			return 3;//超过了后面
		}
		else if(tti > MAX_MAP_width)
		{
			return 4;//超过了右面
		}
		else if (Map[tti][ttj][ttk] != 0)
		{
			return -1;//那个格子有东西了;
		}
	}
	return 0; //检查安全，该格子没有障碍
}

void InitMap()
{
	for (int i=0;i<=MAX_MAP_hight;i++)
	{
		for (int j=0;j<=MAX_MAP_width;i++)
		{
			for (int k=0;k<=MAX_MAP_width;k++)
			{
				Map[i][j][k] = -1;
			}
		}
	}
}

//请保证传递进来的数组是从小到大有序的
void DeleteBlocks(int row[],int n)
{
	int sum = 0;
	for (int j = 0;j<=MAX_MAP_hight;j++)
	{
		if(j == row[sum])
		{
			sum++;
		}
		for (int i = 0;i<=MAX_MAP_width;i++)
		{
			for (int k = 0;k<=MAX_MAP_width;k++)
			{
				if(j+sum <= MAX_MAP_hight)
				{
					Map[i][j][k] = Map[i][j+sum][k];
				}
				else
				{
					Map[i][j][k] = -1;
				}
			}
		}
	}
}

//画地图 和 现在在移动的 方块
void DrawAllBlocks()
{
	now_block.DrawBlocks();

	for (int i=0;i<=MAX_MAP_hight;i++)
	{
		for (int j=0;j<=MAX_MAP_width;i++)
		{
			for (int k=0;k<=MAX_MAP_width;k++)
			{
				if (Map[i][j][k] == 0)
				{
					glPushMatrix();
						glTranslatef((i+0.5)*BIG_BLOCK,(j+0.5)*BIG_BLOCK,(k+0.5)*BIG_BLOCK);
						glScalef(BIG_BLOCK*0.99,BIG_BLOCK*0.99,BIG_BLOCK*0.99);
						DrawOneBlock(DrawList_1);
					glPopMatrix();
				}
			}
		}
	}
}