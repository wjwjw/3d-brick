#include <windows.h>
#include <iostream>
#include <math.h>
#include <gl/glut.h>
#include "blocks_manger.h"
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#define NUM_SPHERES 500 //球的数量



//一个正方体的坐标
extern GLfloat vertices_1[];

extern int Map[MAX_MAP_width + 3][MAX_MAP_hight + 3][MAX_MAP_width + 3];

extern Blocks now_block;
extern Blocks next_block;

extern float Ayimuth = 0.00;			// 绕y轴旋转的角度
extern float Aximuth = 30.00;			// 绕x轴旋转的角度


struct POS{
	float x,y,z;
}spheres[NUM_SPHERES];				// 球数组

GLint pos_x=-100000,pos_y=-100000;	//记录上一次鼠标的坐标
GLint wight,hight;					//窗口的宽高




//随机生成一个新的方块
Blocks Creat_A_NewBlock()
{
	Blocks pTempBlock;
	return pTempBlock;
}
//初始化函数
void SetupRC()
{	
	// 以线框模式绘制
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	for(int iSphere = 0;iSphere<NUM_SPHERES;iSphere++)
	{
		float x = ((float)((rand()%400)-200)*0.1f);
		float y = ((float)((rand()%400)-200)*0.1f);
		float z = ((float)((rand()%400)-200)*0.1f);

		spheres[iSphere].x=x;
		spheres[iSphere].y=y;
		spheres[iSphere].z=z;
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,vertices_1);
	//glEnableClientState(GL_COLOR_ARRAY); //暂时没有颜色数组
	//glColorPointer(3,GL_FLOAT,0,colors); 

	PutList();  //设置显示列表

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

}
void DrawGround(GLfloat fExtent, GLfloat fStep)//那么这个画地板的有什么用？//可以看出边界，如果最后不用可以去掉
{
	glBegin(GL_LINES);
	for(GLint iLine = -fExtent;iLine <= fExtent ;iLine += fStep)
	{
		glVertex3f(iLine,0,fExtent);
		glVertex3f(iLine,0,-fExtent);
		glVertex3f(fExtent,0,iLine);
		glVertex3f(-fExtent,0,iLine);
	}
	glEnd();
}

void DrawWave(GLfloat x,GLfloat y,GLfloat z,int colour)	//传入一个坐标和颜色度深度，画两个圆做波浪
{
	glColor3f(colour,colour,colour);//颜色的深度
	int i;
	if(fabs(z)<0.001)
	{	
		glBegin(GL_LINE_LOOP); //绘制内圆形
			for(i=0; i<60; ++i)
				glVertex3f(BIG_BLOCK*cos( (2*3.14159/60) * i )+x, BIG_BLOCK*sin( (2*3.14159/60) *i)+y,0.0f);
		glEnd(); 
		glBegin(GL_LINE_LOOP); //绘制外圆形
			for(i=0; i<60; ++i)
				glVertex3f(1.5*BIG_BLOCK*cos( (2*3.14159/60) * i )+x,1.5* BIG_BLOCK*sin( (2*3.14159/60) *i)+y,0.0f);
		glEnd(); 
	}
	if(fabs(y)<0.001)
	{
		glBegin(GL_LINE_LOOP); //绘制内圆形
			for(i=0; i<60; ++i)
				glVertex3f(BIG_BLOCK*cos( (2*3.14159/60) * i )+x,0.0f, BIG_BLOCK*sin( (2*3.14159/60) *i)+z);
		glEnd(); 
		glBegin(GL_LINE_LOOP); //绘制外圆形
			for(i=0; i<60; ++i)
				glVertex3f(1.5*BIG_BLOCK*cos( (2*3.14159/60) * i )+x,0.0f,1.5* BIG_BLOCK*sin( (2*3.14159/60) *i)+z);
		glEnd(); 
	}
}

