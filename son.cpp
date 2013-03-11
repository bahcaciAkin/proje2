//
//  main.c
//  Ders1
//
//  Created by Gurel Erceis on 2/10/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//
#include<windows.h>
#include <stdio.h>
#include <GL/gl.h> 
#include <GL/glu.h>
#include <GL/glut.h>
#include<math.h>
#define PI 3.14159265

 
static void DrawBox();
 
GLenum doubleBuffer;
 
	float angle=0;
	float angle1=0;
	float angle2=0;
	float distance =10;
	GLboolean isKeyDownZ = false;
	GLboolean isKeyDownX = false;
	GLfloat material_shininess[] = { 20 };

static void Init(){
	// Background Color
	glClearColor(0.0, 0.0, 0.0, 1.0);
 
	// Draw Lines (Wireframe)
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
 
}
 
static void Draw(void)
{
 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
 
	// Set Angle
	glColor3f(0, 1, 1);
	DrawBox(); 
 
	glutSwapBuffers();
}

static void Key( unsigned char key, int x, int y){
    switch(key){
        case 'q':
            exit(0);
            break;
        case 'z':
            isKeyDownZ = true;
            break;
        case 'x':
            isKeyDownX = true;
            break;
        case 'c':
            material_shininess[0]+=5;
            break;
        case 'v':
            material_shininess[0]-=5;
            break;
    }
}

static void KeyUp( unsigned char key, int x, int y){
    isKeyDownZ = false;
    isKeyDownX = false;
    
}
 
static void timerCallback (int value)
{
// Do timer processing
	angle+=0.5;
	angle1+=3;
	angle2+=5;

	if( isKeyDownX ){
        angle-=5;
    }
    if( isKeyDownZ)
    {
        angle+=5;
    }
    
   

	// call back again after 10ms have passed
	glutTimerFunc(20, timerCallback, value);
	// Re-draw
	glutPostRedisplay();
 
}

void setupLight(){
    glEnable(GL_LIGHTING);
    
    GLfloat light_position[] = {0.0, 0.0, -10.0, 1.0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0.1 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_emmission[] = { 1.0, 1.0, 1.0, 0.0 };
    
    
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_EMISSION, light_emmission);

    
    GLfloat global_ambient[] = { 0.2,  0.2, 0.2, 1.0 };
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat material_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    
    
    glMaterialfv(GL_FRONT,GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT,GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT,GL_SHININESS, material_shininess);
    
	glShadeModel(GL_AMBIENT);
}
 
int main (int argc, char ** argv)
{
 
	GLenum type;
	int width,height;
	double range;
	glutInit(&argc, argv);
 
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
	type |= GLUT_MULTISAMPLE;
	type |= GLUT_SINGLE;
	
	//glShadeModel (GL_SMOOTH);
	
	
	width=glutGet(GLUT_SCREEN_WIDTH);
	height=glutGet(GLUT_SCREEN_HEIGHT);
 
	glutInitWindowPosition(width*0.25,height*0.25);
	glutInitWindowSize(width*.5,height*.5);
	glutInitDisplayMode( type );
	glutCreateWindow("");
	
 
		Init();
	range=2;

	glMatrixMode(GL_PROJECTION);
	gluPerspective(90,(double)width/height,0.1,100);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);	
	setupLight();
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	glutDisplayFunc(Draw);
	timerCallback(0);

glutMainLoop();
return 0; 
}
  
static void DrawBox(){

	GLUquadric* quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);

	//gluLookAt(10,-20,0,0,0,0,0,0,1);
 
	glPushMatrix();

		glTranslatef(0,0,-10);  //GÜNEÞ
		glPushMatrix();	
		glColor3f(1,1,0);
		glRotatef(0, 0, 0, 0);		
		glutSolidSphere (1.0, 140, 140);


	glTranslatef(distance*0.5*(cos(angle*PI/180)),0.0,distance*0.5*(sin(angle*PI/180)));
	glPushMatrix();	//DÜNYA
		glColor3f(0,0,1);
		glRotatef(angle1, 0, 1, 0);
		gluSphere(quadric,1,100,100);
		

 
		glPushMatrix();//AY
			glTranslatef(-distance*0.3*(cos(angle*PI/180)),0.0,distance*0.3*(sin(angle*PI/180)));
			glColor3f(0,1,0);
			glRotatef(angle, 0, 1, 0);
			gluSphere(quadric,0.2,50,50);			
		glPopMatrix();

		glPushMatrix();//AY2
			glTranslatef(distance*0.2*(cos(angle1*PI/180)),0.0,distance*0.2*(sin(angle1*PI/180)));
			glColor3f(0,1,0);
			glRotatef(angle, 0, 1, 0);
			gluSphere(quadric,0.2,50,50);			
		glPopMatrix();


	glPopMatrix();

		glTranslatef(distance*2*(cos(angle*PI/180)),0.0,distance*2*(sin(angle*PI/180)));
	glPushMatrix();	//MARS
		glColor3f(0,0,1);
		glRotatef(angle1, 0, 1, 0);
		gluSphere(quadric,1,100,100);
		

 
		glPushMatrix();//AY
			glTranslatef(-distance*0.3*(cos(angle*PI/180)),0.0,distance*0.3*(sin(angle*PI/180)));
			glColor3f(1,1,0);
			glRotatef(angle, 0, 1, 0);
			gluSphere(quadric,0.2,50,50);			
		glPopMatrix();

		glPushMatrix();//AY2
			glTranslatef(distance*0.2*(cos(angle*PI/180)),0.0,distance*0.2*(sin(angle*PI/180)));
			glColor3f(1,0,0);
			glRotatef(angle, 0, 1, 0);
			gluSphere(quadric,0.2,50,50);			
		glPopMatrix();


	glPopMatrix();

	


glPopMatrix();//güneþ pop
 
}

