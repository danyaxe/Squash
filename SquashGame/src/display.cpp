#include "screencasts.h"

/*
* displayInit()
* ----------
* Initializes display
*/
void displayInit()
{
	/* Clear the image */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	/* Enable Z-Buffering in OpenGL */
	glEnable(GL_DEPTH_TEST);
	/* Reset previous transforms */
	glLoadIdentity();
}

/*
* displayEye()
* ----------
* Define gluLookAt for Perspective View
* Define rotation for Orthogonal View
*/
void displayEye()
{
	if (toggleMode) {
		/* Perspective Dinamic View */
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
		/* Ortho Dinamic View */
		glRotated(ph + 90, 1, 0, 0); /* start from top (+90) */
		glRotated(th, 0, 1, 0);

		/* Ortho Dinamic View - Top View */
		//glRotated(90, 1, 0, 0);
	}
}

/*
* displayReshape
* ----------
* GLUT calls this routine when the window is resized
*/
void displayReshape(int width, int height)
{
	asp = (height > 0) ? (double)width / height : 1;
	glViewport(0, 0, width, height);
	displayProject();
}

/*
* displayProject()
* ----------
* Projection Mode
*/
void displayProject()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (toggleMode) {
		/* perspective projection */
		gluPerspective(fov, windowWidth / windowHeight, (dim - 0.75), (dim - 0.75) * 20);
	}
	else {
		/* orthogonal projection */
		glOrtho(-dim * asp, +dim * asp, -dim, +dim, -dim, +dim);

	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
* display()
* ----------
* Display the scene
*/
void display()
{
	/* Initializes display */
	displayInit();
	/* Set View Angle - Eye Position */
	displayEye();
	/* Draws - Axes, Values, Scene */
	drawScene();
	/* Reshape screen after draws */
	displayReshape(windowWidth, windowHeight);

	glFlush();
	glutSwapBuffers();

	errCheck("Display sanity check");
}