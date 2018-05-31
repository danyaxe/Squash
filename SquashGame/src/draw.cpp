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

		//Squash Ball
		glBindTexture(GL_TEXTURE_2D, 0); 
		
		/* Texture for Ball */
		currentTexture = textures[T_DEF];
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, currentTexture);
			sphere(ballPosition[0], -ballPosition[1], ballPosition[2], ballSize, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Raquet 
		glPushMatrix();
		glTranslated(raquetPosition[0], raquetPosition[1], raquetPosition[2]);
		glScaled(.10, .10, .10);
		glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			glColor4f(0.3, 1.0, 1.0,0.1);	// Turquoise
			glVertex3fv(vertE); //P1
			glVertex3fv(vertF); //P2
			glVertex3fv(vertH); //P3
			glVertex3fv(vertG); //P4
		glEnd();
		glPopMatrix();
		
		/*cilinder(raquetPosition[0], raquetPosition[1], raquetPosition[2], .05, .25, raquetRotation[0], raquetRotation[1], raquetRotation[2], DEF_D);*/
	}
	else
	{
		drawLight();
		drawOrthoRoom();
		
		//Squash Ball
		glBindTexture(GL_TEXTURE_2D, 0);

		/* Texture for Ball */
		currentTexture = textures[T_DEF];
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, currentTexture);

		glPushMatrix();
			glTranslated(ballPosition[0], -ballPosition[1], ballPosition[2]);
			glutSolidSphere(.05, 30, 30);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);

		// Raquet 
		glPushMatrix();
		glTranslated(raquetPosition[0], raquetPosition[1], raquetPosition[2]);
		glScaled(.05, .05, .05);
		glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			glColor3f(0.0, 1.0, 1.0);	// Turquoise
			glVertex3fv(vertE); //P1
			glVertex3fv(vertF); //P2
			glVertex3fv(vertH); //P3
			glVertex3fv(vertG); //P4
		glEnd();
		glPopMatrix();
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

	/* Texture of Walls*/
	glBindTexture(GL_TEXTURE_2D, 0);
	currentTexture = textures[T_WALL];
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, currentTexture);

	/* Background Room */
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);

	glTexCoord2f(1, 1); glVertex3fv(vertA); //P1
	glTexCoord2f(1, 0); glVertex3fv(vertB); //P2
	glTexCoord2f(0, 0); glVertex3fv(vertD); //P3
	glTexCoord2f(0, 1); glVertex3fv(vertC); //P4
	glEnd();

	/* Right room side */
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);

	glTexCoord2f(1, 0); glVertex3fv(vertA); //P1
	glTexCoord2f(0, 0); glVertex3fv(vertB); //P2
	glTexCoord2f(0, 1); glVertex3fv(vertF); //P3
	glTexCoord2f(1, 1); glVertex3fv(vertE); //P4
	glEnd();

	/* Left room side */
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);

	glTexCoord2f(1, 1); glVertex3fv(vertC); //P1
	glTexCoord2f(1, 0); glVertex3fv(vertD); //P2
	glTexCoord2f(0, 0); glVertex3fv(vertH); //P3
	glTexCoord2f(0, 1); glVertex3fv(vertG); //P4
	glEnd();

	/* Texture of Floor*/
	glBindTexture(GL_TEXTURE_2D, 0);
	currentTexture = textures[T_FLOOR];
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, currentTexture);

	/* Floor */
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);

	glTexCoord2f(1, 1); glVertex3fv(vertB); //P1
	glTexCoord2f(0, 1); glVertex3fv(vertD); //P2
	glTexCoord2f(0, 0); glVertex3fv(vertH); //P3
	glTexCoord2f(1, 0); glVertex3fv(vertF); //P4
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();
}

void drawPerspectiveRoom()
{
	/* NO FRONT FACE */
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);

	/* Texture of Walls*/
	glBindTexture(GL_TEXTURE_2D, 0);
	currentTexture = textures[T_WALL];
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, currentTexture);

	/* Background Room */
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	
	glTexCoord2f(1, 1); glVertex3fv(vertA); //P1
	glTexCoord2f(1, 0); glVertex3fv(vertB); //P2
	glTexCoord2f(0, 0); glVertex3fv(vertD); //P3
	glTexCoord2f(0, 1); glVertex3fv(vertC); //P4
	glEnd();

	/* Right room side */
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	
	glTexCoord2f(1, 0); glVertex3fv(vertA); //P1
	glTexCoord2f(0, 0); glVertex3fv(vertB); //P2
	glTexCoord2f(0, 1); glVertex3fv(vertF); //P3
	glTexCoord2f(1, 1); glVertex3fv(vertE); //P4
	glEnd();

	/* Left room side */
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	
	glTexCoord2f(1, 1); glVertex3fv(vertC); //P1
	glTexCoord2f(1, 0); glVertex3fv(vertD); //P2
	glTexCoord2f(0, 0); glVertex3fv(vertH); //P3
	glTexCoord2f(0, 1); glVertex3fv(vertG); //P4
	glEnd();


	/* Texture of Ceiling*/
	glBindTexture(GL_TEXTURE_2D, 0);
	currentTexture = textures[T_CEIL];
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, currentTexture);

	/* Ceiling */
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	
	glTexCoord2f(0, 1); glVertex3fv(vertA); //P1
	glTexCoord2f(0, 0); glVertex3fv(vertC); //P2
	glTexCoord2f(1, 0); glVertex3fv(vertG); //P3
	glTexCoord2f(1, 1); glVertex3fv(vertE); //P4
	glEnd();


	/* Texture of Floor*/
	glBindTexture(GL_TEXTURE_2D, 0); 
	currentTexture = textures[T_FLOOR];
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, currentTexture);
	
	/* Floor */
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	
	glTexCoord2f(1, 1); glVertex3fv(vertB); //P1
	glTexCoord2f(0, 1); glVertex3fv(vertD); //P2
	glTexCoord2f(0, 0); glVertex3fv(vertH); //P3
	glTexCoord2f(1, 0); glVertex3fv(vertF); //P4
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glPopMatrix();
}
