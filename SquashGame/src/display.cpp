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
	redisplayAll();
}

/*
* displayProject()
* ----------
* Projection Mode
*/
void displayProject(double fov, double asp, double dim)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (toggleMode) {
		/* perspective projection */
		gluPerspective(fov, windowWidth / windowHeight, (dim - 1.75), (dim - 1.75) * 20);
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

/*
*  redisplayAll
*  ------
*  This is called whenever we need to draw the display
*/
void redisplayAll()
{
	displayProject(fov, asp, dim);
	glutPostRedisplay();
}


/*Animation*/
void stepBall(int ms) {

	GLfloat dt = ms / 3000.0;

	ballPosition[0] = ballPosition[0] + (ballVelocity[0] * dt);
	ballPosition[1] = ballPosition[1] + (ballVelocity[1] * dt);
	ballPosition[2] = ballPosition[2] + (ballVelocity[2] * dt);

	//X - Not implemented yet
	ballVelocity[0] = ballVelocity[0] + (0 * dt);
	//Y
	ballVelocity[1] = ballVelocity[1] + (gravity * dt);
	//Z
	//colZ = false;
	if (colZ)
	{
		ballVelocity[2] = ballVelocity[2] - (2 * dt);
	}
	else
	{
		ballVelocity[2] = ballVelocity[2] + (2 * dt);
	}
		

	/*if ((ballPosition[0]+0.1) >= raquetPosition[0] && 
		(ballPosition[1]+0.1) >= raquetPosition[1] && 
		(ballPosition[2]+0.1) == 0.8)
	{
		ballVelocity[2] *=  - (1);
	}
	else 
	{
		ballVelocity[2] *= + (1);
	}*/

	/*X Movement*/
	if ((ballVelocity[0] > 0 && ballPosition[0] >= 0.9) || 
		(ballVelocity[0] < 0 && ballPosition[0] <= -0.9)) 
	{
		ballVelocity[0] *= -1;
		/*if (sqrt(pow((ballPosition[0] - raquetPosition[0]),2) + pow((ballPosition[1] - raquetPosition[1]), 2)) < 0.15 && gameOn) {
			ballVelocity[0] *= -1;
			gameOn = true;
		}
		else {
			gameOn = false;
			return;
		}*/
	}
	/*Y Movement*/
	if (-ballPosition[1] >= (vertA[1] - (ballSize * 2))) /*  */
	{
		ballVelocity[1] *= -0.8;
		ballVelocity[2] *= -0.4;
	}
	if (ballVelocity[1] < 0 && -ballPosition[1] <= (vertB[1] - (ballSize * 2))) /* Floor reduces gravity accel. 
																			 as well as Z speed*/
	{
		ballVelocity[1] *= -0.8;
		ballVelocity[2] *= -0.8;
	}
	/*Z Movement*/
	
	if (ballVelocity[2] > 0 && (ballPosition[2] >= (vertH[2] - (ballSize * 3)))) /* Front reset gravity accel.
																				  and increase Z speed*/
	{
		if (
			((ballPosition[0] <= (raquetPosition[0] + (ballSize * 3))) && (ballPosition[0] >= (raquetPosition[0] - (ballSize * 3)))) &&
			((-ballPosition[1] <= (raquetPosition[1] + (ballSize * 3))) && (-ballPosition[1] >= (raquetPosition[1] - (ballSize * 3)))) &&
			((ballPosition[2] <= (raquetPosition[2] + (ballSize * 3))) 
				&& (ballPosition[2] >= (raquetPosition[2] - (ballSize * 3)))
				) &&
			gameOn
			)
		{
			colZ = true;
			dt = 100 / 2000.0;
			ballVelocity[1] = -ballVelocity[1] - ((10)* dt);
			ballVelocity[2] = -ballVelocity[2] - ((gravity)* dt);
			gameOn = true;
		}
		else
		{
			gameOn = false;
			return;
		}
	}
		
	if (ballVelocity[2] < 0 && (ballPosition[2] <= (vertA[2] + (ballSize * 2)))) /* Background decrease Z speed 
																				 as well as gravity accel.*/
	{
		colZ = false;
		ballVelocity[1] = ballVelocity[1] - ((5)* dt);
		ballVelocity[2] *= -0.8;
	}
	glutTimerFunc(ms, stepBall, ms);
}