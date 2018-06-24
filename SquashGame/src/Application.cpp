#include "screencasts.h"

int main(int argc, char *argv[])
{
	name = "";
	cout << "Please enter your name: ";
	cin >> name;
	system("cls");

	int validName = name.length() - 1;

	if (validName >= 0)
	{
		initialize();
		addUser(name);

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowSize(windowWidth, windowHeight);
		glutCreateWindow(windowName);

		glutDisplayFunc(display);
		glutReshapeFunc(displayReshape);
		glutKeyboardFunc(windowKey);
		glutSpecialFunc(windowSpecial);
		glutMouseFunc(windowMouse);
		glutPassiveMotionFunc(mouseCallback);

		glutCreateMenu(windowMenu);
		glutAddMenuEntry("Toggle Axes [1]", '1');
		glutAddMenuEntry("Toggle Values [2]", '2');
		glutAddMenuEntry("Toggle Mode [3]", '3');
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		glutTimerFunc(ms, stepBall, ms); /* Timer for animation */

		initializeTextures();

		redisplayAll();
		glutMainLoop();

		return 0;
	}
}

void show(HWND hwnd)
{
	WINDOWPLACEMENT place = { sizeof(WINDOWPLACEMENT) };
	GetWindowPlacement(hwnd, &place);
	switch (place.showCmd)
	{
	case SW_SHOWMAXIMIZED:
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);
		break;
	case SW_SHOWMINIMIZED:
		ShowWindow(hwnd, SW_SHOWMINIMIZED);
		break;
	case SW_RESTORE:
		ShowWindow(hwnd, SW_RESTORE);
		break;
	default:
		ShowWindow(hwnd, SW_NORMAL);
		break;
	}
	SetWindowPos(0, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
	SetForegroundWindow(hwnd);
}
