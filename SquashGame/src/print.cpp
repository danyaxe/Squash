#include "screencasts.h"
#include <GL/glext.h>

#define LEN 8192

/*GLOBAL*/


void printv(va_list args, const char* format)
{
	char buf[LEN];
	char* ch = buf;
	vsnprintf(buf, LEN, format, args);
	while (*ch)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *ch++);
}

void print(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	printv(args, format);
	va_end(args);
}

void printAt(int x, int y, const char* format, ...)
{
	va_list args;
	//glWindowPos2i(x, y);
	va_start(args, format);
	printv(args, format);
	va_end(args);
}