#include "screencasts.h"

/* Printing convenience */
void printv(va_list args, const char* format);
void print(const char* format, ...);
void printAt(int x, int y, const char* format, ...);
void errCheck(const char* where);

/* Window Key Methods */
void windowKey(unsigned char key, int x, int y);
void windowSpecial(int key, int x, int y);
void windowMenu(int value);
void windowMouse(int btn, int state, int x, int y);
void windowPmotion(int x, int y);

/* Main Methods */
void project(int toggleMode, double dim, int fov, int asp);
void setViewAngle(); 

void drawAxes(int toggleAxes);
void drawValues(int toggleValues, int ph, int th);
void drawScene();
void reshape(int windowWidth, int windowHeight);

void drawOrthoRoom();
void drawPerspectiveRoom();
