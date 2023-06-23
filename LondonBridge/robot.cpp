
#include <Windows.h>
#include <Windowsx.h>
#include <gl/GL.h>
#include <math.h>
#include <gl/GLU.h>
#include <iostream>
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "London Bridge"                  // Can change the window name
#pragma region define
// VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

//VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39
#define PI 3.1415927
#pragma endregion
#pragma region void


GLuint loadTexture(LPCSTR filename);
//Lighting Material
void lightGreyMaterial();
void greyMaterial();
void blackMaterial();
void whiteMaterial();
void yellowMaterial();
void redMaterial();
void orangeMaterial();
void blueMaterial();
void lighting();
void reset();
#pragma endregion
#pragma region Set Variable
double rotateDegree = 0;
int axis[3] = { 0,0,0 };
//======================================			VIEW
// Variable for Viewing
//======================================
//Variable for rotating using mouse
float xRotated = 0.0f, yRotated = 0.0f, zRotated = 0.0f;

float zoomLevel = -1.0f, openAngle = 0, open = false;
//======================================			SHAPE
// Variable to draw Sphere
float radius = 0, slices = 0, stacks = 0;
#pragma region DRAW CURVE CYLINDER VARIABLE
//variable for curve cylinder
GLfloat w0, w1, ang0, ang1, angle, x, y, xb, yb, zb;
int i, j;
int slice = 4;
GLfloat bend_radius = 1.0f;

GLfloat bend_angle, bend_ang0, bend_ang1;
#pragma endregion
//======================================			BODY


boolean rotateLeft = false;
boolean rotateRight = false;
boolean rotateUp = false;
boolean rotateDown = false;
boolean rUp = false;
boolean punch = false;
#pragma endregion
#pragma region LEG PART VARIABLE
// leg
int chooseInteraction = 0;
// Variable for full leg --- Walking
float rightkneeAngle = 180.0f;
float leftkneeAngle = 180.0f;
float leftLegAngle = 180.0f;
float rightLegAngle = 180.0f;

bool leftFrontMax = false, rightFrontMax = false;
bool firstWalk = true, leftFrontWalked = false, rightFrontWalked = true;


float xPosition = 0.0f, yPosition = 0.0f, zPosition = 3.5f;
float zAfterMoved = 0.0;
float leftLegAxis[3][3] = { {1.0f,0.0f,0.0f},{ 1.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f } };
float rightLegAxis[3][3] = { { 1.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f },{ 1.0f,0.0f,0.0f } };

// Variable for Jumping
bool jumpMax = false;
bool firstJump = true, frontJump = false;
bool squatBeforeJump = false;
bool jump = false;
#pragma endregion
//======================================			WEAPON
#pragma region weapon
//weapon
bool laser = false;
float size = 0.0f;
float shootBall = 0.0f;
bool moveBackBall = false;

//weaponGun
boolean bulletShoot = false;
boolean weaponGunFire = false;
float weaponGunX = 0.0f;
float weaponGunSpin = 0.0f;
#pragma endregion
//======================================			TEXTURE
#pragma region TEXTURE 
//Texture
GLuint textureArr[5];
GLuint armorTexture, metalTexture, glassTexture, galaxyTexture, ironManCircleTexture, flameTexture;
BITMAP BMP;
HBITMAP hBMP = NULL;
LPCSTR textureArray[2][4] = {
	{"textures/galaxy.bmp", "textures/dragon.bmp", "textures/red_texture.bmp", "textures/ironManCircle.bmp"},
	{"textures/galaxy_texture3.bmp", "textures/lava_texture.bmp", "textures/blue_texture2.bmp", "textures/ironManCircle.bmp"}
};
int textureOption = 0;
bool textureOn = false;
GLuint texture;
#pragma endregion
//======================================			LIGHTING
#pragma region LIGHTING
//lighting
bool lightingOn = false;
bool isDiffuse = true;
bool isAmbient = true;
bool isSpecular = true;
float positionX = -2.0f, positionY = 5.0f, positionZ = -0.5f;

