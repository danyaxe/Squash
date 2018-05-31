#pragma once
#ifndef SCREENCASTS
#define SCREENCASTS
#define USEGLEW
#define GL_GLEXT_PROTOTYPES 1

/* OpenGL */
#include <GLFW\glew.h>
#include <GLFW\glfw3.h>

/* Standard Headers */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <iostream>

#include "stb_image.h"



#ifdef __APPLE__
#include <GLUT/glut.h>
#else 
#include <GLFW\glut.h>
#endif // __APPLE__

/* Includes */
#include "definition.h"
#include "print.h"
#include "error.h"
#include "shapes.h"
#include "textures.h"
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

/* Room Vertex */
extern GLfloat vertA[3];
extern GLfloat vertB[3];
extern GLfloat vertC[3];
extern GLfloat vertD[3];
extern GLfloat vertE[3];
extern GLfloat vertF[3];
extern GLfloat vertG[3];
extern GLfloat vertH[3];

/* Animation */
extern int ms; 
extern int mouseX; /* mouse coordinates */
extern int mouseY; /* mouse coordinates */
extern GLfloat dt; /* derivative of time */
extern GLfloat gravity;
extern GLfloat ballSize; 
extern GLfloat ballPosition[3];
extern GLfloat ballVelocity[3];
extern GLfloat raquetPosition[3];
//extern GLfloat raquetRotation[3]; /* improvement */
//extern GLfloat raquetVelocity[3]; /* improvement */
extern bool gameOn; /* End game flag */
extern bool colZ; /* Ball speed after collision in Z */

/* Textures */
extern unsigned int textures[5]; /* holds our textures */
extern int currentTexture;

#endif // SCREENCASTS