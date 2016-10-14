// CS 465
// Author:


#include "../shared/gltools.h"	// OpenGL toolkit
#define PI 3.14159265
#define MOVE_DELTA 0.5f
#define ANGLE_DELTA 2.0f
#define MOUSE_ANGLE_DELTA 0.1f

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
float sunRotationAngle=0;
float sunRadius = 150.0;
float day=0;
float dusk=1;
float forwardMovement = 1;
// Light values and coordinates
GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat	 lightPos2[] = { 0.0f, 0.0f, 50.0f, 1.0f };
GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  specular2[] = { 0.0f, 1.0f, 0.0f, 1.0f};
GLfloat  diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat  diffuse2[] = { 0.0f, 0.3f, 0.0f, 1.0f};
GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat  ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f};
GLfloat  spotDir[] = { 0.0f, 0.0f, -1.0f };

void drawTwoSidedTriangle()
{
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 1, 0);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);

	glNormal3f(0, 0, -1);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(-1, 0, 0);
	glEnd();
}
void drawPlane()
{
	glPushMatrix();
	//glTranslatef(0,5,0);
	glColor3ub(100, 100, 100);

	//wings
	glPushMatrix();
	glRotatef(90, -1, 0, 0);
	glScalef(5, 5, 5);
	drawTwoSidedTriangle();
	glPopMatrix();

	//nose
	glPushMatrix();
	glTranslatef(0, 0, -2);
	glRotatef(90, -1, 0, 0);
	glScalef(2, 5, 5);
	drawTwoSidedTriangle();
	glPopMatrix();

	//elevator
	glPushMatrix();
	glTranslatef(0, 0, 2);
	glRotatef(90, -1, 0, 0);
	glScalef(2, 4, 2);
	drawTwoSidedTriangle();
	glPopMatrix();

	//left tail
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(-.5, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(1, 2, 1);
	drawTwoSidedTriangle();
	glPopMatrix();
	//right tail
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(0.5, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(1, 2, 1);
	drawTwoSidedTriangle();
	glPopMatrix();

	//cockpit
	glPushMatrix();
	glTranslatef(0, 0, 2.5);
	glScalef(0.2, 0.7, 1.5);
	glColor3f(0.5, 0.5, 1);
	glPushMatrix();
	glTranslatef(-1, 0, -5);
	glRotatef(-45, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(1, 1.414, 1);
	drawTwoSidedTriangle();
	glPopMatrix();

	glColor3f(0.5, 0.5, 1);
	glPushMatrix();
	glTranslatef(1, 0, -5);
	glRotatef(45, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(1, 1.414, 1);
	drawTwoSidedTriangle();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -4.);
	glRotatef(-45, 1, 0, 0);
	glScalef(1, 1.414, 1);
	drawTwoSidedTriangle();
	glPopMatrix();

	glColor3f(0.5, 0.5, 1);
	glPushMatrix();
	glTranslatef(0, 0, -6);
	glRotatef(45, 1, 0, 0);
	glScalef(1, 1.414, 1);
	drawTwoSidedTriangle();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}
void mouseMovement(int x, int y) 
{
	int mouseDiffx=x-mouseLastx; 
	int mouseDiffy=y-mouseLasty; 
	mouseLastx=x; 
	mouseLasty=y; //set lasty to the current y position
	xRotationAngle -= ((GLfloat)mouseDiffy)*MOUSE_ANGLE_DELTA;
	yRotationAngle += ((GLfloat)mouseDiffx)*MOUSE_ANGLE_DELTA;
	if (xRotationAngle>=90)
			xRotationAngle=90;
	if (xRotationAngle<=-90)
			xRotationAngle=-90;

	//cout << "x:" << x << "y:" << y << endl;
}

///////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
	GLUquadricObj *pObj;	// Quadric Object
	pObj = gluNewQuadric(); 
	gluQuadricNormals(pObj, GLU_SMOOTH);
	GLfloat horizontalMovement=1;
	GLfloat verticalMovement=0;

	

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	/*glRotatef(-xRotationAngle,1,0,0);
	glRotatef(yRotationAngle,0,1,0);
	glTranslatef(-xCameraLocation,-yCameraLocation,-zCameraLocation);*/
	
	glTranslatef(0, -10, -50);
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);

	glColor3f(1,0.8,0);

	glColor3f(0,0,0);
	
	
	//desert
	glColor3ub(250, 223, 173);
	glBegin(GL_QUADS);
		glNormal3f(0,1,0);
		for (int i=-100;i<=100;i+=10)
			for (int j=-100;j<=100;j+=10)
			{

				glVertex3f(i+10,-0.1,j);
				glVertex3f(i, -0.1, j);
				glVertex3f(i, -0.1, j + 10);
				glVertex3f(i + 10, -0.1, j + 10);
			}
	glEnd();

	glEnable(GL_NORMALIZE);
	
	glPushMatrix();

		glTranslatef(xCameraLocation, 
			yCameraLocation, 
			zCameraLocation);
	
		glRotatef(-yRotationAngle, 0, 1, 0);


		glRotatef(xRotationAngle, 1, 0, 0);

		


		drawPlane();
	glPopMatrix();
	
	glLineWidth(2);
	glBegin(GL_LINES);
	//x
	glColor3f(1, 0, 0);
	glVertex3f(-10, 0, 0);
	glVertex3f(10, 0, 0);

	//y
	glColor3f(0, 1, 0);
	glVertex3f(0, -10, 0);
	glVertex3f(0, 10, 0);

	//z
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -10);
	glVertex3f(0, 0, 10);
	glEnd();


	// Flush drawing commands
	
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
	lookUp=false;
	lookDown=false;
	lookLeft=false;
	lookRight=false;
	walkForward=false;
	walkBackward=false;
	strafeLeft=false;
	strafeRight=false;
	yRotationAngle=0;
	xRotationAngle=0;
	zRotationAngle=0;
	xCameraLocation = 0;
	yCameraLocation = 5;
	zCameraLocation = 10.0;
	// White background
	glClearColor(0.5f,0.95f, 1.0f, 1.0f );

	// Set drawing color to green
	glColor3f(0.0f, 1.0f, 0.0f);

	// Set color shading model to flat
	glShadeModel(GL_SMOOTH);

	// Clock wise wound polygons are front facing, this is reversed
	// because we are using triangle fans
	glFrontFace(GL_CCW);

	 glEnable (GL_DEPTH_TEST);











}

