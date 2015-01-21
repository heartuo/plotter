#include <cstdio>
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#if !defined(__APPLE__)
#include <malloc.h>
#endif
#include <stdarg.h>
#include <math.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/time.h>
#include "math_lib.h"
#include "GL/freeglut.h"
// #include "GL/gl.h"
#define FPS 60

   float x;
   float y;

   exprtk::symbol_table<float> symbol_table;
   exprtk::expression<float> expr;
   exprtk::parser<float> parser;
int counter = 0;
bool test = 1;
bool dir = 1;
int i,j;
F3I demo;
CUBT edge;
F3I_PTR demo_ptr=&demo;
PT4D_PTR pt_ptr=NULL;
float ulx,llx,uly,lly,ulz,llz,stepX,stepY,currentX,currentY,zoomX,zoomY,zoomZ;
//float ALPHA = 319.5, BETA = 179.5;
float ALPHA, BETA;
bool anim = 0;
char text_buffer[100];
PT4D cam_pos(0.0f,10000.0f,0.0f,1.0f);
MAT44 mworld(1,0,0,0,
		  0,1,0,0,
		  0,0,1,0,
		  0,0,0,1);
MAT44 mmove(1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        -cam_pos.x,-cam_pos.y,-cam_pos.z,1);
	MAT44 mhome;
	MAT44 mcorrect(1,0,0,0,
				    0,0,1,0,
					0,-1,0,0,
					0,0,0,1);
	MAT44 mzoom;
		//The angle is 1.5 degree.
MAT44 mlrotation_x(1,0,0,0,
						 0,0.999657325,0.02617694831,0,
						 0,-0.02617694831,0.999657325,0,
						 0,0,0,1);
MAT44 mrrotation_x(1,0,0,0,
						 0,0.999657325,-0.02617694831,0,
						 0,0.02617694831,0.999657325,0,
						 0,0,0,1);
MAT44 mlrotation_y(0.999657325,0,-0.02617694831,0,
	    0,1,0,0,
		0.02617694831,0,0.999657325,0,
		0,0,0,1);
MAT44 mrrotation_y(0.999657325,0,0.02617694831,0,
	    0,1,0,0,
		-0.02617694831,0,0.999657325,0,
		0,0,0,1);
MAT44 mlrotation_z(0.999657325,0.02617694831,0,0,
		 -0.02617694831,0.999657325,0,0,
		 0,0,1,0,
		 0,0,0,1);
MAT44 mrrotation_z(0.999657325,-0.02617694831,0,0,
		 0.02617694831,0.999657325,0,0,
		 0,0,1,0,
		 0,0,0,1);
MAT44 mrecord(1,0,0,0,
		  0,1,0,0,
		  0,0,1,0,
		  0,0,0,1);
/*MAT44 mdisplay(ALPHA,0,0,0,
		0,-BETA,0,0,
		0,0,1,0,
		ALPHA+256,BETA,0,1);
*/

/*
	MAT44 mdisplay(0.998f,0,0,0,
					0,-0.998f,0,0,
					0,0,0,0,
					249.5f+370,250.5f+200,0,1);
*/
/*
	MAT44 mdisplay(0.998f,0,0,0,
			0,-0.998f,0,0,
			ALPHA,BETA,1,1,
			0,0,0,0);
*/
MAT44 mscreenzoom;
MAT44 mscreenmove;
/*

//zoom the image to the size of the window, which is 4/5 of the screen height
MAT44 mscreenzoom(8*BETA/5/500,0,0,0,
		0,8*BETA/5/500,0,0,
		0,0,8*BETA/5/500,0,
		0,0,0,1);

//move the image to the center of the screen
MAT44 mscreenmove(1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		ALPHA,BETA,0,1);

*/

void compile_expression(string s)
{
   symbol_table.add_variable("x", x);
   symbol_table.add_variable("y", y);
   symbol_table.add_constants();
   expr.register_symbol_table(symbol_table);
   parser.compile(s, expr);
}

