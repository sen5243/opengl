
#include <Windows.h>		//window class
#include <gl/GL.h>			//openGL class
#include <gl/GLU.h>			//GLU class
#include <math.h>			//GLU class

#pragma comment (lib, "GLU32.lib")
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int qNo = 4;
float rotateSpeed = 0, rZ = 0, rY = 0;
double r = 0;


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == 0x31)	//press key '1'
			qNo = 1;
		else if (wParam == 0x32)	//press key '2'
			qNo = 2;
		else if (wParam == 0x33)	//press key '3'
			qNo = 3;
		else if (wParam == 0x34)	//press key '4'
			qNo = 4;


		else if (wParam == 0x58)	//press key 'X'
			glRotatef(-5, 1.0, 0.0, 0.0);
		else if (wParam == 0x59)	//press key 'Y'
			glRotatef(-5, 0.0, 1.0, 0.0);
		else if (wParam == 0x5A)	//press key 'Z'
			glRotatef(-5, 0.0, 0.0, 1.0);


		else if (wParam == VK_UP)	//press UP arrow
			rZ -= 2;
		else if (wParam == VK_DOWN)	//press DOWN arrow
			rZ += 2;
		else if (wParam == VK_LEFT)	//press UP arrow
			rY -= 2;
		else if (wParam == VK_RIGHT)	//press DOWN arrow
			rY += 2;
		else if (wParam == VK_SPACE) {
			//press DOWN arrow
			rY = 0;
			rZ = 0;
		}
		break;

	default:
		break;
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
void drawCube(float size) {

	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 1.0);
	//Face 1 (Bottom face)
	glVertex3f(0.0, 0.0, size);
	glVertex3f(size, 0.0, size);
	glVertex3f(size, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);			//ORIGIN must be point 4 || MUST end at ORIGIN for 1st face

	glColor3f(1.0, 0.0, 0.0);
	//Face 2 (Left face)
	glVertex3f(0.0, 0.0, 0.0);			//must start with face that is connected to where we stopped previously (0.0,0.0,0.0)
	glVertex3f(0.0, size, 0.0);
	glVertex3f(0.0, size, size);
	glVertex3f(0.0, 0.0, size);

	glColor3f(0.0, 1.0, 0.0);
	//Face 3 (Front face)
	glVertex3f(0.0, 0.0, size);			//must start with face that is connected to where we stopped previously (0.0, 0.0, size)
	glVertex3f(0.0, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, 0.0, size);

	glColor3f(0.0, 0.0, 1.0);
	//Face 4 (Right face)
	glVertex3f(size, 0.0, size);			//must start with face that is connected to where we stopped previously (size, 0.0, size)
	glVertex3f(size, size, size);
	glVertex3f(size, size, 0.0);
	glVertex3f(size, 0.0, 0.0);

	glColor3f(1.0, 1.0, 0.775);
	//Face 5 (Back face)
	glVertex3f(size, 0.0, 0.0);			//must start with face that is connected to where we stopped previously (size, 0.0, 0.0)
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, size, 0.0);
	glVertex3f(size, size, 0.0);

	glColor3f(0.4, 0.3, 0.7);
	//Face 6 (Top face)
	glVertex3f(size, size, 0.0);			//must start with face that is connected to where we stopped previously (size, size, 0.0)
	glVertex3f(0.0, size, 0.0);
	glVertex3f(0.0, size, size);
	glVertex3f(size, size, size);
	glEnd();
}

