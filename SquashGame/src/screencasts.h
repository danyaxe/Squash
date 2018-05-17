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

#include "prototypes.h"

#endif // SCREENCASTS