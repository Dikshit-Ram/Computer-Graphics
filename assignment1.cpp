// CS 465
// Author:


#include "../shared/gltools.h"	// OpenGL toolkit
#define PI 3.14159265
#define MOVEDELTA 0.5f
#define ANGLEDELTA 2.0f
GLfloat rot;

bool lookUp;
bool lookDown;
bool lookLeft;
bool lookRight;
bool walkForward;
bool walkBackward;
bool strafeLeft;
bool strafeRight;
float xCameraLocation;
float yCameraLocation;
float zCameraLocation;
float yRotationAngle;
float zRotationAngle;
float xRotationAngle;
int mouseLastx;
int mouseLasty;
float sunRotationAngle = 0;
float sunRadius = 150.0;
float day = 0;
float dusk = 1;
// Light values and coordinates
GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat	 lightPos2[] = { 0.0f, 0.0f, 50.0f, 1.0f };
GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat  specular2[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat  diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat  diffuse2[] = { 0.0f, 0.3f, 0.0f, 1.0f };
GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat  ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat  spotDir[] = { 0.0f, 0.0f, -1.0f };

void mouseMovement(int x, int y)
{
	int mouseDiffx = x - mouseLastx;
	int mouseDiffy = y - mouseLasty;
	mouseLastx = x;
	mouseLasty = y; //set lasty to the current y position
	xRotationAngle -= ((GLfloat)mouseDiffy)*0.1;
	yRotationAngle += ((GLfloat)mouseDiffx)*0.1;
	if (xRotationAngle >= 90)
		xRotationAngle = 90;
	if (xRotationAngle <= -90)
		xRotationAngle = -90;

	//cout << "x:" << x << "y:" << y << endl;
}

void drawRiver()
{
	glColor3ub(14, 68, 123);
	glBegin(GL_QUADS);
	glVertex3f(-10, 0.01, 100);
	glVertex3f(10, 0.01, 100);
	glColor3ub(34, 48, 62);
	glVertex3f(10, 0.01, -100);
	glColor3ub(34, 48, 62);
	glVertex3f(-10, 0.01, -100);
	glEnd();
}

void drawPyramid()
{
	glColor3ub(210, 180, 140);
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0.7, -0.7);
	glVertex3f(0, 10, 0);
	glVertex3f(5, 0, -5);
	glVertex3f(-5, 0, -5);
	glNormal3f(-0.7, 0.7, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(-5, 0, -5);
	glVertex3f(-5, 0, 5);
	glNormal3f(0, 0.7, 0.7);
	glVertex3f(0, 10, 0);
	glVertex3f(-5, 0, 5);
	glVertex3f(5, 0, 5);
	glNormal3f(0.7, 0.7, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(5, 0, 5);
	glVertex3f(5, 0, -5);
	glEnd();
}
void drawGrass()
{
	glColor3ub(58, 175, 58);
	glBegin(GL_QUADS);
	glVertex3f(-100, 0, 100);
	glVertex3f(100, 0, 100);
	glColor3f(0, 0, 0);
	glVertex3f(100, 0, -100);
	glColor3f(0, 0, 0);
	glVertex3f(-100, 0, -100);
	glEnd();
}
void drawBoat()
{
	glColor3ub(196, 140, 84);
	glBegin(GL_QUADS);
	//front face
	glVertex3f(-5, 3, 2);
	glVertex3f(-5, 0.02, 2);
	glVertex3f(5, 0.02, 2);
	glVertex3f(5, 3, 2);
	//back face
	glVertex3f(-5, 3, -2);
	glVertex3f(5, 3, -2);
	glVertex3f(5, 0.02, -2);
	glVertex3f(-5, 0.02, -2);
	//left face
	glVertex3f(-5, 3, 2);
	glVertex3f(-5, 3, -2);
	glVertex3f(-5, 0.02, -2);
	glVertex3f(-5, 0.02, 2);
	//right face
	glVertex3f(5, 3, 2);
	glVertex3f(5, 0.02, 2);
	glVertex3f(5, 0.02, -2);
	glVertex3f(5, 3, -2);
	glEnd();

	glColor3ub(120, 84, 47);
	glBegin(GL_QUADS);
	glVertex3f(2, 3, 0);
	glVertex3f(2.3, 3, 0);
	glVertex3f(2.3, 9, 0);
	glVertex3f(2, 9, 0);

	glVertex3f(2, 3, -0.2);
	glVertex3f(2, 3, 0);
	glVertex3f(2, 9, 0);
	glVertex3f(2, 9, -0.2);

	glVertex3f(2.3, 3, 0);
	glVertex3f(2.3, 3, -0.2);
	glVertex3f(2.3, 9, -0.2);
	glVertex3f(2.3, 9, 0);

	glVertex3f(2, 3, -0.2);
	glVertex3f(2, 9, -0.2);
	glVertex3f(2.3, 9, -0.2);
	glVertex3f(2.3, 3, -0.2);

	glEnd();



}

///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
	GLUquadricObj *pObj;	// Quadric Object
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	GLfloat horizontalMovement = 1;
	GLfloat verticalMovement = 0;
	rot += 1;

	horizontalMovement = MOVEDELTA;
	if (lookDown)
	{
		xRotationAngle -= ANGLEDELTA;
		if (xRotationAngle <= -90)
			xRotationAngle = -90;
	}
	if (lookUp)
	{
		xRotationAngle += ANGLEDELTA;
		if (xRotationAngle >= 90)
			xRotationAngle = 90;
	}
	if (lookLeft)
	{
		yRotationAngle -= ANGLEDELTA;
		if (yRotationAngle <= 0)
			yRotationAngle = 360;
	}
	if (lookRight)
	{
		yRotationAngle += ANGLEDELTA;
		if (yRotationAngle >= 360)
			yRotationAngle = 0;
	}
	horizontalMovement = cos(xRotationAngle*PI / 180)*MOVEDELTA;
	verticalMovement = sin(xRotationAngle*PI / 180)*MOVEDELTA;
	if (walkForward)
	{
		zCameraLocation -= cos(yRotationAngle*PI / 180)*horizontalMovement;
		xCameraLocation += sin(yRotationAngle*PI / 180)*horizontalMovement;
		yCameraLocation += verticalMovement;
	}
	if (walkBackward)
	{
		zCameraLocation += cos(yRotationAngle*PI / 180)*horizontalMovement;
		xCameraLocation -= sin(yRotationAngle*PI / 180)*horizontalMovement;
		yCameraLocation -= verticalMovement;
	}
	if (strafeRight)
	{
		zCameraLocation -= cos((yRotationAngle + 90)*PI / 180)*MOVEDELTA;
		xCameraLocation += sin((yRotationAngle + 90)*PI / 180)*MOVEDELTA;
	}
	if (strafeLeft)
	{
		zCameraLocation -= cos((yRotationAngle - 90)*PI / 180)*MOVEDELTA;
		xCameraLocation += sin((yRotationAngle - 90)*PI / 180)*MOVEDELTA;
	}


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(-xRotationAngle, 1, 0, 0);
	glRotatef(yRotationAngle, 0, 1, 0);
	glTranslatef(-xCameraLocation, -yCameraLocation, -zCameraLocation);


	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glRotatef(-xRotationAngle, 1, 0, 0);
	glRotatef(yRotationAngle, 0, 1, 0);
	glTranslatef(-xCameraLocation, -yCameraLocation, -zCameraLocation);




	glTranslatef(0, -6, -80);
	glColor3f(1, 0, 0);
	drawGrass();
	//	drawBackground();
	//drawStars();
	drawRiver();


	glPushMatrix();

	glRotatef(45, 0, 1, 0);
	//	drawBoat();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 0.01, -10);

	glPushMatrix();
	glTranslatef(0, 10, 0);
	glRotated(rot, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.9, 0.9, 0);
	glutWireSphere(5, 40, 20);

	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(rot, 1, 0, 0);
	glTranslatef(0, 10, 0);
	glutSolidSphere(2, 40, 20);
	glPopMatrix();

	glPushMatrix();
	glRotatef(rot, 0, 1, 0);
	glTranslatef(10, 0, 0);
	glutSolidSphere(2, 40, 20);
	glPopMatrix();


	glPushMatrix();
	glRotatef(rot, 1, 1, 0);
	glTranslatef(0, 0, 10);
	glutSolidSphere(2, 40, 20);
	glPopMatrix();

	glPopMatrix();

	drawPyramid();
	glPopMatrix();



	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0, 30, -200);
	glutSolidSphere(100, 20, 10);

	/*		glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(-7, 2, 0);
	glutSolidSphere(13, 20, 10);
	glPopMatrix();
	*/
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-10, 4, 30);
	glutSolidSphere(3, 20, 10);
	glPopMatrix();

	glutSolidSphere(5, 20, 10);

	glPopMatrix();
	glPopMatrix();



	// Flush drawing commands

	glutSwapBuffers();


}

