#include "screencasts.h"

/*
* Convenience method to print out OpenGL errors to stderr
*/
void errCheck(const char* where)
{
	int err = glGetError();
	if (err) fprintf(stderr, "Error: %s [%s]\n", gluErrorString(err), where);
}

/*
* Convenience method to print out OpenGL fatal errors to stderr
*/
void fatal(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	exit(1);
}