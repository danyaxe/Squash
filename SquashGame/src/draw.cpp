#include "screencasts.h"

/*
*	Draw Scene
*/
void drawScene()
{

	drawAxes();
	drawValues();

	if (toggleMode)
	{
		drawLight();
		drawPerspectiveRoom();
		//sphere(0, .5, 1, 0.1, 0);
		sphere(ballPosition[0], ballPosition[1], ballPosition[2], 0.1, 0);
	}
	else
	{
		drawLight();
		drawOrthoRoom();
		//sphere(0, .5, 1, 0.1, 0);
		sphere(ballPosition[0], ballPosition[1], ballPosition[2], 0.1, 0);
	}
}

/*
*	Draw Light
*/
void drawLight()
{
	/* Light Switch*/
	if (toggleLight)
	{
		/*Translate intensity to color vectors*/
		float Ambient[] = { 0.01*ambient, 0.01*ambient,0.01*ambient,1.0 };
		float Diffuse[] = { 0.01*diffuse, 0.01*diffuse,0.01*diffuse,1.0 };
		float Specular[] = { 0.01*specular, 0.01*specular,0.01*specular,1.0 };

		/* Light Position */
		float Position[] = { lightD*Cos(lightPh),lightY,lightD*(Sin(lightPh)),1.0 };

		/* Draw light position as sphere */
		glColor3fv(white3fv);
		glDisable(GL_LIGHTING);
		
		/* OpenGL should normalize vectors */
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);

		/* glColor sets ambient and diffuse color materials */
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHT0);

		/* Set ambient, diffuse, specular components and position of light 0 */
		glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
		glLightfv(GL_LIGHT0, GL_POSITION, Position);		
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
}


/*
*	Draw Axes
*/
void drawAxes()
{
	if (toggleAxes) {

		/* Lenght of Axes */
		GLfloat len = 5.0;
		glDisable(GL_LIGHTING);
		glColor3fv(white3fv);

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
	else
	{
		glEnable(GL_LIGHTING);
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
	glNormal3f(0, 0, 1);
	glColor3f(1.0, 1.0, 0.0);	// Yellow 
	glVertex3fv(vertA); //P1
	glVertex3fv(vertB); //P2
	glVertex3fv(vertD); //P3
	glVertex3fv(vertC); //P4
						// Right room side
	glNormal3f(-1, 0, 0);
	glColor3f(1.0, 0.0, 0.0);	// Red
	glVertex3fv(vertA); //P1
	glVertex3fv(vertB); //P2
	glVertex3fv(vertF); //P3
	glVertex3fv(vertE); //P4
						// Left room side
	glNormal3f(1, 0, 0);
	glColor3f(0.0, 0.0, 1.0);	// Blue
	glVertex3fv(vertC); //P1
	glVertex3fv(vertD); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertG); //P4
						// Floor
	glNormal3f(0, 1, 0); 
	glColor3f(1.0, 0.0, 1.0);	// Pink
	glVertex3fv(vertB); //P1
	glVertex3fv(vertD); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertF); //P4
						
						/* Front Face */
	glNormal3f(0, 0, -1);
	glColor3f(0.0, 1.0, 1.0);	// Turquoise
	glVertex3fv(vertE); //P1
	glVertex3fv(vertF); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertG); //P4

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
	glNormal3f(0, 0, 1);
	glColor3f(1.0, 1.0, 0.0);	// Yellow 
	glVertex3fv(vertA); //P1
	glVertex3fv(vertB); //P2
	glVertex3fv(vertD); //P3
	glVertex3fv(vertC); //P4
						// Right room side
	glNormal3f(-1, 0, 0);
	glColor3f(1.0, 0.0, 0.0);	// Red
	glVertex3fv(vertA); //P1
	glVertex3fv(vertB); //P2
	glVertex3fv(vertF); //P3
	glVertex3fv(vertE); //P4
						// Ceiling
	glNormal3f(0, -1, 0);
	glColor3f(0.0, 1.0, 0.0);	// Green
	glVertex3fv(vertA); //P1
	glVertex3fv(vertC); //P2
	glVertex3fv(vertG); //P3
	glVertex3fv(vertE); //P4
						// Left room side
	glNormal3f(1, 0, 0);
	glColor3f(0.0, 0.0, 1.0);	// Blue
	glVertex3fv(vertC); //P1
	glVertex3fv(vertD); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertG); //P4
						// Floor
	glNormal3f(0, 1, 0);
	glColor3f(1.0, 0.0, 1.0);	// Pink
	glVertex3fv(vertB); //P1
	glVertex3fv(vertD); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertF); //P4

						/* Front Face */
	glNormal3f(0, 0, -1); 
	glColor3f(0.0, 1.0, 1.0);	// Turquoise
	glVertex3fv(vertE); //P1
	glVertex3fv(vertF); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertG); //P4
	glEnd();
	glPopMatrix();
}
