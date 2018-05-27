#include "screencasts.h"
#include <windows.h>

/* WINDOW */
const char *windowName = "Squash";
int windowWidth = DEF_WINDOW_WIDTH;
int windowHeight = DEF_WINDOW_HEIGHT;

/* TOGGLE */
int toggleAxes = DEF_AXES; /* toggle axes on and off */
int toggleValues = DEF_PARAMS; /* toggle values on and off */
int toggleMode = DEF_MODE; /* projection mode */
int toggleLight = DEF_LIGHT; /* light turn on/off */

/* LIGHTING*/
int lightPh = DEF_LIGHTPH;			/* light movement */
float lightY = DEF_LIGHTY;			/* elevation of light */
int lightD = DEF_LIGHTD;			/* light distance */
int ambient = DEF_AMBIENT;			/* ambient intensity % */
int diffuse = DEF_DIFFUSE;			/* diffuse intesity % */
int specular = DEF_SPECULAR;		/* specular intensity % */
int emission = DEF_EMISSION;		/* the color white */
int shininess = DEF_SNININESS;		/* shininess (power of two) */
float shinYvec[1] = { 0.0 };	/* shiness Y Vector */

/* PROJECTION */
double dim = DEF_DIM; /*dimension of Ortho box*/
int th = DEF_TH;	/* azimuth of view angle */
int ph = DEF_PH;	/* elevation of view angle */
int fov = DEF_FOV;	/* field of view for perspective */
int asp = DEF_ASP;	/* aspect ratio */
double ecX = DEF_ECX;		/* Eye Center Position X*/
double ecY = DEF_ECY;		/* Eye Center Position Y*/
double ecZ = DEF_ECZ;		/* Eye Center Position Z*/
GLfloat eyeP[] = { DEF_ECX,DEF_ECY,DEF_ECZ }; /* eye camera pointer */

/* COLORS*/
float white3fv[3] = { 1.0,1.0,1.0 };
float yellow4fv[4] = { 1.0,1.0,1.0,1.0 };

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

/*Animation*/
GLfloat gravity = 9.81;
int ms = 100;
GLfloat ballPosition[3] = { 0.0, 0.0, 0.0 };
GLfloat ballVelocity[3] = { 0.0, 0.0, 0.0 };
GLfloat raquetPosition[3] = { 0.0, 0.0, 0.0 };
GLfloat raquetRotation[3] = { 0.0, 0.0, -45.0 };
GLfloat raquetVelocity[3] = { 0.0, 0.0, 0.0 };


/*Game is going on*/
bool gameOn = true;
int mouseX, mouseY = 0;