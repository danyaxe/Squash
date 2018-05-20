#include "screencasts.h"

void initializeGlobal(void)
{
	/* GLOBALS */
	const char *windowName = "Squash";
	int windowWidth = 500;
	int windowHeight = 450;

	/* Toggles */
	int toggleAxes = 0; /* toggle axes on and off */
	int toggleValues = 1; /* toggle values on and off */
	int toggleMode = 0; /* projection mode */

	/* Display View */
	double dim = 1.75; /*dimension of Ortho box*/

	int th = 0;		/* azimuth of view angle */
	int ph = 0;		/* elevation of view angle */

	int fov = 90;	/* field of view for perspective */
	int asp = 1;	/* aspect ratio */

	GLfloat eyeP[] = { 0.0,0.0,2.0 }; /* eye camera pointer */

	/* Objects */
	int objId = 0;		/* object to draw */
	int objSlices = 16; /* slices lines of longitude */
	int objStacks = 16; /* stacks lines of latitude */

	// Background Vertex
	GLfloat vertA[3] = { 1.0, 1.0, -1.0 };
	GLfloat vertB[3] = { 1.0,-1.0, -1.0 };
	GLfloat vertC[3] = { -1.0, 1.0, -1.0 };
	GLfloat vertD[3] = { -1.0,-1.0, -1.0 };

	// Front Vertex
	GLfloat vertE[3] = { 1.0, 1.0, 1.0 };
	GLfloat vertF[3] = { 1.0,-1.0, 1.0 };
	GLfloat vertG[3] = { -1.0, 1.0, 1.0 };
	GLfloat vertH[3] = { -1.0,-1.0, 1.0 };
}