void drawPyramid(float size) {

	glColor3f(1.0, 0.0, 0.0);
	//Face 1 (Bottom face)
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, size);
	glVertex3f(size, 0.0, size);
	glVertex3f(size, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(size / 2, size, size / 2); //top vertice
	glVertex3f(0.0, 0.0, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0.0, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0.0, 0.0);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void drawCuboidLineLoopOri(float size) {

	glPushMatrix();
	glRotatef(rY, 1.0, 1.0, 1.0);
	//Cuboid 1 (upper arm)
	glBegin(GL_LINE_LOOP);
	//Bottom
	glVertex3f(0, 0, -0.2);
	glVertex3f(size, 0, -0.2);
	glVertex3f(size, 0, 0);
	glVertex3f(0, 0, 0);			//ORIGIN must be point 4 || MUST end at ORIGIN for 1st face

	//Left
	glVertex3f(0, 0.0, -0.2);
	glVertex3f(0, 0.2, -0.2);
	glVertex3f(0, 0.2, 0.0);
	glVertex3f(0, 0, 0);

	//Back
	glVertex3f(size, 0.0, 0.0);
	glVertex3f(size, 0.2, 0.0);
	glVertex3f(0, 0.2, 0.0);
	glVertex3f(0, 0, 0);

	//Right
	glVertex3f(0.0, 0.2, 0.0);
	glVertex3f(size, 0.2, 0.0);
	glVertex3f(size, 0.0, 0.0);

	//Front
	glVertex3f(size, 0.0, 0.0);
	glVertex3f(size, 0.2, 0.0);
	glVertex3f(size, 0.2, -0.2);
	glVertex3f(size, 0.0, -0.2);

	//Top
	glVertex3f(size, 0.0, -0.2);
	glVertex3f(0, 0.0, -0.2);
	glVertex3f(0, 0.2, -0.2);
	glVertex3f(size, 0.2, -0.2);
	glVertex3f(size, 0.0, -0.2);
	glEnd();

	glPushMatrix();
	glRotatef(rZ, 0.0, 0.0, 1.0);
	//Cuboid 2 (lower arm)
	glBegin(GL_LINE_LOOP);
	//Bottom
	glVertex3f(0, 0, -0.2);
	glVertex3f(-size, 0, -0.2);
	glVertex3f(-size, 0, 0);
	glVertex3f(0, 0, 0);			//ORIGIN must be point 4 || MUST end at ORIGIN for 1st face

	//Right
	glVertex3f(0, 0.0, -0.2);
	glVertex3f(0, 0.2, -0.2);
	glVertex3f(0, 0.2, 0.0);
	glVertex3f(0, 0, 0);

	//Back
	glVertex3f(-size, 0.0, 0.0);
	glVertex3f(-size, 0.2, 0.0);
	glVertex3f(0, 0.2, 0.0);
	glVertex3f(0, 0, 0);

	//Left
	glVertex3f(-size, 0.0, 0.0);
	glVertex3f(-size, 0.2, 0.0);
	glVertex3f(-size, 0.2, -0.2);
	glVertex3f(-size, 0.0, -0.2);

	////Front
	glVertex3f(-size, 0.0, -0.2);
	glVertex3f(-size, 0.2, -0.2);
	glVertex3f(0, 0.2, -0.2);
	glVertex3f(0, 0.0, -0.2);
	glEnd();
	glPopMatrix();

	glPopMatrix();

}

void drawCuboidLineLoop(float length) {

	//Cuboid 1 (upper arm)
	glBegin(GL_LINE_LOOP);
	//Bottom
	glVertex3f(0, 0, -0.2);
	glVertex3f(length, 0, -0.2);
	glVertex3f(length,0,0);
	glVertex3f(0,0,0);			//ORIGIN must be point 4 || MUST end at ORIGIN for 1st face

	//Left
	glVertex3f(0, 0.0, -0.2);
	glVertex3f(0, 0.2, -0.2);
	glVertex3f(0, 0.2, 0.0);
	glVertex3f(0, 0, 0);

	//Back
	glVertex3f(length, 0.0, 0.0);
	glVertex3f(length, 0.2, 0.0);
	glVertex3f(0, 0.2, 0.0);
	glVertex3f(0, 0, 0);

	//Right
	glVertex3f(0.0, 0.2, 0.0);
	glVertex3f(length, 0.2, 0.0);
	glVertex3f(length, 0.0, 0.0);

	//Front
	glVertex3f(length, 0.0, 0.0);
	glVertex3f(length, 0.2, 0.0);
	glVertex3f(length, 0.2, -0.2);
	glVertex3f(length, 0.0, -0.2);

	//Top
	glVertex3f(length, 0.0, -0.2);
	glVertex3f(0, 0.0, -0.2);
	glVertex3f(0, 0.2, -0.2);
	glVertex3f(length, 0.2, -0.2);
	glVertex3f(length, 0.0, -0.2);
	glEnd();


	////Cuboid 2 (lower arm)
	//glBegin(GL_LINE_LOOP);
	////Bottom
	//glVertex3f(0, 0, -0.2);
	//glVertex3f(-length, 0, -0.2);
	//glVertex3f(-length, 0, 0);
	//glVertex3f(0, 0, 0);			//ORIGIN must be point 4 || MUST end at ORIGIN for 1st face

	////Right
	//glVertex3f(0, 0.0, -0.2);
	//glVertex3f(0, 0.2, -0.2);
	//glVertex3f(0, 0.2, 0.0);
	//glVertex3f(0, 0, 0);

	////Back
	//glVertex3f(-length, 0.0, 0.0);
	//glVertex3f(-length, 0.2, 0.0);
	//glVertex3f(0, 0.2, 0.0);
	//glVertex3f(0, 0, 0);

	////Left
	//glVertex3f(-length, 0.0, 0.0);
	//glVertex3f(-length, 0.2, 0.0);
	//glVertex3f(-length, 0.2, -0.2);
	//glVertex3f(-length, 0.0, -0.2);

	//////Front
	//glVertex3f(-length, 0.0, -0.2);
	//glVertex3f(-length, 0.2, -0.2);
	//glVertex3f(0, 0.2, -0.2);
	//glVertex3f(0, 0.0, -0.2);
	//glEnd();


}

void drawSphere(double r) {
	GLUquadricObj* sphere = NULL;	//create quadric object pointer
	sphere = gluNewQuadric();		//create quadric object in memory
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, r, 50, 50);	//draw sphere with glu library (slice = vertical | stack = horizontal)
	gluDeleteQuadric(sphere);		//delete object so dont waste heap memory
}

