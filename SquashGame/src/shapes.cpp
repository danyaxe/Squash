#include "screencasts.h"

/*
* Draw a cube
* at (x,y,z)
* dimensions (dx, dy, dz)
* rotation (ox, oy, oz)
*/
void cube(double x, double y, double z, double dx, double dy, double dz, double ox, double oy, double oz) 
{
	glPushMatrix();
	/* Transform cube */
	glTranslated(x, y, z);
	glRotated(ox, 1, 0, 0);
	glRotated(oy, 0, 1, 0);
	glRotated(oz, 0, 0, 1);
	glScaled(dx, dy, dz);

	/* Cube */
	glBegin(GL_QUADS);
	// Background Room
	glNormal3f(0, 0, -1);
	glColor3f(1.0, 1.0, 0.0);	// Yellow 
	glVertex3fv(vertA);
	glVertex3fv(vertB);
	glVertex3fv(vertD);
	glVertex3fv(vertC);
						// Right room side
	glNormal3f(1, 0, 0);
	glColor3f(1.0, 0.0, 0.0);	// Red
	glVertex3fv(vertA);
	glVertex3fv(vertB);
	glVertex3fv(vertF);
	glVertex3fv(vertE);
						// Left room side
	glNormal3f(-1, 0, 0); 
	glColor3f(0.0, 0.0, 1.0);	// Blue
	glVertex3fv(vertC);
	glVertex3fv(vertD);
	glVertex3fv(vertH);
	glVertex3fv(vertG);
						// Floor
	glNormal3f(0, -1, 0);
	glColor3f(1.0, 0.0, 1.0);	// Pink
	glVertex3fv(vertB);
	glVertex3fv(vertD);
	glVertex3fv(vertH);
	glVertex3fv(vertF);
						
						/* Front Face */
	glNormal3f(0, 0, 1);
	glColor3f(0.0, 1.0, 1.0);	// Turquoise
	glVertex3fv(vertE);
	glVertex3fv(vertF);
	glVertex3fv(vertH);
	glVertex3fv(vertG);

						/* Ceiling */
	glNormal3f(0, 1, 0);
	glColor3f(0.0, 1.0, 0.0);	// Green
	glVertex3fv(vertA);
	glVertex3fv(vertC);
	glVertex3fv(vertG);
	glVertex3fv(vertE);
	glEnd();

	glPopMatrix();
}

/*
* Draw a cone
* at (x,y,z)
* radius - r / height - h
* rotation (ox, oy, oz)
* 360/deg sides
*/
void cone(double x, double y, double z, double r, double h, double ox, double oy, double oz, int deg)
{
	int k;
	glPushMatrix();

	/* Transformation */
	glTranslated(x, y, z);
	glRotated(ox, 1, 0, 0);
	glRotated(oy, 0, 1, 0);
	glRotated(oz, 0, 0, 1); 
	glScaled(r, h, r);

	/* sides */
	glBegin(GL_TRIANGLES);
	for (k = 0; k <= 360; k += deg)
	{
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0, 0, 1);
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(Cos(k), Sin(k), 0);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(Cos(k+deg), Sin(k+deg), 0);
	}
	glEnd();

	/* Bottom circle */
	/* rotated back */
	glRotated(90, 1, 0, 0);
	glBegin(GL_TRIANGLES);
	for (k = 0; k <= 360; k += deg)
	{
		glColor3f(1.0, 0.0, 0.0); 
		glVertex3f(0, 0, 0);
		glColor3f(1.0, 0.0, 1.0);
		glVertex3f(Cos(k), 0, Sin(k));
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(Cos(k + deg), 0, Sin(k + deg));
	}
	glEnd();
	glPopMatrix();
}

/*
* Draw a sphere
* at (x,y,z)
* dimensions (dx, dy, dz)
*/
void sphere(double x, double y, double z, double r, double rot)
{
	int th2, ph2;
	float emissions[] = { 0.0,0.0,0.01*emission,1.0 };

	/*
		Material shininess = specular exponent
		Material specular = specular color of material
		Material emission = simulates original lighting from an object
	*/
	glMaterialfv(GL_FRONT, GL_SHININESS, shinYvec);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellow4fv);
	glMaterialfv(GL_FRONT, GL_EMISSION, emissions);

	glPushMatrix();
	/* Transformation */
	glTranslated(x, y, z);
	glRotated(rot, 1, 0, 0);
	glScaled(r, r, r);

	/* Sphere */
	for (ph2 = -90; ph2 < 90; ph2 += DEF_D)
	{
		glBegin(GL_QUAD_STRIP);
		for (th2 = 0; th2 <= 360; th2 += 2 * DEF_D)
		{
			glColor3f(0.0, 1.0, 0.0);
			vertex(th2, ph2);
			glColor3f(0.0, 0.0, 1.0);
			vertex(th2, ph2 + DEF_D);
		}
		glEnd();
	}
	glPopMatrix();
}

/*
* Draw a cilinder
* at (x,y,z)
* radius - r / height - h
* rotation (ox, oy, oz)
*/
void cilinder(double x, double y, double z, double r, double h, double ox, double oy, double oz, int deg)
{
	int i, j, k;
	glPushMatrix();

	/* Transformation */
	glTranslated(x, y, z);
	glRotated(ox, 1, 0, 0);
	glRotated(oy, 0, 1, 0);
	glRotated(oz, 0, 0, 1);
	glScaled(r, h, r);

	glBegin(GL_QUAD_STRIP);
	for (j = 0; j <= 360; j += deg)
	{
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(Cos(j), +1, Sin(j));
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(Cos(j), -1, Sin(j));
	}
	glEnd();
	
	/* top and bottom circles */
	/* reuse the current Texture on top and bottom */
	for (i = 1; i >= -1; i -= 2)
	{
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0, i, 0);
		for (k = 0; k <= 360; k += deg)
		{
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(i*Cos(k), i, Sin(k));
		}
		glEnd();
	}
	glPopMatrix();
}

/*
* Draw vertex for sphere
*/
void vertex(double th2, double ph2)
{
	double x = Sin(th2)*Cos(ph2);
	double y = Cos(th2)*Cos(ph2);
	double z = Sin(ph2);
	
	glNormal3d(x, y, z);
	glVertex3d(x, y, z);
}