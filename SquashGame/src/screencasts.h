#pragma once
#ifndef SCREENCASTS
#define SCREENCASTS

/* Standard Headers */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>
//#include "stb_image.h"

/* OpenGL */

#include <GL/glew.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <cmath>
#include <cstdio>
#include <Ole2.h>
#include <NuiApi.h>
#include <NuiImageCamera.h>
#include <NuiSensor.h>

/* Includes */
#include "definition.h"
#include "print.h"
#include "error.h"
#include "shapes.h"
//#include "models.h" //pendind to code
#include "interaction.h"
#include "initialization.h"
#include "draw.h"
#include "display.h"

/* Global variables (externs) */
/* Global variables must be initializaed*/

/* Window Info*/
extern const char *windowName;
extern int windowWidth;
extern int windowHeight;

/* Toggles */
extern int toggleAxes;	/* toggle axes on and off */
extern int toggleValues;/* toggle values on and off */
extern int toggleMode;	/* projection mode */
extern int toggleLight; /* toggle light on and off */

/* Light Variables */
extern int lightPh;			/* light movement */
extern float lightY;		/* elevation of light */
extern int lightD;			/* light distance */
extern int ambient;			/* ambient intensity % */
extern int diffuse;			/* diffuse intesity % */
extern int specular;		/* specular intensity % */
extern int emission;		/* the color white */
extern int shininess;		/* shininess (power of two) */
extern float shinYvec[1];	/* shininess (value) */
extern float white3fv[3];	/* the color white wo/alpha */
extern float yellow4fv[4];	/* the color yellow w/alpha */

/* Projection - Display View */
extern double dim;	/* dimension of ortho box */
extern int th;	/* azimuth of view angle */
extern int ph;	/* elevation of view angle */
extern int fov;	/* field of view for perspective */
extern int asp;	/* aspect ratio */
extern double ecX;		/* Eye Center Position X*/
extern double ecY;		/* Eye Center Position Y*/
extern double ecZ;		/* Eye Center Position Z*/
extern GLfloat eyeP[];				/* eye camera pointer */

// Background Vertex
extern GLfloat vertA[3];
extern GLfloat vertB[3];
extern GLfloat vertC[3];
extern GLfloat vertD[3];

// Front Vertex
extern GLfloat vertE[3];
extern GLfloat vertF[3];
extern GLfloat vertG[3];
extern GLfloat vertH[3];

/* Animation */
extern GLfloat gravity;
extern int ms;
extern GLfloat ballPosition[3];
extern GLfloat ballVelocity[3];
extern GLfloat raquetPosition[3];
extern GLfloat raquetRotation[3];
extern GLfloat raquetVelocity[3];
extern bool gameOn;
extern GLfloat dt;
extern int mouseX, mouseY;
extern bool colX;
extern bool colY;
extern bool colZ;
extern GLfloat ballSize;
#endif // SCREENCASTS