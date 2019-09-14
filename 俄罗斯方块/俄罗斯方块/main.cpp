#include <windows.h>
#include <iostream>
#include <math.h>
#include <gl/glut.h>
#include "blocks_manger.h"
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#define NUM_SPHERES 500 //�������



//һ�������������
extern GLfloat vertices_1[];

extern int Map[MAX_MAP_width + 3][MAX_MAP_hight + 3][MAX_MAP_width + 3];

extern Blocks now_block;
extern Blocks next_block;

extern float Ayimuth = 0.00;			// ��y����ת�ĽǶ�
extern float Aximuth = 30.00;			// ��x����ת�ĽǶ�


struct POS{
	float x,y,z;
}spheres[NUM_SPHERES];				// ������

GLint pos_x=-100000,pos_y=-100000;	//��¼��һ����������
GLint wight,hight;					//���ڵĿ��




//�������һ���µķ���
Blocks Creat_A_NewBlock()
{
	Blocks pTempBlock;
	return pTempBlock;
}
//��ʼ������
void SetupRC()
{	
	// ���߿�ģʽ����
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
	//glEnableClientState(GL_COLOR_ARRAY); //��ʱû����ɫ����
	//glColorPointer(3,GL_FLOAT,0,colors); 

	PutList();  //������ʾ�б�

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

}
void DrawGround(GLfloat fExtent, GLfloat fStep)//��ô������ذ����ʲô�ã�//���Կ����߽磬�������ÿ���ȥ��
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

void DrawWave(GLfloat x,GLfloat y,GLfloat z,int colour)	//����һ���������ɫ����ȣ�������Բ������
{
	glColor3f(colour,colour,colour);//��ɫ�����
	int i;
	if(fabs(z)<0.001)
	{	
		glBegin(GL_LINE_LOOP); //������Բ��
			for(i=0; i<60; ++i)
				glVertex3f(BIG_BLOCK*cos( (2*3.14159/60) * i )+x, BIG_BLOCK*sin( (2*3.14159/60) *i)+y,0.0f);
		glEnd(); 
		glBegin(GL_LINE_LOOP); //������Բ��
			for(i=0; i<60; ++i)
				glVertex3f(1.5*BIG_BLOCK*cos( (2*3.14159/60) * i )+x,1.5* BIG_BLOCK*sin( (2*3.14159/60) *i)+y,0.0f);
		glEnd(); 
	}
	if(fabs(y)<0.001)
	{
		glBegin(GL_LINE_LOOP); //������Բ��
			for(i=0; i<60; ++i)
				glVertex3f(BIG_BLOCK*cos( (2*3.14159/60) * i )+x,0.0f, BIG_BLOCK*sin( (2*3.14159/60) *i)+z);
		glEnd(); 
		glBegin(GL_LINE_LOOP); //������Բ��
			for(i=0; i<60; ++i)
				glVertex3f(1.5*BIG_BLOCK*cos( (2*3.14159/60) * i )+x,0.0f,1.5* BIG_BLOCK*sin( (2*3.14159/60) *i)+z);
		glEnd(); 
	}
}

// ��ʾ�ص�����
void RenderScene(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �����赱ǰ�����ˣ�ֱ��LoadIdentity��
	// ��Ϊ��ChangeSize����Ѿ��赱ǰ����Ϊģ-�Ӿ�����
	glLoadIdentity();	

	//�����
	//	glMultMatrixf(matrixCamera);

	
	glTranslatef(0.0,-5.0,-30.0); //����Ҫ��һ�¼�ξ��Ҫ��Ҫpush�����Է�Ӱ������//������ʵ������϶���������֮��Ķ���������ǰ��
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


	//���ذ�
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

	// ��������
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

// ���ڵ����ص�����
void ChangeSize(int w, int h)
{	
	wight=w;
	hight=h;
	// ��ֹ��0
	if(h == 0)
		h = 1;

	glViewport(0, 0, w, h);		// �ӿ�ռ����������

	GLfloat fAspect = (GLfloat)w / (GLfloat)h;	// ���㴰�ڿ�߱�

	// ����ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// ����͸��ͶӰ������
	gluPerspective(35.0f, fAspect, 1.0f, 50.0f);

	// ����ǰ�����л�Ϊģ-�Ӿ���
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(
		GetSystemMetrics( SM_CXSCREEN ), //�˺���������Ļ��� 
		GetSystemMetrics( SM_CYSCREEN )//�˺���������Ļ�߶� 
		);
	//	ShowCursor(FALSE);
	glutCreateWindow("3D ����˹����");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys);
	// 	glutMouseFunc(mouse);
	glutMotionFunc(mouse);
	//	glutPassiveMotionFunc(mouse);//��׽����ƶ�
	glutTimerFunc(100,TimerFunction,0);
	SetupRC();
	glutMainLoop();

	return 0;
}