float red[4] = { 1, 0, 0, 1 };
float blue[4] = { 0, 1, 0.792, 1 };
float white[4] = { 1, 1, 1, 1 };
float darkGrey[4] = { 0.1, 0.1, 0.1, 1 };
float lightGrey[4] = { 0.7, 0.7, 0.7, 1 };
float yellow[4] = { 1, 1, 0, 1 };
float grey[4] = { 0.6, 0.6, 0.6, 1 };
float orange[4] = { 1, 0.5, 0, 1 };
float purple[4] = { 0.635,0.404,0.812,1 };

GLfloat ambient[4] = { 0.635,0.404,0.812,1 };	//purple
GLfloat diffuse[4] = { 1,1,1,1 };	//white
GLfloat specular[4] = { 1,1,1, 1 };	//white
GLfloat lightClose[4] = { 0,0,0,0 };
#pragma endregion

//perspective
bool isPerspective = true;
bool isOrtho = false;
float P_NEAR = 0.5, P_FAR = 21.0;
float O_NEAR = -1.0, O_FAR = 11.0;

float pTx = 0, pTy = 0, ptSpeed = 0.1; // Translate for projection
float prSpeed = 2.0; // Rotate Y for projection
float ry = 0; // Rotate Y for Ortho (NO ROTATE Y FOR PERSPECTIVE!!!) and Model View
float mTx = 0, mTy = 0, mTz = 0, mtSpeed = 1; // Translate for modelview
float mRx = 0, mRy = 0, mRz = 0;

//background
float backgroundDegree = 0;
bool onBackground = true;
#pragma endregion
GLuint loadTexture(LPCSTR filename) {
	GLuint texture = 0;
	glColor3f(1.0f, 1.0f, 1.0f);

	//Step 3 : Initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	//Step 4 : Assign texture to polygon
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//take from step 5
	DeleteObject(hBMP);
	return texture;
}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		switch (wParam) {
		case MK_LBUTTON:
			POINT pt;
			pt.x = GET_X_LPARAM(lParam);
			pt.y = GET_Y_LPARAM(lParam);
			ScreenToClient(hWnd, &pt);
			zRotated = pt.x;
			xRotated = pt.y;
			break;
		}
		break;
	case WM_MOUSEWHEEL:
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) { // zoom in (scroll forward)
			if (zoomLevel < 3.0f)
				zoomLevel += GET_WHEEL_DELTA_WPARAM(wParam) / 120.0f;
			break;
		}
		else {// zoom out (scroll backward)
			if (zoomLevel > -7.0f)
				zoomLevel += GET_WHEEL_DELTA_WPARAM(wParam) / 120.0f;
			break;
		}

	case WM_KEYDOWN:
	{
		switch (wParam) {
#pragma region General Utility							  
		case VK_ESCAPE:	PostQuitMessage(0);	break;
		case VK_I: // zoom in
			if (zoomLevel < 3.0f) {
				zoomLevel += 1.0f;
			}

			break;
		case VK_O: //zoom out
			if (zoomLevel > -7.0f) {
				zoomLevel -= 1.0f;
			}
			break;
			
		case VK_F:
			open = !open;
			break;
			
		case VK_SPACE: {
			reset();
		}				break;

#pragma endregion				 
#pragma region RotatetheView							
		case VK_UP: {
			xRotated -= 5.0f;
		}				break;
		case VK_DOWN: {
			xRotated += 5.0f;
		}				break;
		case VK_LEFT: {
			yRotated += 5.0f;
		}				break;
		case VK_RIGHT: {
			yRotated -= 5.0f;
		}			break;

#pragma endregion		 



#pragma region Texture control
		case VK_T: {
			textureOn = !textureOn;
		}				break;
		case VK_G: {
			if (textureOn) {
				textureOption += 1;

				if (textureOption == 3) {
					textureOption = 0;
				}
			}
		}				break;
#pragma endregion	
#pragma region Lighting Control 
			// lighting on and off
		case VK_U: {
			lightingOn = !lightingOn;
		}				break;
			// lighting position
		case VK_F1: {
			positionX -= 0.5f;
		}			break;
		case VK_F2: {
			positionX += 0.5f;
		}			break;
		case VK_F3: {
			positionY -= 0.5f;
		}			break;
		case VK_F4: {
			positionY += 0.5f;
		}			break;
		case VK_F5: {
			positionZ -= 0.5f;
		}			break;
		case VK_F6: {
			positionZ += 0.5f;
		}			break;
			//Diffuse, Ambient, Specular, Perspective, Onbackground
		case VK_NUMPAD7: {
			isDiffuse = !isDiffuse;
		}			break;
		case VK_NUMPAD8: {
			isAmbient = !isAmbient;
		}			break;
		case VK_NUMPAD9: {
			isSpecular = !isSpecular;
		}			break;
		case VK_Y: {
			isPerspective = !isPerspective;
		}			break;
		case VK_V: {
			onBackground = !onBackground;
		}			break;
#pragma endregion
#pragma region Camera
		case VK_D: {
			pTx += ptSpeed;
		}
					   break;
		case VK_A: {
			pTx -= ptSpeed;
		}
					   break;
		case VK_W: {
			pTy += ptSpeed;
		}
					   break;
		case VK_S: {
			pTy -= ptSpeed;
		}
					   break;
		case VK_Q: {
			ry += prSpeed;;
		}
					   break;
		case VK_E: {
			ry -= prSpeed;
		}
					   break;
		}
	default:
		break;
	}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}

}
//--------------------------------------------------------------------

