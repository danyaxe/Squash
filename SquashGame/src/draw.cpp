#include "screencasts.h"

GLuint vboId;
GLuint cboId;
INuiSensor* sensor;

// Stores the coordinates of each joint
Vector4 skeletonPosition[NUI_SKELETON_POSITION_COUNT];

bool initKinect() {
	// Get a working kinect sensor
	int numSensors;
	if (NuiGetSensorCount(&numSensors) < 0 || numSensors < 1) return false;
	if (NuiCreateSensorByIndex(0, &sensor) < 0) return false;

	// Initialize sensor
	sensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_SKELETON);
	sensor->NuiSkeletonTrackingEnable(NULL, 0); // NUI_SKELETON_TRACKING_FLAG_ENABLE_SEATED_SUPPORT for only upper body
	return sensor;
}

void getSkeletalData() {
	NUI_SKELETON_FRAME skeletonFrame = { 0 };
	if (sensor->NuiSkeletonGetNextFrame(0, &skeletonFrame) >= 0) {
		sensor->NuiTransformSmooth(&skeletonFrame, NULL);
		// Loop over all sensed skeletons
		for (int z = 0; z < NUI_SKELETON_COUNT; ++z) {
			const NUI_SKELETON_DATA& skeleton = skeletonFrame.SkeletonData[z];
			// Check the state of the skeleton
			if (skeleton.eTrackingState == NUI_SKELETON_TRACKED) {
				// Copy the joint positions into our array
				for (int i = 0; i < NUI_SKELETON_POSITION_COUNT; ++i) {
					skeletonPosition[i] = skeleton.SkeletonPositions[i];
					if (skeleton.eSkeletonPositionTrackingState[i] == NUI_SKELETON_POSITION_NOT_TRACKED) {
						skeletonPosition[i].w = 0;
					}
				}
				return; // Only take the data for one skeleton
			}
		}
	}
}

/*
*	Draw Scene
*/
void drawScene()
{
	getSkeletalData();
	drawAxes();
	drawValues();
	const Vector4& rh = skeletonPosition[NUI_SKELETON_POSITION_HAND_RIGHT];

	if (toggleMode)
	{
		drawLight();
		drawPerspectiveRoom();

		//Squash Ball
		glPushMatrix();
			glTranslated(ballPosition[0], -ballPosition[1], ballPosition[2]);
			glColor3f(1.0, 1.0, 1.0);
			glutSolidSphere(ballSize, 30, 30);
		glPopMatrix();
		
		// Raquet 
		glPushMatrix();
		if (rh.w > 0) {
			glTranslated(rh.x/1.5, rh.y/1.5, rh.z/1.5);
		}
		glScaled(.10, .10, .10);
		glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			glColor3f(0.0, 1.0, 1.0);	// Turquoise
			glVertex3fv(vertE); //P1
			glVertex3fv(vertF); //P2
			glVertex3fv(vertH); //P3
			glVertex3fv(vertG); //P4
		glEnd();
		glPopMatrix();
		
		/*cilinder(raquetPosition[0], raquetPosition[1], raquetPosition[2], .05, .25, raquetRotation[0], raquetRotation[1], raquetRotation[2], DEF_D);*/
	}
	else
	{
		drawLight();
		drawOrthoRoom();
		
		//Squash Ball
		glPushMatrix();
			glTranslated(ballPosition[0], -ballPosition[1], ballPosition[2]);
			glColor3f(1.0, 1.0, 1.0);
			glutSolidSphere(.05, 30, 30);
		glPopMatrix();

		// Raquet 
		glPushMatrix();
		if (rh.w > 0) {
			glTranslated(rh.x, rh.y, rh.z);
		}
		glScaled(.05, .05, .05);
		glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			glColor3f(0.0, 1.0, 1.0);	// Turquoise
			glVertex3fv(vertE); //P1
			glVertex3fv(vertF); //P2
			glVertex3fv(vertH); //P3
			glVertex3fv(vertG); //P4
		glEnd();
		glPopMatrix();
	}
}

/*
*	Draw Light
*/
void drawLight()
{
	/* Light Switch*/
	if (toggleLight)
	{
		/*Translate intensity to color vectors*/
		float Ambient[] = { 0.01*ambient, 0.01*ambient,0.01*ambient,1.0 };
		float Diffuse[] = { 0.01*diffuse, 0.01*diffuse,0.01*diffuse,1.0 };
		float Specular[] = { 0.01*specular, 0.01*specular,0.01*specular,1.0 };

		/* Light Position */
		float Position[] = { lightD*Cos(lightPh),lightY,lightD*(Sin(lightPh)),1.0 };

		/* Draw light position as sphere */
		glColor3fv(white3fv);
		glDisable(GL_LIGHTING);
		
		/* OpenGL should normalize vectors */
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);

		/* glColor sets ambient and diffuse color materials */
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHT0);

		/* Set ambient, diffuse, specular components and position of light 0 */
		glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
		glLightfv(GL_LIGHT0, GL_POSITION, Position);		
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
}