void initialize()
{
	
ulx=5;
llx=-5;
uly=5;
lly=-5;

		
		for(j=0;j<35;j++)
		{
			for(i=0;i<35;i++)
			{
				pt_ptr=&(demo.pis[i][j]);
				pt_ptr->w=1;
				pt_ptr=&(demo.pid[i][j]);
				pt_ptr->w=1;
			}
		}
			edge.vlist[0].setPoint(ulx,uly,ulz,1);
			edge.vlist[1].setPoint(llx,uly,ulz,1);
			edge.vlist[2].setPoint(llx,lly,ulz,1);
			edge.vlist[3].setPoint(ulx,lly,ulz,1);
			edge.vlist[4].setPoint(ulx,uly,llz,1);
			edge.vlist[5].setPoint(llx,uly,llz,1);
			edge.vlist[6].setPoint(llx,lly,llz,1);
			edge.vlist[7].setPoint(ulx,lly,llz,1);
			
			edge.dlist[0].setPoint(ulx,uly,ulz,1);
			edge.dlist[1].setPoint(llx,uly,ulz,1);
			edge.dlist[2].setPoint(llx,lly,ulz,1);
			edge.dlist[3].setPoint(ulx,lly,ulz,1);
			edge.dlist[4].setPoint(ulx,uly,llz,1);
			edge.dlist[5].setPoint(llx,uly,llz,1);
			edge.dlist[6].setPoint(llx,lly,llz,1);
			edge.dlist[7].setPoint(ulx,lly,llz,1);
}

void reshape(int width, int height)
{
	ALPHA = 0.5f*(float)width;
	BETA = 0.5f*(float)height;
//	printf("%f\n", ALPHA);
//	printf("%f\n", BETA);
	//zoom the image to the size of the window, which is 4/5 of the screen height
	mscreenzoom.setMatrix(6*BETA/5/500,0,0,0,
		0,6*BETA/5/500,0,0,
		0,0,6*BETA/5/500,0,
		0,0,0,1);

	//move the image to the center of the screen
	mscreenmove.setMatrix(1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		ALPHA,BETA,0,1);

    glutPostRedisplay();
}

void keyControl(unsigned char key, int x, int y)
{
		
	if (key == 87 || key == 119) //'W' and 'w'
	{

		//demo.pis[i][j]=Matrix_Multiplication_14_44(pt_ptr,&mlrotation_x);
		mrecord=Matrix_Multiplication_44_44(&mrecord,&mrrotation_x);

	
		}
/*
*/
                        //glutPostRedisplay();
	if (key == 83 || key == 115) //'S' and 's'
	{

		//demo.pis[i][j]=Matrix_Multiplication_14_44(pt_ptr,&mrrotation_x);
		mrecord=Matrix_Multiplication_44_44(&mrecord,&mlrotation_x);

	
		}
/*
*/
                        //glutPostRedisplay();
	if (key == 65 || key == 97) //'A' and 'a'
	{

		//demo.pis[i][j]=Matrix_Multiplication_14_44(pt_ptr,&mlrotation_y);
		mrecord=Matrix_Multiplication_44_44(&mrecord,&mlrotation_z);


	
		}

/*
*/
                        //glutPostRedisplay();
	if (key == 68 || key == 100) //'D' and 'd'
	{

		mrecord=Matrix_Multiplication_44_44(&mrecord,&mrrotation_z);


	
		}

/*
	for(i=0;i<8;i++)
	{
		pt_ptr=&edge.vlist[i];
		//edge.vlist[i]=Matrix_Multiplication_14_44(pt_ptr,&mrrotation_y);
	}
*/
                        //glutPostRedisplay();
	if (key == 80 || key == 112)
	{
		anim = !anim;
	}
	if (key == 67 || key == 99) dir = !dir;
	if (key == 27)
	{
		glutLeaveMainLoop();
	}
}