void drawSphere(float radius, float slices, float stacks) {
	GLUquadricObj* sphere = gluNewQuadric();
	glPushMatrix();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, true);
	gluSphere(sphere, radius, slices, stacks);
	gluDeleteQuadric(sphere);
	glPopMatrix();
}
void drawCone(float baseRadius, float topRadius, float height, float slices, float stacks) {
	glPushMatrix();
	{
		GLUquadricObj* cone = gluNewQuadric();
		//Inside
		blackMaterial();
		gluQuadricDrawStyle(cone, GLU_FILL);
		gluQuadricTexture(cone, true);
		gluCylinder(cone, baseRadius, topRadius, height, slices, stacks);
		gluDeleteQuadric(cone);
	}
	glPopMatrix();
}
void drawCylinderWithSlices(double baseR, double topR, double height, double slices, double stacks) {
	GLUquadric* cyl = NULL;
	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_FILL);
	gluQuadricTexture(cyl, true);
	gluCylinder(cyl, baseR, topR, height, slices, stacks);
	gluDeleteQuadric(cyl);
}
void drawCylinder(double baseR, double topR, double height) {
	GLUquadric* cyl = NULL;
	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_FILL);
	gluQuadricTexture(cyl, true);
	gluCylinder(cyl, baseR, topR, height, 20, 20);
	gluDeleteQuadric(cyl);
}
void drawQuadsWithTex(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4) {
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x1, y1, z1);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x2, y2, z2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x3, y3, z3);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x4, y4, z4);
	}
	glEnd();
}
void drawTriWithTex(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
	glBegin(GL_TRIANGLES);
	{
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x1, y1, z1);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x2, y2, z2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x3, y3, z3);
	}
	glEnd();
}
void drawCurveCylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B)
{
	bend_angle = bend_radius * height;
	bend_ang0 = -bend_angle / 0.30f;
	bend_ang1 = bend_angle / 0.30f;
	for (i = 0; i < slice; i++)
	{
		w0 = (float)i / (float)slice;
		w1 = (float)(i + 1) / (float)slice;

		ang0 = bend_ang0 + (bend_ang1 - bend_ang0) * w0;
		ang1 = bend_ang0 + (bend_ang1 - bend_ang0) * w1;

		glPushMatrix();
		glTranslatef(-0.85, 0.15, 0.1);
		glRotatef(120, 1, 1, 1);
		lightGreyMaterial();
		glColor3f(0.0, 1, 0.792);
		if (textureOn) {
			armorTexture = loadTexture("textures/tinyrobot_texture.bmp");
		}
		glBegin(GL_QUAD_STRIP);

		for (j = 0; j <= 360; ++j)
		{
			angle = PI * (float)j * PI / 180.0f;
			x = radius * cos(angle) + bend_radius;
			y = radius * sin(angle);

			xb = sin(ang0) * x;
			yb = y;
			zb = cos(ang0) * x;
			glTexCoord2f(0.0f, 0.0f); glVertex3f(xb, yb, zb);

			xb = sin(ang1) * x;
			yb = y;
			zb = cos(ang1) * x;
			glTexCoord2f(0.0f, 0.1f); glVertex3f(xb, yb, zb);
		}
		glEnd();
		glDeleteTextures(1, &armorTexture);
		glPopMatrix();
	}
}


