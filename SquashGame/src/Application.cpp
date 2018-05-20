#include "screencasts.h"

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE| GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow(windowName);

	glutDisplayFunc(display);
	glutReshapeFunc(displayReshape);
	glutKeyboardFunc(windowKey);
	glutSpecialFunc(windowSpecial);

	glutCreateMenu(windowMenu);
	glutAddMenuEntry("Toggle Axes [a]", 'a');
	glutAddMenuEntry("Toggle Values [v]", 'v');
	glutAddMenuEntry("Toggle Mode [m]", 'm');
	glutAttachMenu(GLUT_RIGHT_BUTTON);
		
	glutMouseFunc(windowMouse);
	glutPassiveMotionFunc(windowPmotion);

	glutMainLoop();
	return 0;
}
