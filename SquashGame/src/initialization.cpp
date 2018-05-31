#include "screencasts.h"

void initializeGlobal()
{
	/* WINDOW */
	const char *windowName = "Squash";
	windowWidth = DEF_WINDOW_WIDTH;
	windowHeight = DEF_WINDOW_HEIGHT;

	/* TOGGLE */
	toggleAxes = DEF_AXES; /* toggle axes on and off */
	toggleValues = DEF_PARAMS; /* toggle values on and off */
	toggleMode = DEF_MODE; /* projection mode */
	toggleLight = DEF_LIGHT; /* light turn on/off */

	/* LIGHTING*/
	lightPh = DEF_LIGHTPH;			/* light movement */
	lightY = DEF_LIGHTY;			/* elevation of light */
	lightD = DEF_LIGHTD;			/* light distance */
	ambient = DEF_AMBIENT;			/* ambient intensity % */
	diffuse = DEF_DIFFUSE;			/* diffuse intesity % */
	specular = DEF_SPECULAR;		/* specular intensity % */
	emission = DEF_EMISSION;		/* the color white */
	shininess = DEF_SNININESS;		/* shininess (power of two) */
	float shinYvec[1] = { 0.0 };	/* shiness Y Vector */

	/* PROJECTION */
	dim = DEF_DIM; /*dimension of Ortho box*/
	th = DEF_TH;	/* azimuth of view angle */
	ph = DEF_PH;	/* elevation of view angle */
	fov = DEF_FOV;	/* field of view for perspective */
	asp = DEF_ASP;	/* aspect ratio */
	ecX = DEF_ECX;	/* Eye X Position */
	ecY = DEF_ECY;	/* Eye Y Position */
	ecZ = DEF_ECZ;	/* Eye Z Position */
	GLfloat eyeP[] = { DEF_ECX,DEF_ECY,DEF_ECZ }; /* eye camera pointer */

	/* COLORS*/
	float white3fv[3] = { 1.0,1.0,1.0 };
	float yellow4fv[4] = { 1.0,1.0,1.0,1.0 };

	/* Room Vertex */
	GLfloat vertA[3] = { 1.0, 1.0, -1.0 };
	GLfloat vertB[3] = { 1.0,-1.0, -1.0 };
	GLfloat vertC[3] = { -1.0, 1.0, -1.0 };
	GLfloat vertD[3] = { -1.0,-1.0, -1.0 };
	GLfloat vertE[3] = { 1.0, 1.0, 1.0 };
	GLfloat vertF[3] = { 1.0,-1.0, 1.0 };
	GLfloat vertG[3] = { -1.0, 1.0, 1.0 };
	GLfloat vertH[3] = { -1.0,-1.0, 1.0 };

	/*Animation*/
	int ms = 100; 
	GLfloat gravity = 9.81;
	GLfloat ballPosition[3] = { 0.0, 0.0, 0.0 };
	GLfloat ballVelocity[3] = { 0.0, 0.0, 5.0 };
	GLfloat raquetPosition[3] = { 0.0, 0.0, 2.0 };
	//GLfloat raquetRotation[3] = { 15.0, 15.0, 0.0 };
	//GLfloat raquetVelocity[3] = { 0.0, 0.0, 0.0 };

	/* Game is going on */
	mouseX = 0;
	mouseY = 0;
	gameOn = true;
	colZ = false; 
	ballSize = .05; 
	dt = ms / 10000.0;
	
	/* Textures */
	currentTexture = T_DEF;
}


void initializeTextures()
{
	/*
	* T_DEF 0
	* T_FLOOR 1
	* T_WALL 2
	* T_CEIL 3
	* T_BALL 4
	*/

	textures[T_DEF] = loadBMP("C:/Users/alexd/Documents/Squash-master/SquashGame/src/default.png");
	textures[T_FLOOR] = loadBMP("C:/Users/alexd/Documents/Squash-master/SquashGame/src/floor.png");
	textures[T_WALL] = loadBMP("C:/Users/alexd/Documents/Squash-master/SquashGame/src/wall.png");
	textures[T_CEIL] = loadBMP("C:/Users/alexd/Documents/Squash-master/SquashGame/src/ceil.png");
	textures[T_BALL] = loadBMP("C:/Users/alexd/Documents/Squash-master/SquashGame/src/ball.png");
}