#pragma endregion
void background() {
	yellowMaterial();
	glColor3f(0.15, 0.15, 0.15);
	if (textureOn) {
		armorTexture = loadTexture("textures/galaxy_background1.bmp");
	}

	glPushMatrix();
	{
		glRotatef(backgroundDegree, 0, 1, 0);
		glPushMatrix();
		{
			glTranslatef(0, 25.0f, 0);

			glRotatef(90, 1, 0, 0);
			drawCylinder(10, 10, 50);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glDeleteTextures(1, &armorTexture);
	glDisable(GL_TEXTURE_2D);


}
#pragma region LIGHTING MATERIAL
//Lighting Material
void greyMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, grey);

}
void lightGreyMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, lightGrey);
}
void redMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, red);
}
void blackMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkGrey);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, darkGrey);
}
void yellowMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yellow);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, yellow);
}
void whiteMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
}
void orangeMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, orange);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, orange);
}
void purpleMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, purple);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, purple);
}
void blueMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blue);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blue);
}
void cylinder(float bot, float top, float height, int h, int v, LPCSTR filename) {
	GLUquadricObj* cylinder = gluNewQuadric();
	gluQuadricTexture(cylinder, true);
	texture = loadTexture(filename);

	gluQuadricDrawStyle(cylinder, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluCylinder(cylinder, bot, top, height, h, v);		//draw cylinder
	gluDeleteQuadric(cylinder);
	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);
}
#pragma endregion
void cube(float length, float height, float width) {
	glBegin(GL_QUADS);

	// Face 1 / Bottom
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, width);
	glTexCoord2f(1, 1);
	glVertex3f(length, 0.0f, width);
	glTexCoord2f(1, 0);
	glVertex3f(length, 0.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 / Left
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, height, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, height, width);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, width);

	// Face 3 / Front
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, height, 0);
	glTexCoord2f(1, 0);
	glVertex3f(length, height, 0);
	glTexCoord2f(0, 0);
	glVertex3f(length, 0.0f, 0);

	// Face 4 / Right
	glTexCoord2f(0, 1);
	glVertex3f(length, 0.0f, 0);
	glTexCoord2f(1, 1);
	glVertex3f(length, height, 0);
	glTexCoord2f(1, 0);
	glVertex3f(length, height, width);
	glTexCoord2f(0, 0);
	glVertex3f(length, 0.0f, width);

	// Face 5 / Back
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.0f, width);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, height, width);
	glTexCoord2f(1, 0);
	glVertex3f(length, height, width);
	glTexCoord2f(0, 0);
	glVertex3f(length, 0, width);

	// Face 6 / Top
	glTexCoord2f(0, 1);
	glVertex3f(0, height, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(length, height, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(length, height, width);
	glTexCoord2f(0, 0);
	glVertex3f(0, height, width);
	glEnd();

}
void cubeLine(float length, float height, float width) {
	glBegin(GL_LINE_LOOP);
	// Face 1 / Bottom
	glVertex3f(0.0f, 0.0f, width);
	glVertex3f(length, 0.0f, width);
	glVertex3f(length, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 / Left
	glVertex3f(0, 0.0f, 0.0f);
	glVertex3f(0.0f, height, 0.0f);
	glVertex3f(0.0f, height, width);
	glVertex3f(0, 0, width);

	// Face 3 / Front
	glVertex3f(0.0f, 0.0f, 0);
	glVertex3f(0.0f, height, 0);
	glVertex3f(length, height, 0);
	glVertex3f(length, 0.0f, 0);

	// Face 4 / Right
	glVertex3f(length, 0.0f, 0);
	glVertex3f(length, height, 0);
	glVertex3f(length, height, width);
	glVertex3f(length, 0.0f, width);

	// Face 5 / Back
	glVertex3f(0, 0.0f, width);
	glVertex3f(0.0f, height, width);
	glVertex3f(length, height, width);
	glVertex3f(length, 0, width);

	// Face 6 / Top
	glVertex3f(0, height, 0.0f);
	glVertex3f(length, height, 0.0f);
	glVertex3f(length, height, width);
	glVertex3f(0, height, width);
	glEnd();
}
void reset() {
	xRotated = 0.0f;
	yRotated = 0.0f;
	zRotated = 0.0f;
	zoomLevel = -3.0f;
	zPosition = 3.5f;
	yPosition = 0;

	//light
	positionX = -2.0f;
	positionY = 5.0f;
	positionZ = -0.5f;
	//Camera
	pTx = 0;
	pTy = 0;
	ry = 0;
}
void lighting() {


	if (lightingOn) {
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_LIGHTING);
	}



	if (isDiffuse) {
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);			//assign diffuse 
	}
	else {
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightClose);
	}
	if (isAmbient) {
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);			//assign ambient 
	}
	else {
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightClose);
	}
	if (isSpecular) {
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);			//assign ambient 
	}
	else {
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightClose);
	}

	GLfloat lightPosition[4] = { positionX, positionY, positionZ, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);		//assign position of the light
}
void projection() {

	if (isPerspective) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(80.0, 1.0, P_NEAR, P_FAR);
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-6.0, 6.0, -6.0, 6.0, O_NEAR, O_FAR);
	}


	glTranslatef(pTx, pTy, 0); // Translate X & Y for O and P projection
	glRotatef(ry, 0, 1, 0); // Rotate Y for ortho only!!!
}
void leftBuild() {
	glEnable(GL_TEXTURE_2D);

#pragma region basement
	glPushMatrix();

	glTranslatef(-2.75, -2, 0);
	cubeLine(1.5, 1, 1.5);
	texture = loadTexture("textures/wall.bmp");
	cube(1.5, 1, 1.5);
	glPopMatrix();
	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);