void TimerFunction(int value)
{
	// Redraw the scene with new coordinates
	glutPostRedisplay();
	glutTimerFunc(16, TimerFunction, 1);
}

///////////////////////////////////////////////////////////
// Setup the rendering context
void SetupRC(void)
{
	lookUp = false;
	lookDown = false;
	lookLeft = false;
	lookRight = false;
	walkForward = false;
	walkBackward = false;
	strafeLeft = false;
	strafeRight = false;
	yRotationAngle = 0;
	xRotationAngle = 0;
	zRotationAngle = 0;
	xCameraLocation = 0;
	yCameraLocation = 0;
	zCameraLocation = 0;
	// White background
	glClearColor(0.5f, 0.95f, 1.0f, 1.0f);

	// Set drawing color to green
	glColor3f(0.0f, 1.0f, 0.0f);

	// Set color shading model to flat
	glShadeModel(GL_SMOOTH);

	// Clock wise wound polygons are front facing, this is reversed
	// because we are using triangle fans
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);

	xCameraLocation = 0;
	yCameraLocation = 0.5;
	zCameraLocation = 10.0;









}

void ChangeSize(int w, int h)
{
	//GLfloat nRange = 100.0f;

	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset projection matrix stack
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
	GLfloat fAspect;
	fAspect = (GLfloat)w / (GLfloat)h;
	//glOrtho(-10,10,-10,10,0,1000);
	gluPerspective(45, fAspect, 0.1, 1000);

	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}