void drawSphereWithoutGLU()
{
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	GLfloat radius = 0.5;
	int sliceNo = 30, stackNo = 30;

	for (sliceA = 0.0; sliceA < 2 * PI; sliceA += PI / sliceNo)
	{
		glBegin(GL_LINE_STRIP);
		for (stackA = 0.0; stackA < 2 * PI; stackA += PI / stackNo)
		{
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glVertex3f(x, y, z);
			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void drawSemiSphereWithoutGLU()
{
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	GLfloat radius = 0.5;
	int sliceNo = 30, stackNo = 30;

	for (sliceA = 0.0; sliceA < PI; sliceA += PI / sliceNo)
	{
		glBegin(GL_LINE_STRIP);
		for (stackA = 0.0; stackA < PI; stackA += PI / stackNo)
		{
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glVertex3f(x, y, z);
			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void drawCylinder (double bR, double tR, double h) {
	GLUquadricObj* cylinder = NULL;	//create quadric object pointer
	cylinder = gluNewQuadric();		//create quadric object in memory
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, bR, tR, h, 50, 50);	//draw sphere with glu library (slice = vertical | stack = horizontal)
	gluDeleteQuadric(cylinder);		//delete object so dont waste heap memory
}

void drawCone(double tR, double h) {

	GLUquadricObj* cylinder = NULL;	//create quadric object pointer
	cylinder = gluNewQuadric();		//create quadric object in memory
	gluQuadricDrawStyle(cylinder, GLU_LINE);	//GLU_FILL is default
	gluCylinder(cylinder, 0, tR, h, 18, 18);	//draw sphere with glu library (slice = vertical | stack = horizontal)
	gluDeleteQuadric(cylinder);		//delete object so dont waste heap memory
}

void drawConeFill(double tR, double h) {

	GLUquadricObj* cylinder = NULL;	//create quadric object pointer
	cylinder = gluNewQuadric();		//create quadric object in memory
	gluQuadricDrawStyle(cylinder, GLU_FILL);	//GLU_FILL is default
	gluCylinder(cylinder, 0, tR, h, 30, 30);	//draw sphere with glu library (slice = vertical | stack = horizontal)
	gluDeleteQuadric(cylinder);		//delete object so dont waste heap memory
}

void GPprac4a() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(1.0, 1.0, 1.0, 1.0);
	//cube 1
	drawCube(0.5);
	//cube 2
	drawCube(0.2);
}

void GPprac4b() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glClearColor(0.5, 0.5, 0.0, 1.0);

	glColor3f(0.5, 0.0, 0.0);
	glRotatef(1.0, 1.0, 1.0, 1.0);			//to move, use translate, now only rotate from origin
	glLineWidth(0.5);

	drawSphere(0.2);
	glColor3f(0.5, 0.5, 0.0);
	drawCylinder(0.2,0.2,0.8);

	glPushMatrix();
	glColor3f(0.0, 0.5, 0.0);
	glTranslatef(0.0, 0.0, 0.8);
	drawSphere(0.2);
	glPopMatrix();

	//drawSphereWithoutGLU(); 
	//drawSemiSphereWithoutGLU();
}

void P4Aq3() {

	glPushMatrix();
	glRotatef(rY, 1.0, 1.0, 1.0);
	drawCuboidLineLoop(0.6);

	glPushMatrix();
	glRotatef(rZ, 0.0, 0.0, 1.0);
	drawCuboidLineLoop(-0.6);
	
	glPopMatrix();

	glPopMatrix();
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
}

void P4Bq1() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);

	glColor3f(0.15, 0.16, 0.38);

	//top ice cream
	drawSphere(0.2);

	//bottom ice cream
	glPushMatrix();
	glColor3f(0.44, 0.29, 0.78);
	glTranslatef(0.0, 0.25, 0.0);
	drawSphere(0.2);
	glPopMatrix();

	//cone filled
	glPushMatrix();
	glColor3f(0.72, 0.38, 0.11);
	glTranslatef(0.0, -0.6, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	drawConeFill(0.22,0.6);
	glPopMatrix();

	//cone outline
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0, -0.6, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	drawCone(0.22, 0.6);
	glPopMatrix();

	//cone paper
	glPushMatrix();
	glColor3f(1.0, 0.95, 0.8);
	glTranslatef(0.0, -0.7, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	drawConeFill(0.20, 0.6);
	glPopMatrix();

	//topping 1 (left choc)
	glPushMatrix();
	glTranslatef(-0.15, 0.45, 0.0);
	glRotatef(10, 1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	drawCylinder(0.08, 0.08, 0.02);
	glPopMatrix();

	//topping 2 (left choc)
	glPushMatrix();
	glTranslatef(-0.10, 0.45, -0.05);
	glRotatef(10, 1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	drawCylinder(0.08, 0.08, 0.02);
	glPopMatrix();

	//topping 3 (cherry)
	glPushMatrix();
	glTranslatef(0.05, 0.48, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	drawSphere(0.05);
	glPopMatrix();

	//topping 4 (wafer)
	glPushMatrix();
	glTranslatef(0.1, 0.3, 0.0);
	glRotatef(-70, 1.0, 1.0, 0.0);
	glColor3f(0.72, 0.38, 0.11);
	drawCylinder(0.03,0.03,0.5);
	glPopMatrix();
}

void display()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);			//stop the see-through effect

	switch (qNo)
	{
	case 1: 
		drawPyramid(0.5);
		break;
	case 2:
		P4Aq3();
		break;
	case 3:
		GPprac4b();
		break;
	case 4:
		P4Bq1();
		break;
	default:
		break;
	}
	


}


//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
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
		1300, 150, 600, 600,
		NULL, NULL, wc.hInstance, NULL);

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

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
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