#pragma endregion basement

#pragma region body
	glPushMatrix();
	texture = loadTexture("textures/window.bmp");
	glTranslatef(-2.5, 0, 0.3);
	cubeLine(1, 2, 1);
	cube(1, 2, 1);
	glPopMatrix();
	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);
#pragma endregion body

#pragma region bodyDesign
	glPushMatrix();
	texture = loadTexture("textures/bodydesign.bmp");
	glTranslatef(-2.6, 1.25, 0.3);
	cube(1.2, 0.2, 1.2);
	cubeLine(1.2, 0.2, 1.2);
	glPopMatrix();
	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	texture = loadTexture("textures/bodydesign.bmp");
	glTranslatef(-2.6, 0.5, 0.3);
	cube(1.2, 0.2, 1.2);
	cubeLine(1.2, 0.2, 1.2);
	glPopMatrix();
	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);
#pragma endregion bodyDesign

#pragma region pillars

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(-2.6, 1.3, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "textures/wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(-1.4, 1.3, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "textures/wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(-2.6, 0.2, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "textures/wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(-1.4, 0.2, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "textures/wall.bmp");
	glPopMatrix();
#pragma endregion pillars

#pragma region topCones

	//Top 4 small cones
	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-2.6, -1.3, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "textures/wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-1.4, -1.3, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "textures/wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-2.6, -0.2, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "textures/wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-1.4, -0.2, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "textures/wall.bmp");
	glPopMatrix();

	//Top Big cone
	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(-2, -0.7, 2);
	cylinder(0.6, 0, 1, 20, 1, "textures/wall.bmp");
	glPopMatrix();

#pragma endregion topCones
	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);

}
void rightBuild() {
	glEnable(GL_TEXTURE_2D);
#pragma region basement
	glPushMatrix();
	glTranslatef(2.75, -2, 0);
	cubeLine(1.5, 1, 1.5);
	texture = loadTexture("textures/wall.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	cube(1.5, 1, 1.5);
	glPopMatrix();
	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);

#pragma endregion basement

#pragma region body
	glPushMatrix();
	texture = loadTexture("textures/window.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glTranslatef(3, 0, 0.3);
	cubeLine(1, 2, 1);
	cube(1, 2, 1);
	glPopMatrix();
	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);
#pragma endregion body

#pragma region bodyDesign
	glPushMatrix();
	texture = loadTexture("textures/bodydesign.bmp");
	glTranslatef(2.9, 1.25, 0.3);
	cube(1.2, 0.2, 1.2);
	cubeLine(1.2, 0.2, 1.2);
	glPopMatrix();
	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	texture = loadTexture("textures/bodydesign.bmp");
	glTranslatef(2.9, 0.5, 0.3);
	cube(1.2, 0.2, 1.2);
	cubeLine(1.2, 0.2, 1.2);
	glPopMatrix();
	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);