/*
*	Draw Axes
*/
void drawAxes()
{
	if (toggleAxes) {

		/* Lenght of Axes */
		GLfloat len = 5.0;
		glDisable(GL_LIGHTING);
		glColor3fv(white3fv);

		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(len, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, len, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, len);
		glEnd();

		/* Label Axes */
		glRasterPos3d(len, 0, 0);
		print("X");
		glRasterPos3d(0, len, 0);
		print("Y");
		glRasterPos3d(0, 0, len);
		print("Z");
	}
	else
	{
		glEnable(GL_LIGHTING);
	}
	errCheck("error in draw axes");
}

/*
*	Draw Values
*/
void drawValues()
{
	if (toggleValues) {
		glColor3f(0.8, 0.8, 0.8);
		glRasterPos2d(50, 50);
		print("View Angle (th,ph) =(%d, %d)", th, ph);
		print("Projection mode= (%s)", toggleMode ? "Perspective" : "Orthogonal");
	}
	errCheck("error in draw values");
}

/*
*	Draw Ortho Room
*/
void drawOrthoRoom()
{
	// NO CEILING NO FRONT FACES
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	// Background Room
	glNormal3f(0, 0, 1);
	glColor3f(1.0, 1.0, 0.0);	// Yellow 
	glVertex3fv(vertA); //P1
	glVertex3fv(vertB); //P2
	glVertex3fv(vertD); //P3
	glVertex3fv(vertC); //P4
						// Right room side
	glNormal3f(-1, 0, 0);
	glColor3f(1.0, 0.0, 0.0);	// Red
	glVertex3fv(vertA); //P1
	glVertex3fv(vertB); //P2
	glVertex3fv(vertF); //P3
	glVertex3fv(vertE); //P4
						// Left room side
	glNormal3f(1, 0, 0);
	glColor3f(0.0, 0.0, 1.0);	// Blue
	glVertex3fv(vertC); //P1
	glVertex3fv(vertD); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertG); //P4
						// Floor
	glNormal3f(0, 1, 0); 
	glColor3f(1.0, 0.0, 1.0);	// Pink
	glVertex3fv(vertB); //P1
	glVertex3fv(vertD); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertF); //P4
						
						/* Front Face */
	//glNormal3f(0, 0, -1);
	//glColor3f(0.0, 1.0, 1.0);	// Turquoise
	//glVertex3fv(vertE); //P1
	//glVertex3fv(vertF); //P2
	//glVertex3fv(vertH); //P3
	//glVertex3fv(vertG); //P4

						/* Ceiling */
	//glColor3f(0.0, 1.0, 0.0);	// Green
	//glVertex3fv(vertA); //P1
	//glVertex3fv(vertC); //P2
	//glVertex3fv(vertG); //P3
	//glVertex3fv(vertE); //P4

	glEnd();
	glPopMatrix();
}

/*
*	Draw Perspective Room
*/
void drawPerspectiveRoom()
{
	// NO FRONT FACE
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	// Background Room
	glNormal3f(0, 0, 1);
	glColor3f(1.0, 1.0, 0.0);	// Yellow 
	glVertex3fv(vertA); //P1
	glVertex3fv(vertB); //P2
	glVertex3fv(vertD); //P3
	glVertex3fv(vertC); //P4
						// Right room side
	glNormal3f(-1, 0, 0);
	glColor3f(1.0, 0.0, 0.0);	// Red
	glVertex3fv(vertA); //P1
	glVertex3fv(vertB); //P2
	glVertex3fv(vertF); //P3
	glVertex3fv(vertE); //P4
						// Ceiling
	glNormal3f(0, -1, 0);
	glColor3f(0.0, 1.0, 0.0);	// Green
	glVertex3fv(vertA); //P1
	glVertex3fv(vertC); //P2
	glVertex3fv(vertG); //P3
	glVertex3fv(vertE); //P4
						// Left room side
	glNormal3f(1, 0, 0);
	glColor3f(0.0, 0.0, 1.0);	// Blue
	glVertex3fv(vertC); //P1
	glVertex3fv(vertD); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertG); //P4
						// Floor
	glNormal3f(0, 1, 0);
	glColor3f(1.0, 0.0, 1.0);	// Pink
	glVertex3fv(vertB); //P1
	glVertex3fv(vertD); //P2
	glVertex3fv(vertH); //P3
	glVertex3fv(vertF); //P4

						/* Front Face */
	//glNormal3f(0, 0, -1); 
	//glColor3f(0.0, 1.0, 1.0);	// Turquoise
	//glVertex3fv(vertE); //P1
	//glVertex3fv(vertF); //P2
	//glVertex3fv(vertH); //P3
	//glVertex3fv(vertG); //P4
	glEnd();
	glPopMatrix();
}