void timer(int v) {
if (anim == 1)
{
	if (dir)
{
    ulx += 0.1f;
	llx += 0.1f;
	uly += 0.1f;
	lly += 0.1f;
}
else
{
	
    ulx -= 0.1f;
	llx -= 0.1f;
	uly -= 0.1f;
	lly -= 0.1f;
}
counter++;
if (counter > 30)
{
	counter = 0;
	printf("Width: %f\n",ALPHA*2);
	printf("X: %f\n",edge.dlist[0].x);
	printf("Y: %f\n",edge.dlist[0].y);
	printf("Z: %f\n",edge.dlist[0].z);
}
}
    glutPostRedisplay();
  glutTimerFunc(1000/FPS, timer, v);
}

void plotCube(CUBT_PTR cptr)
{
	    glBegin(GL_LINE_LOOP);
	    	glVertex2f(cptr->dlist[0].x, cptr->dlist[0].y);
	        glVertex2f(cptr->dlist[1].x, cptr->dlist[1].y);
	        glVertex2f(cptr->dlist[2].x, cptr->dlist[2].y);
	        glVertex2f(cptr->dlist[3].x, cptr->dlist[3].y);
	    glEnd();
	    glBegin(GL_LINE_LOOP);
	   	    glVertex2f(cptr->dlist[4].x, cptr->dlist[4].y);
	   	    glVertex2f(cptr->dlist[5].x, cptr->dlist[5].y);
	   	    glVertex2f(cptr->dlist[6].x, cptr->dlist[6].y);
	   	    glVertex2f(cptr->dlist[7].x, cptr->dlist[7].y);
	   	glEnd();
	    glBegin(GL_LINES);
	   	    glVertex2f(cptr->dlist[0].x, cptr->dlist[0].y);
	   	    glVertex2f(cptr->dlist[4].x, cptr->dlist[4].y);			
	   	    glVertex2f(cptr->dlist[1].x, cptr->dlist[1].y);
	   	    glVertex2f(cptr->dlist[5].x, cptr->dlist[5].y);			
	   	    glVertex2f(cptr->dlist[2].x, cptr->dlist[2].y);
	   	    glVertex2f(cptr->dlist[6].x, cptr->dlist[6].y);
	   	    glVertex2f(cptr->dlist[3].x, cptr->dlist[3].y);
	   	    glVertex2f(cptr->dlist[7].x, cptr->dlist[7].y);			
	   	glEnd();
	   	//glFlush();
}
void plot()
{
		for(i=0;i<35;i++)
		{
			glBegin(GL_LINE_STRIP);
			for(j=0;j<35;j++)
			{
				pt_ptr=&(demo.pid[i][j]);
				glVertex2f(pt_ptr->x, pt_ptr->y);
			}
			glEnd();
		}
		for(j=0;j<35;j++)
		{
			glBegin(GL_LINE_STRIP);
			for(i=0;i<35;i++)
			{
				pt_ptr=&(demo.pid[i][j]);
				glVertex2f(pt_ptr->x, pt_ptr->y);
			}
			glEnd();
		}
}
void renderFunction()
{
	
		stepX=(ulx-llx)/34;
		stepY=(uly-lly)/34;
		currentX=llx;
		currentY=lly;
		for(j=0;j<35;j++)
	{
		for(i=0;i<35;i++)
		{
			pt_ptr=&(demo.pis[i][j]);
			pt_ptr->x=currentX;
			pt_ptr->y=currentY;
			currentX+=stepX;
		}
		currentY+=stepY;
		currentX=llx;
	}
	
	
			for(i=0;i<35;i++)
		{
			for(j=0;j<35;j++)
			{
				pt_ptr=&(demo.pis[i][j]);
				//here is where the outcome of the intepreter comes in!
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				x = pt_ptr->x;
				y = pt_ptr->y;
				pt_ptr->z = expr.value();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(pt_ptr->z>ulz)

					ulz=pt_ptr->z;

				if(pt_ptr->z<llz)

					llz=pt_ptr->z;
			}
		}
//Input the values here.
		pt_ptr=&(demo.ori);
		pt_ptr->x=(ulx+llx)/2;
		pt_ptr->y=(uly+lly)/2;
		pt_ptr->z=(ulz+llz)/2;
		zoomX=500/(ulx-llx);
		zoomY=500/(uly-lly);
		zoomZ=500/(ulz-llz);
		

	mhome.setMatrix(1,0,0,0,
				 0,1,0,0,
				 0,0,1,0,
				 -demo.ori.x,-demo.ori.y,-demo.ori.z,1);

	mzoom.setMatrix(zoomX,0,0,0,
				 0,zoomY,0,0,
				 0,0,zoomZ,0,
				 0,0,0,1);


			edge.vlist[0].setPoint(ulx,uly,ulz,1);
			edge.vlist[1].setPoint(llx,uly,ulz,1);
			edge.vlist[2].setPoint(llx,lly,ulz,1);
			edge.vlist[3].setPoint(ulx,lly,ulz,1);
			edge.vlist[4].setPoint(ulx,uly,llz,1);
			edge.vlist[5].setPoint(llx,uly,llz,1);
			edge.vlist[6].setPoint(llx,lly,llz,1);
			edge.vlist[7].setPoint(ulx,lly,llz,1);

			for(i=0;i<8;i++)
			{
				pt_ptr=&(edge.vlist[i]);
				edge.vlist[i]=Matrix_Multiplication_14_44(pt_ptr,&mhome);
				edge.vlist[i]=Matrix_Multiplication_14_44(pt_ptr,&mzoom);
				edge.vlist[i]=Matrix_Multiplication_14_44(pt_ptr,&mrecord);
			}

			for(i=0;i<35;i++)
		{
			for(j=0;j<35;j++)
			{
				pt_ptr=&(demo.pis[i][j]);
				demo.pis[i][j]=Matrix_Multiplication_14_44(pt_ptr,&mhome);
				demo.pis[i][j]=Matrix_Multiplication_14_44(pt_ptr,&mzoom);
				demo.pis[i][j]=Matrix_Multiplication_14_44(pt_ptr,&mrecord);
			}
		}
for(i=0;i<35;i++)
{
	for(j=0;j<35;j++)
	{
		pt_ptr=&(demo.pis[i][j]);
		
				demo.pid[i][j]=Matrix_Multiplication_14_44(pt_ptr,&mmove);
		
		pt_ptr=&(demo.pid[i][j]);
				demo.pid[i][j]=Matrix_Multiplication_14_44(pt_ptr,&mcorrect);
		demo.pid[i][j]=Matrix_Multiplication_14_44(pt_ptr,&mscreenzoom);
		demo.pid[i][j]=Matrix_Multiplication_14_44(pt_ptr,&mscreenmove);
	}
}
		
			for(i=0;i<8;i++)
			{
				pt_ptr=&edge.vlist[i];
				edge.dlist[i]=Matrix_Multiplication_14_44(pt_ptr,&mmove);

				pt_ptr=&edge.dlist[i];
				edge.dlist[i]=Matrix_Multiplication_14_44(pt_ptr,&mcorrect);
		edge.dlist[i]=Matrix_Multiplication_14_44(pt_ptr,&mscreenzoom);
		edge.dlist[i]=Matrix_Multiplication_14_44(pt_ptr,&mscreenmove);

//	if (test)
//{
//	test = 0;
//}
			}
	
	glClearColor(0.0, 0.0, 0.0, 0.0); //set the background to black
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	//glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f, 0.0f, 1.0f);
	glOrtho(0.0f, 2*ALPHA, 2*BETA, 0.0f, 0.0f, 1.0f);
	plotCube(&edge);
	plot();
	glutSwapBuffers();
}
///////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	compile_expression(argv[1]);
	initialize();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    //glutInitWindowSize(1280,768);
    glutInitWindowSize(1280,720);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - Plotter");
    glutDisplayFunc(renderFunction);
    //glutIdleFunc(renderFunction);
    glutTimerFunc(100, timer, 0);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyControl);
    glutMainLoop();
    return 0;
}