#pragma endregion bodyDesign

#pragma region pillars
	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(2.9, 1.3, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "textures/wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(4.1, 1.3, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "textures/wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(2.9, 0.2, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "textures/wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.1, 0, 0);
	glTranslatef(4.1, 0.2, -2);
	cylinder(0.2, 0.2, 3, 25, 1, "textures/wall.bmp");
	glPopMatrix();
#pragma endregion pillars

#pragma region topCones
	//Top 4 small cones
	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(2.9, -1.3, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "textures/wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(4.1, -1.3, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "textures/wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(2.9, -0.2, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "textures/wall.bmp");
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(4.1, -0.2, 2);
	cylinder(0.2, 0, 0.5, 20, 1, "textures/wall.bmp");
	glPopMatrix();

	//Top Big cone
	glPushMatrix();
	glRotatef(-90, 0.1, 0, 0);
	glTranslatef(3.5, -0.7, 2);
	cylinder(0.6, 0, 1, 20, 1, "textures/wall.bmp");
	glPopMatrix();
#pragma endregion topCones
	glDisable(GL_TEXTURE_2D);
}
void bridge() {
	glEnable(GL_TEXTURE_2D);
#pragma region topBridge
	glPushMatrix();
	texture = loadTexture("textures/bridge.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);
	glTranslatef(-1.5, 1, 0.4);
	cube(5, 0.4, 0.8);
	glPopMatrix();
	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);
#pragma endregion topBridge

#pragma region bridge
	texture = loadTexture("textures/bridge.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);

	//left bridge
	glPushMatrix();
	glTranslatef(-4.7, -1.2, 0);
	cube(2.0, 0.2, 1.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.25, -1.2, 0);
	glRotatef(openAngle, 0, 0, 1);
	cube(2.0, 0.2, 1.5);
	glPopMatrix();

	//right bridge
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-6.2, -1.2, -1.5);
	cube(2.0, 0.2, 1.5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-2.75, -1.2, -1.5);
	glRotatef(openAngle, 0, 0, 1);
	cube(2.0, 0.2, 1.5);
	glPopMatrix();

	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);

	if (open) {
		if (openAngle < 45)
			openAngle += 0.4;
	}
	else {
		if (openAngle > 0)
			openAngle -= 0.4;
	}
#pragma endregion bridge

#pragma region water
	texture = loadTexture("textures/sea.bmp");
	glPushMatrix();
	glTranslatef(-5, -6, 0);
	cube(15, 4, 10);
	glPopMatrix();

#pragma endregion water
	glDeleteTextures(1, &texture);
	glDisable(GL_TEXTURE_2D);
}
void drawBridge() {

	projection();

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	if (isPerspective) {
		glTranslatef(0, 0, -15);
	}

	glPushMatrix();
	glTranslatef(0, 0, 5);
	leftBuild();
	rightBuild();
	bridge();

	glPopMatrix();
	glPopMatrix();
}
void display()														// to display
{

	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClearColor(0, 0, 0, 0.0f);							// to change the background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	projection();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0, 0.0, zoomLevel);
	//texture
	glEnable(GL_TEXTURE_2D);
	yellowMaterial();
	lighting();
	glEnable(GL_LIGHT0);

	//background
	if (!onBackground) {
		background();
	}
	//-----------------------------------------------
	//Control the view
	glRotatef(xRotated, 1.0, 0.0, 0.0);
	glRotatef(yRotated, 0.0, 1.0, 0.0);
	glRotatef(zRotated, 0.0, 0.0, 1.0);
	//-----------------------------------------------


	//draw
	glPushMatrix();
	glTranslatef(0.0, 0.0, 5);
	drawBridge();
	glPopMatrix();





	glPopMatrix();
	glFlush();	//Empty all GL buffers.

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)   //WinMain is same as the main in C
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);                                // The window size

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------
	//
	glEnable(GL_DEPTH_TEST);		//To tell the compiler we need to do the 3d.
	ShowWindow(hWnd, nCmdShow);


	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)											//Important part(the code)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		display();
		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------
