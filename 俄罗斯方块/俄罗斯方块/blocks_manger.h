#include "Blocks.h"

const int MAX_MAP_width = 8;
const int MAX_MAP_hight = 12;

int CheckCollision(Blocks* pTextBlock);

void InitMap();

void DeleteBlocks(int row[],int n); //�뱣֤���ݽ����������Ǵ�С���������

void DrawAllBlocks();