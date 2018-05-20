#include "screencasts.h"

/*
* Convenience method to print out OpenGL errors to stderr
*/
void errCheck(const char* where)
{
	int err = glGetError();
	if (err) fprintf(stderr, "Error: %s [%s]\n", gluErrorString(err), where);
}