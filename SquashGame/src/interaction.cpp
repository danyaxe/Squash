#include "screencasts.h"

/* Globals */
double dim = 1.75; /*dimension of Ortho box*/

/* Toggles */
int toggleAxes = 0; /* toggle axes on and off */
int toggleValues = 1; /* toggle values on and off */
int toggleMode = 0; /* projection mode */

/* Display View */
int th = 0;		/* azimuth of view angle */
int ph = 0;		/* elevation of view angle */

int fov = 90;	/* field of view for perspective */
int asp = 1;	/* aspect ratio */

GLfloat eyeP[] = { 0.0,0.0,2.0 }; /* eye camera pointer */

/* Global State Event */
//const char *mouseBtnPressed = "";
//const char *mouseState = "";
//int keyPressed = 0;

//const char *specialPressed = "";
//const char *modifiers = "";
//int mouseX, mouseY = 0;

void drawScene()
{

	drawAxes(toggleAxes);
	drawValues(toggleValues, ph, th);
	if (toggleMode) drawPerspectiveRoom();
	else drawOrthoRoom();
}

/*
* reshape
* -------
* GLUT calls this routine when the window is resized
*/
void reshape(int width, int height)
{
	asp = (height > 0) ? (double)width / height : 1;
	glViewport(0, 0, width, height);
	project(toggleMode, dim, fov, asp);
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
	else if (key == 'v' || key == 'V') toggleValues = 1 - toggleValues;
	else if (key == 'm' || key == 'M') toggleMode = 1 - toggleMode;
	/* Change field of view angle */
	else if (key == '-') fov--;
	else if (key == '+') fov++;
	/* Change dimensions */
	else if (key == 'D') dim += 0.25;
	else if (key == 'd') dim -= 0.25;
	// Reset View Angle to center
	if (toggleMode && key == 32)
	{
		eyeP[0] = 0.0;
		eyeP[1] = 0.0;
		eyeP[2] = 2.0;
		fov = 90;
	}
	else if (key == 32){
		th = 0;
		ph = 0;
		dim = 1.75;
	}

	/*if (currModifiers == GLUT_ACTIVE_SHIFT)
	modifiers = "SHIFT";
	else if (currModifiers == GLUT_ACTIVE_CTRL)
	modifiers = "CTRL";*/

	project(toggleMode, dim, fov, asp);
	glutPostRedisplay();
}

/*
* windowSpecial
* -------
* GLUT calls this when a special key is pressed
*/
void windowSpecial(int key, int x, int y)
{
	/* Display - Set View Angle */
	if (toggleMode) {
		// Right arrow key - increase eyeP X coordinate by 0.05 degrees
		if (key == GLUT_KEY_RIGHT)
		{
			if (eyeP[0] >= 0 && eyeP[0] < 1)
			{
				eyeP[0] += 0.05;
				fov--;
			}
			else if (eyeP[0] < 0)
			{
				eyeP[0] += 0.05;
				fov++;
			}
		}
		// Left arrow key - decrease eyeP X coordinate by .05 degrees
		else if (key == GLUT_KEY_LEFT)
		{
			if (eyeP[0] <= 0 && eyeP[0] > -1)
			{
				eyeP[0] -= 0.05;
				fov--;
			}
			else if (eyeP[0] > 0)
			{
				eyeP[0] -= 0.05;
				fov++;
			}
		}
		// Up arrow key - increase eyeP Y coordinate by 0.05 degrees
		else if (key == GLUT_KEY_UP)
		{
			if (eyeP[1] >= 0 && eyeP[1] <= 0.3)
			{
				eyeP[1] += 0.05;
				fov--;
			}
			else if (eyeP[1] < 0)
			{
				eyeP[1] += 0.05;
				fov++;
			}
		} 
		// Down arrow key - decrease eyeP Y coordinate by 0.05 degrees
		else if (key == GLUT_KEY_DOWN)
		{
			if (eyeP[1] <= 0 && eyeP[1] > -0.3)
			{
				eyeP[1] -= 0.05;
				fov--;
			}
			else if (eyeP[1] > 0)
			{
				eyeP[1] -= 0.05;
				fov++;
			}
		}
	}
	else {
		// Right arrow key - increase azimuth by 5 degrees
		if (key == GLUT_KEY_RIGHT) th += 5;
		// Left arrow key - decrease azimuth by 5 degrees
		else if (key == GLUT_KEY_LEFT) th -= 5;
		// Up arrow key - increase elevation by 5 degrees
		else if (key == GLUT_KEY_UP) ph += 5;
		// Down arrow key - decrease elevation by 5 degrees
		else if (key == GLUT_KEY_DOWN) ph -= 5;
		
		/* Keep angles to +/- 360 degrees */
		th %= 360;
		ph %= 360;
	}

	project(toggleMode, dim, fov, asp);
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

/*
* setViewAngle
* -------
* Define gluLookAt for Perspective View
* Define rotation for Orthogonal View
*/
void setViewAngle()
{
	/* Perspective - Set Eye Position */
	if (toggleMode) {
		/* Dinamic View */
		//double Ex = -2 *Sin(th)*Cos(ph);
		//double Ey = +2 *Sin(ph);
		//double Ez = +2 *Cos(th)*Sin(ph);

		///* Camera/ eje position, aim of camera lens, up-vector */
		//gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);

		/* Dinamic View - Cursor Keys*/
		gluLookAt(eyeP[0], eyeP[1], eyeP[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	}
	else
	{
		// Ortho Dynamic
		glRotated(ph + 90, 1, 0, 0); /* start from top (+90) */
		glRotated(th, 0, 1, 0);

		// Ortho Static - Top View
		//glRotated(90, 1, 0, 0);
	}

}