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

/* OpenGL */
#ifdef USEGLEW
#include <GL.glew.h>
#endif // USEGLEW
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else 
#include <GL/glut.h>
#endif // __APPLE__

/* Includes */
#include "definition.h"
#include "print.h"
#include "error.h"
//#include "shapes.h" //pendind to code
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

/* Display View */
extern double dim;	/* dimension of ortho box */

extern int th;	/* azimuth of view angle */
extern int ph;	/* elevation of view angle */

extern int fov;	/* field of view for perspective */
extern int asp;	/* aspect ratio */

extern GLfloat eyeP[]; /* eye camera pointer */

/* Objects */
extern int objId;		/* object to draw */
extern int objSlices; /* slices lines of longitude */
extern int objStacks; /* stacks lines of latitude */

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

#endif // SCREENCASTS