#include "Blocks.h"

const int MAX_MAP_width = 8;
const int MAX_MAP_hight = 12;

int CheckCollision(Blocks* pTextBlock);

void InitMap();

void DeleteBlocks(int row[],int n); //请保证传递近来的数组是从小到大有序的

void DrawAllBlocks();