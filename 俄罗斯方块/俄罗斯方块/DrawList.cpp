#include "DrawList.h"

//��ʾ�б���������������ֱ�ӵ���Draw�����Ϳ�����

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
	//��ʾ�б�1
	//��һ���������ʾ�б�
	glNewList(DrawList_1,GL_COMPILE);
	glDrawElements(GL_QUADS , 24 , GL_UNSIGNED_BYTE , cubeIndices_1);
	glEndList();
}


//��һ������ĺ���
void DrawOneBlock(GLint List_to_Draw)
{
	glCallList(List_to_Draw);
}