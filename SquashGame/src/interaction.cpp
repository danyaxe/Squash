#include "screencasts.h"

/* Global State Event */
//const char *mouseBtnPressed = "";
//const char *mouseState = "";
//int keyPressed = 0;

//const char *specialPressed = "";
//const char *modifiers = "";
//int mouseX, mouseY = 0;

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
	else if (key == '1') toggleAxes = 1 - toggleAxes;
	else if (key == '2') toggleValues = 1 - toggleValues;
	else if (key == '3') toggleMode = 1 - toggleMode;

	/* Change field of view angle */
	else if (key == '-') fov--;
	else if (key == '+') fov++;
	/* Change dimensions */ // NO USAGE
	/*
	else if (key == 'D') dim += 0.25;
	else if (key == 'd') dim -= 0.25;
	*/

	/* Reset View Angle to center */
	if (toggleMode && key == 32)
	{
		eyeP[0] = 0.0;
		eyeP[1] = 0.0;
		eyeP[2] = 2.0;
		fov = 90;
	}
	else if (key == 32) {
		th = 45;
		ph = -75;
		dim = 2.75;
	}

	/* LIGHTING */
	else if (key == 'l' || key == 'L') toggleLight = 1 - toggleLight;
	/* Move light (rotation -> deg) */
	else if (key == '<') lightPh -= 5;
	else if (key == '>') lightPh += 5;
	/* Move light (elevation -> int) */
	else if (key == '[') lightY -= .2;
	else if (key == ']') lightY += .2;
	/* Move light (distance -> int ) */
	else if (key == '{') lightD -= 1;
	else if (key == '}') lightD += 1;
	/* Change Ortho Box Dimension */
	else if (key == 'i') dim -= 0.5;
	else if (key == 'I') dim += 0.5;
	/* Ambient Level */
	else if (key == 'a' && ambient > 0) ambient -= 5;
	else if (key == 'A' && ambient < 100) ambient += 5;
	/* Diffuse Level */
	else if (key == 'd' && diffuse > 0) diffuse -= 5;
	else if (key == 'D' && diffuse < 100) diffuse += 5;
	/* Specular Level */
	else if (key == 's' && specular > 0) specular -= 5;
	else if (key == 'S' && specular < 100) specular += 5;
	/* Emission Level */
	else if (key == 'e' && emission > 0) emission -= 5;
	else if (key == 'E' && emission < 100) emission += 5;
	/* Shininess Level */
	else if (key == 'n' && shininess > -1) shininess -= 1;
	else if (key == 'N' && shininess < 7) shininess += 1;
	else if (key == 'r' || key == 'R')
	{
		ballPosition[0] = 0.0;
		ballPosition[1] = 0.0;
		ballPosition[2] = 0.0;
	}
	/* Translate shininess power to value (-1 => 0) */
	shinYvec[0] = shininess < 0 ? 0 : pow(2.0, shininess);

	redisplayAll();

	glutPostRedisplay();
}

/*
* windowSpecial
* -------
* GLUT calls this when a special key is pressed
*/
void windowSpecial(int key, int x, int y)
{
	int modifiers = glutGetModifiers();
	
	/* Display - Set View Angle */

	/* PERSPECTIVE VIEW MODE */
	if (toggleMode) {
		// Right arrow key - increase eyeP X coordinate by 0.05 degrees
		if (key == GLUT_KEY_RIGHT)
		{
			if (eyeP[0] >= 0 && eyeP[0] < 1)
			{
				eyeP[0] += 0.05;
				fov--;
			}
			else if (eyeP[0] <= 0)
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
			else if (eyeP[0] >= 0)
			{
				eyeP[0] -= 0.05;
				fov++;
			}
		}
		// Up arrow key - increase eyeP Y coordinate by 0.05 degrees
		else if (key == GLUT_KEY_UP)
		{
			if (eyeP[1] >= 0 && eyeP[1] < 0.4)
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
			if (eyeP[1] <= 0 && eyeP[1] > -0.4)
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
	/* ORTHOGONAL VIEW MODE */
	else {
		if (modifiers == GLUT_ACTIVE_SHIFT)
		{
			/*  If holding shift, then just shift screen*/

			if (key == GLUT_KEY_RIGHT) ecX += .5;
			else if (key == GLUT_KEY_LEFT) ecX -= .5;
			else if (key == GLUT_KEY_DOWN) ecZ += .5;
			else if (key == GLUT_KEY_UP) ecZ -= .5;
		}
		else
		{
			/*  If not holding shift, then rotate/elevate */

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
	}

	redisplayAll();
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
