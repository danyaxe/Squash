#include "screencasts.h"

/* GLOBALS */
double dim = 3.0; /*dimension of Ortho box*/
const char *windowName = "Squash";
int windowWidth = 500;
int windowHeight = 450;

/* Global State Event */
//const char *mouseBtnPressed = "";
//const char *mouseState = "";
//int keyPressed = 0;
//
//const char *specialPressed = "";
//const char *modifiers = "";
//int mouseX, mouseY = 0;

/* Toggles */
int toggleAxes = 0; /* toggle axes on and off */
int toggleValues = 1; /* toggle values on and off */

/* Display View */
int th = 0; /* azimuth of view angle */
int ph = 0; /* elevation of view angle */

/* Objects */
int objId = 0;		/* object to draw */
int objSlices = 16; /* slices lines of longitude */
int objStacks = 16; /* stacks lines of latitude */


/*
 *	Draw Axes
 */

void drawAxes()
{
	if (toggleAxes) {
		
		/* Lenght of Axes */
		double len = 2.0;
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
			glVertex3d(0, 0, 0);
			glVertex3d(len, 0, 0);
			glVertex3d(0, 0, 0);
			glVertex3d(0, len, 0);
			glVertex3d(0, 0, 0);
			glVertex3d(0, 0, len);
		glEnd();

		/* Label Axes */
		glRasterPos3d(len, 0, 0);
		print("X");
		glRasterPos3d(0, len, 0);
		print("Y");
		glRasterPos3d(0, 0, len);
		print("Z");
	}
}

/*
 *	Draw Axes
 */
void drawValues()
{
	if (toggleValues) {
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2d(50, 50);
		print("View Angle (th,ph) =(%d, %d)", th, ph);
	}
}

/*
 *	Display Scene
 */
void display()
{
	/* Clear the image */
	glClear(GL_COLOR_BUFFER_BIT);
	/* Reset previous transforms */
	glLoadIdentity();

	/* Set Vew Angle */
	glRotated(ph, 1, 0, 0);
	glRotated(th, 0, 1, 0);

	/*Draws*/
	drawAxes();
	drawValues();


	/* SCREEN INFO */
	/*printAt(5, 105, "mouse button = %s", mouseBtnPressed);
	printAt(5, 85, "mouse state = %s", mouseState);
	printAt(5, 65, "key = %d", keyPressed);
	printAt(5, 45, "special = %s", specialPressed);
	printAt(5, 25, "modifiers = %s", modifiers);
	printAt(5, 05, "mouse x=%d, mouse y=%d", mouseX, mouseY);*/

	/*glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glutSolidSphere(1, 40, 40);
	glPopMatrix();*/


	glFlush();
	glutSwapBuffers();
}


void reshape(int width, int height)
{
	double w2h = (height > 0) ? (double)width / height : 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-dim * w2h, +dim * w2h, -dim, +dim, -dim, +dim);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
 * windowKey
 * -------
 * GLUT calls this when a non-special key is pressed
 */
void windowKey(unsigned char key, int x, int y)
{
	//int currModifiers = glutGetModifiers();

	/* Exit on ESC */
	if (key == 27) exit(0);
	else if (key == 'a' || key == 'A') toggleAxes = 1 - toggleAxes;
	else if (key == 'a' || key == 'V') toggleValues = 1 - toggleValues;

	/* Spacebar - Toggle through shapes */
	else if (key == 32) {
		if (objId == 18) objId = 0;
		else objId++;
	}

	/*if (currModifiers == GLUT_ACTIVE_SHIFT)
		modifiers = "SHIFT";
	else if (currModifiers == GLUT_ACTIVE_CTRL)
		modifiers = "CTRL";*/

	glutPostRedisplay();
}

/*
 * windowSpecial 
 * -------
 * GLUT calls this when a special key is pressed 
 */

void windowSpecial(int key, int x, int y)
{
	/* Right arrow key - increase azimuth by 5 degrees */
	if (key == GLUT_KEY_RIGHT) th += 5;
	/* Left arrow key - decrease azimuth by 5 degrees */
	else if (key == GLUT_KEY_LEFT) th -= 5;
	/* Up arrow key - increase elevation by 5 degrees */
	else if (key == GLUT_KEY_UP) ph += 5;
	/* Down arrow key - decrease elevation by 5 degrees */
	else if (key == GLUT_KEY_DOWN) ph -= 5;

	/* Keep angles to +/- 360 degrees */
	th %= 360;
	ph %= 360;

	/*if (currModifiers == GLUT_ACTIVE_SHIFT)
		modifiers = "SHIFT";
	else if (currModifiers == GLUT_ACTIVE_CTRL)
		modifiers = "CTRL";*/

	glutPostRedisplay();
}

/*
 * windowMenu
 * -------
 * Window menu is the same as the keyboard clicks
 */

void windowMenu(int value)
{
	windowKey((unsigned char)value, 0, 0);
}

/*
 * windowMouse
 * -------
 * GLUT calls this when the mouse is clicked down or up
 */

void windowMouse(int btn, int state, int x, int y)
{
	/*if (btn == GLUT_LEFT_BUTTON)
		mouseBtnPressed = "LEFT";
	else if (btn == GLUT_RIGHT_BUTTON)
		mouseBtnPressed = "RIGHT";

	if (state == GLUT_DOWN)
		mouseState = "down";
	else if (state == GLUT_UP)
		mouseState = "up";

	glutPostRedisplay();*/
}

/*
 * windowPmotion
 * -------
 * GLUT calls this whenever the mouse is moved
 */
void windowPmotion(int x, int y)
{
	/*mouseX = x;
	mouseY = y;
	glutPostRedisplay();*/
}



int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow(windowName);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(windowKey);
	glutSpecialFunc(windowSpecial);

	glutCreateMenu(windowMenu);
	glutAddMenuEntry("Toggle Axes [a]", 'a');
	glutAttachMenu(GLUT_RIGHT_BUTTON);
		
	glutMouseFunc(windowMouse);
	glutPassiveMotionFunc(windowPmotion);

	glutMainLoop();
	return 0;
}