// Respond to arrow keys by moving the camera frame of reference
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		lookDown = true;

	if (key == GLUT_KEY_DOWN)
		lookUp = true;

	if (key == GLUT_KEY_LEFT)
		lookLeft = true;

	if (key == GLUT_KEY_RIGHT)
		lookRight = true;

	// Refresh the Window
	glutPostRedisplay();
}
void SpecialKeysUp(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		lookDown = false;

	if (key == GLUT_KEY_DOWN)
		lookUp = false;

	if (key == GLUT_KEY_LEFT)
		lookLeft = false;

	if (key == GLUT_KEY_RIGHT)
		lookRight = false;


	glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'w':
		walkForward = true;
		break;
	case 's':
		walkBackward = true;
		break;
	case 'a':
		strafeLeft = true;
		break;
	case 'd':
		strafeRight = true;
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}

}

void keyboardUpFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		walkForward = false;
		break;
	case 's':
		walkBackward = false;
		break;
	case 'a':
		strafeLeft = false;
		break;
	case 'd':
		strafeRight = false;
		break;
	default:
		break;
	}


}
///////////////////////////////////////////////////////////
// Main program entry point
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Assignment 1");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys);
	glutSpecialUpFunc(SpecialKeysUp);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutKeyboardFunc(keyboardFunc);
	glutPassiveMotionFunc(mouseMovement);
	glutTimerFunc(16, TimerFunction, 1);
	SetupRC();

	glutMainLoop();

	return 0;
}

