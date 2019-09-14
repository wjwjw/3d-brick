#include "DrawList.h"

//显示列表放在这里，其他下面直接调用Draw函数就可以了

GLfloat vertices_1[] = {-1.0 , -1.0 ,  1.0,
						-1.0 ,  1.0 ,  1.0,
						 1.0 ,  1.0 ,  1.0,
						 1.0 , -1.0 ,  1.0,
						-1.0 , -1.0 , -1.0,
						-1.0 ,  1.0 , -1.0,
						 1.0 ,  1.0 , -1.0,
						 1.0 , -1.0 , -1.0  };

GLubyte cubeIndices_1[] = {0,3,2,1 , 3,7,6,2 , 7,4,5,6 , 4,0,1,5 , 5,1,2,6 , 4,7,3,0};


void PutList()
{
	//显示列表1
	//画一个方块的显示列表
	glNewList(DrawList_1,GL_COMPILE);
	glDrawElements(GL_QUADS , 24 , GL_UNSIGNED_BYTE , cubeIndices_1);
	glEndList();
}


//画一个方格的函数
void DrawOneBlock(GLint List_to_Draw)
{
	glCallList(List_to_Draw);
}