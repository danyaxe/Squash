#include "screencasts.h"

/* PI definition */
#define PI 3.1415926535898

/* Macro for sin & cos in degrees */
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))

/* GLOBALS */
const char *windowName = "Squash";
int windowWidth = 500;
int windowHeight = 450;

/*
 *	Projection Mode
 */
void project(int toggleMode, double dim, int fov, int asp)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (toggleMode) {
		/* perspective projection */
		gluPerspective(fov,windowWidth/windowHeight, (dim-0.75), (dim-0.75)*20);
	}
	else {
		/* orthogonal projection */
		glOrtho(-dim * asp, +dim * asp, -dim, +dim, -dim, +dim);
		
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
 *	Display Scene
 */
void display()
{
	/* Clear the image */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	/* Enable Z-Buffering in OpenGL */
	glEnable(GL_DEPTH_TEST);

	/* Reset previous transforms */
	glLoadIdentity();

	/* Set View Angle */
	setViewAngle();
	
	/*Draws*/
	drawScene();
	reshape(windowWidth, windowHeight);
	/* SCREEN INFO */
	/*
	printAt(5, 105, "mouse button = %s", mouseBtnPressed);
	printAt(5, 85, "mouse state = %s", mouseState);
	printAt(5, 65, "key = %d", keyPressed);
	printAt(5, 45, "special = %s", specialPressed);
	printAt(5, 25, "modifiers = %s", modifiers);
	printAt(5, 05, "mouse x=%d, mouse y=%d", mouseX, mouseY);
	*/

	/*
	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glutSolidSphere(1, 40, 40);
	glPopMatrix();
	*/

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE| GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow(windowName);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(windowKey);
	glutSpecialFunc(windowSpecial);

	glutCreateMenu(windowMenu);
	glutAddMenuEntry("Toggle Axes [a]", 'a');
	glutAddMenuEntry("Toggle Values [v]", 'v');
	glutAddMenuEntry("Toggle Mode [m]", 'm');
	glutAttachMenu(GLUT_RIGHT_BUTTON);
		
	glutMouseFunc(windowMouse);
	glutPassiveMotionFunc(windowPmotion);

	glutMainLoop();
	return 0;
}
