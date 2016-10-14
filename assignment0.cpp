// CS 465
// Assignment 0
// Author:


#include "../shared/gltools.h"	// OpenGL toolkit


///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	
	glPointSize(10.0);


	
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex2i(700, 700);
	glColor3f(0, 1, 0);
	glVertex2i(720, 720);
	glColor3f(0, 0, 1);
	glVertex2i(740, 740);
	glColor3f(0, 0, 0);
	glVertex2i(760, 760);
	glEnd();


	glColor3f(0, 0, 1);
	glBegin(GL_TRIANGLES);		
		glVertex2i(0,0);
		glVertex2i(640,0);
		glVertex2i(320,480);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
		glVertex2i(800, 800);
		glVertex2i(900, 800);
		glVertex2i(900, 900);
		glVertex2i(800, 900);
		
	glEnd();

	

	// Flush drawing commands and swap the buffer
	glutSwapBuffers();
}

void TimerFunction(int value)
{
    // Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(16,TimerFunction, 1);
}

///////////////////////////////////////////////////////////
// Setup the rendering context
void SetupRC(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1000.0, 0, 1000.0);
}

///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800,800); 
 	glutCreateWindow("Assignment 0");
	glutDisplayFunc(RenderScene);
	glutTimerFunc(16, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
    return 0;
}