void ChangeSize(int w, int h)
	{
	//GLfloat nRange = 100.0f;

	// Prevent a divide by zero
	if(h == 0)
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
	gluPerspective(45,fAspect,0.1,1000);
	
	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	
	}
// Respond to arrow keys by moving the camera frame of reference
void SpecialKeys(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_UP:
		xRotationAngle--;
		break;

	case GLUT_KEY_DOWN:
		xRotationAngle++;
		break;

	case GLUT_KEY_LEFT:
		yRotationAngle--;
		break;

	case GLUT_KEY_RIGHT:
		yRotationAngle++;
		break;

	default:
		break;
	}
                        
    // Refresh the Window
    glutPostRedisplay();
}


void keyboardFunc(unsigned char key, int x, int y)
{
	float VM = (sin(xRotationAngle*PI / 180.0)*forwardMovement);
	float HM = (cos(xRotationAngle*PI / 180.0)*forwardMovement);

	float dX = sin(yRotationAngle*PI / 180.0) * HM;
	float dZ = -cos(yRotationAngle * PI / 180.0) * HM;
	float dY = VM;

	float dXSide = 0;
	float dZSide = 0;
	float dYSide = 0;

	switch(key)
	{
	case 'w':
		xCameraLocation += dX;
		yCameraLocation += dY;
		zCameraLocation += dZ;
		break;
	case 's':
		xCameraLocation -= dX;
		yCameraLocation -= dY;
		zCameraLocation -= dZ;
			break;
	case 'a':
		dXSide = sin((yRotationAngle-90)*PI / 180.0) * 1;
		dZSide = -cos((yRotationAngle-90) * PI / 180.0) * 1;
		dYSide = 0;
		xCameraLocation += dXSide;
		yCameraLocation += dYSide;
		zCameraLocation += dZSide;
			break;
	case 'd':
		dXSide = sin((yRotationAngle + 90)*PI / 180.0) * 1;
		dZSide = -cos((yRotationAngle + 90) * PI / 180.0) * 1;
		dYSide = 0;
		xCameraLocation += dXSide;
		yCameraLocation += dYSide;
		zCameraLocation += dZSide;
			break;
	case 27:
		exit(0);
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
	glutInitWindowSize(800,800); 
 	glutCreateWindow("Assignment 1");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(keyboardFunc);
	glutPassiveMotionFunc(mouseMovement);
	glutTimerFunc(16,TimerFunction, 1);
	SetupRC();
	
	glutMainLoop();
    
    return 0;
}