// 显示回调函数
void RenderScene(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 不用设当前矩阵了，直接LoadIdentity，
	// 因为在ChangeSize最后已经设当前矩阵为模-视矩阵了
	glLoadIdentity();	

	//照相机
	//	glMultMatrixf(matrixCamera);

	
	glTranslatef(0.0,-5.0,-30.0); //这里要问一下键尉，要不要push矩阵，以防影响下面//这里是实现鼠标拖动，画场景之外的东西可以在前面
	glRotatef(Aximuth,1.0,0.0,0.0);
	glRotatef(Ayimuth,0.0,1.0,0.0);


	if(Ayimuth>0.0)
		Ayimuth-=0.3;
	if(Ayimuth<0.0)
		Ayimuth+=0.3;

	if(Aximuth>30.0&&fabs(Ayimuth)<0.3)
		Aximuth-=0.3;
	if(Aximuth<30.0&&fabs(Ayimuth)<0.3)
		Aximuth+=0.3;

	/*1*/glPushMatrix();


	//画地板
	/*2*/glPushMatrix();
	// 	glTranslatef(0.0,-0.4,0.0);
		DrawGround((MAX_MAP_width/2)*BIG_BLOCK,BIG_BLOCK);
		
		glTranslatef(0.0,(MAX_MAP_hight/2)*BIG_BLOCK,-(MAX_MAP_hight/2-2)*BIG_BLOCK);
		glBegin(GL_LINES);
		for(GLint iLine = -(MAX_MAP_width/2)*BIG_BLOCK;iLine <= (MAX_MAP_width/2)*BIG_BLOCK ;iLine += BIG_BLOCK)
		{
			glVertex3f(iLine,(MAX_MAP_hight/2)*BIG_BLOCK,0);
			glVertex3f(iLine,-(MAX_MAP_hight/2)*BIG_BLOCK,0);
		}
		glEnd();
		glBegin(GL_LINES);
		for(GLint iLine = -(MAX_MAP_hight/2)*BIG_BLOCK;iLine <= (MAX_MAP_hight/2)*BIG_BLOCK ;iLine += BIG_BLOCK)
		{
			glVertex3f((MAX_MAP_width/2)*BIG_BLOCK,iLine,0);
			glVertex3f(-(MAX_MAP_width/2)*BIG_BLOCK,iLine,0);
		}
		glEnd();

	/*2*/glPopMatrix();

	for(int i=0;i<NUM_SPHERES;i++)
	{
		/*3*/glPushMatrix();
			glTranslatef(spheres[i].x,spheres[i].y,spheres[i].z);
			glRotatef(90,1,0,0);
			glutSolidSphere(0.2f,15,15);
		/*3*/glPopMatrix();
	}

	/*1*/glPopMatrix();

	// 交换缓存
	glutSwapBuffers();
}

void SpecialKeys(int key ,int x,int y)
{

	if(key == GLUT_KEY_UP ){

	}
	if(key == GLUT_KEY_DOWN ){

	}
	if(key == GLUT_KEY_LEFT ){

	}
	if(key == GLUT_KEY_RIGHT){

	}

	glutPostRedisplay();
}

void mouse(int x,int y)
{
	if(pos_x<x)
	{
		Ayimuth += 1.5;
		if ( Ayimuth > 45.0f ) {
			Ayimuth = 45.0f;
		}
	}
	if(pos_x>x)
	{
		Ayimuth -= 1.5;
		if ( Ayimuth < -45.0f ) {
			Ayimuth = -45.0f;
		}
	}
	if(pos_y<y)
	{
		Aximuth += 1.5;
		if ( Aximuth > 90.0f ) {
			Aximuth = 90.0f;
		}
	}
	if(pos_y>y)
	{
		Aximuth -= 1.5;
		if ( Aximuth < -0.0f ) {
			Aximuth = -0.0f;
		}
	}

	pos_x=x;
	pos_y=y;
	if(pos_x<100)pos_x+=200;
	if(pos_y<100)pos_y+=200;
	if(pos_x>wight-50) pos_x-=200;
	if(pos_y>hight-50) pos_y-=200;

}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000/60,TimerFunction,value);
}

// 窗口调整回调函数
void ChangeSize(int w, int h)
{	
	wight=w;
	hight=h;
	// 防止除0
	if(h == 0)
		h = 1;

	glViewport(0, 0, w, h);		// 视口占满整个窗口

	GLfloat fAspect = (GLfloat)w / (GLfloat)h;	// 计算窗口宽高比

	// 设置投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 设置透视投影视域体
	gluPerspective(35.0f, fAspect, 1.0f, 50.0f);

	// 将当前矩阵切换为模-视矩阵
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(
		GetSystemMetrics( SM_CXSCREEN ), //此函数返回屏幕宽度 
		GetSystemMetrics( SM_CYSCREEN )//此函数返回屏幕高度 
		);
	//	ShowCursor(FALSE);
	glutCreateWindow("3D 俄罗斯方块");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys);
	// 	glutMouseFunc(mouse);
	glutMotionFunc(mouse);
	//	glutPassiveMotionFunc(mouse);//捕捉鼠标移动
	glutTimerFunc(100,TimerFunction,0);
	SetupRC();
	glutMainLoop();

	return 0;
}
