#include "screencasts.h"

/*
*	Draw Scene
*/
void drawScene()
{
	drawAxes();
	drawValues();

	if (toggleMode) 
		drawPerspectiveRoom();
	else 
		drawOrthoRoom();
}

/*
*	Draw Axes
*/
void drawAxes()
{
	if (toggleAxes) {

		/* Lenght of Axes */
		GLfloat len = 3.0;
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(len, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, len, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, len);
		glEnd();

		/* Label Axes */
		glRasterPos3d(len, 0, 0);
		print("X");
		glRasterPos3d(0, len, 0);
		print("Y");
		glRasterPos3d(0, 0, len);
		print("Z");
	}
	errCheck("error in draw axes");
}

/*
*	Draw Values
*/
void drawValues()
{
	if (toggleValues) {
		glColor3f(0.8, 0.8, 0.8);
		glRasterPos2d(50, 50);
		print("View Angle (th,ph) =(%d, %d)", th, ph);
		print("Projection mode= (%s)", toggleMode ? "Perspective" : "Orthogonal");
	}
	errCheck("error in draw values");
}

/*
*	Draw Ortho Room
*/
void drawOrthoRoom()
{
	// NO CEILING NO FRONT FACES
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	// Background Room
	glColor3f(1.0, 1.0, 0.0);	// Yellow 
	glVertex3fv(vertA); //P1
	glVertex3fv(vertB); //P2
	glVertex3fv(vertD); //P3
	glVertex3fv(vertC); //P4
						// Right room side
	glColor3f(1.0, 0.0, 0.0);	// Red
	glVertex3fv(vertA); //P1
	glVertex3fv(vertB); //P2
	glVertex3fv(vertF); //P3
	glVertex3fv(vertE); //P4
						// Left room side
	glColor3f(0.0, 0.0, 1.0);	// Blue
	glVertex3fv(vertC); //P1
	glVertex3fv(vertD); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertG); //P4
						// Floor
	glColor3f(1.0, 0.0, 1.0);	// Pink
	glVertex3fv(vertB); //P1
	glVertex3fv(vertD); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertF); //P4
						
						/* Front Face */
	//glColor3f(0.0, 1.0, 1.0);	// Turquoise
	//glVertex3fv(vertE); //P1
	//glVertex3fv(vertF); //P2
	//glVertex3fv(vertH); //P3
	//glVertex3fv(vertG); //P4

						/* Ceiling */
	//glColor3f(0.0, 1.0, 0.0);	// Green
	//glVertex3fv(vertA); //P1
	//glVertex3fv(vertC); //P2
	//glVertex3fv(vertG); //P3
	//glVertex3fv(vertE); //P4

	glEnd();
	glPopMatrix();
}

/*
*	Draw Perspective Room
*/
void drawPerspectiveRoom()
{
	// NO FRONT FACE
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	// Background Room
	glColor3f(1.0, 1.0, 0.0);	// Yellow 
	glVertex3fv(vertA); //P1
	glVertex3fv(vertB); //P2
	glVertex3fv(vertD); //P3
	glVertex3fv(vertC); //P4
						// Right room side
	glColor3f(1.0, 0.0, 0.0);	// Red
	glVertex3fv(vertA); //P1
	glVertex3fv(vertB); //P2
	glVertex3fv(vertF); //P3
	glVertex3fv(vertE); //P4
						// Ceiling
	glColor3f(0.0, 1.0, 0.0);	// Green
	glVertex3fv(vertA); //P1
	glVertex3fv(vertC); //P2
	glVertex3fv(vertG); //P3
	glVertex3fv(vertE); //P4
						// Left room side
	glColor3f(0.0, 0.0, 1.0);	// Blue
	glVertex3fv(vertC); //P1
	glVertex3fv(vertD); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertG); //P4
						// Floor
	glColor3f(1.0, 0.0, 1.0);	// Pink
	glVertex3fv(vertB); //P1
	glVertex3fv(vertD); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertF); //P4

						/* Front Face */
	//glColor3f(0.0, 1.0, 1.0);	// Turquoise
	//glVertex3fv(vertE); //P1
	//glVertex3fv(vertF); //P2
	//glVertex3fv(vertH); //P3
	//glVertex3fv(vertG); //P4
	glEnd();
	glPopMatrix();
}
