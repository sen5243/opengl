
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>


#define WINDOW_TITLE "P4b Demo"
int qno = 1;
float rotateSpeed = 0, rZ = 0, rY = 0;
double r = 0;
//glu = 1 polygon (sphere,cylinder) , cube = 6 polygons, pyramid = 5 polygons

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);

		else if (wParam == 0x31) {
			qno = 1;
		}
		else if (wParam == 0x32) {
			qno = 2;
		}

		else if (wParam == VK_LEFT) {	
			rY = 1;
			rotateSpeed += 1;
		}
		else if (wParam == VK_RIGHT) {	
			rY = 1;
			rotateSpeed -= 1;
		}
		else if (wParam == VK_SPACE) {
			//press DOWN arrow
			rotateSpeed = 0;
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

void drawSphereLine(double r, double slice, double stacks) {


	GLUquadric* sphere = NULL; // define by create quadric obj pointer

	sphere = gluNewQuadric(); // create new quadric obj in memory, return pointer, null pointer will be returned if failed

	gluQuadricDrawStyle(sphere, GLU_LINE);;
	gluSphere(sphere, r, slice, stacks); // draw sphere with glu library; more slices and stacks, more smoother
	gluDeleteQuadric(sphere); // delete the quadric obj in the memory
}
void drawSphere(double r, double slice, double stacks) {


	GLUquadric* sphere = NULL; // define by create quadric obj pointer

	sphere = gluNewQuadric(); // create new quadric obj in memory, return pointer, null pointer will be returned if failed

	gluQuadricDrawStyle(sphere, GLU_FILL);;
	gluSphere(sphere, r, slice, stacks); // draw sphere with glu library; more slices and stacks, more smoother
	gluDeleteQuadric(sphere); // delete the quadric obj in the memory
}
void drawCylinderLine(double baser, double topr, double h, double slice, double stacks) {

	GLUquadric* cylinder = NULL; // define by create quadric obj pointer

	cylinder = gluNewQuadric(); // create new quadric obj in memory, return pointer, null pointer will be returned if failed

	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, baser, topr, h, slice, stacks); // draw sphere with glu library; more slices and stacks, more smoother
	gluDeleteQuadric(cylinder); // delete the quadric obj in the memory
}
void drawCylinder(double baser, double topr, double h, double slice, double stacks) {

	GLUquadric* cylinder = NULL; // define by create quadric obj pointer

	cylinder = gluNewQuadric(); // create new quadric obj in memory, return pointer, null pointer will be returned if failed

	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, baser, topr, h, slice, stacks); // draw sphere with glu library; more slices and stacks, more smoother
	gluDeleteQuadric(cylinder); // delete the quadric obj in the memory
}
void drawConeLine(double topr, double h, double slice, double stacks) {

	GLUquadric* cone = NULL; // define by create quadric obj pointer

	cone = gluNewQuadric(); // create new quadric obj in memory, return pointer, null pointer will be returned if failed

	gluQuadricDrawStyle(cone, GLU_LINE);
	gluCylinder(cone, 0, topr, h, slice, stacks); // draw sphere with glu library; more slices and stacks, more smoother
	gluDeleteQuadric(cone); // delete the quadric obj in the memory
}
void drawCone(double topr, double h, double slice, double stacks) {

	GLUquadric* cone = NULL; // define by create quadric obj pointer

	cone = gluNewQuadric(); // create new quadric obj in memory, return pointer, null pointer will be returned if failed

	gluQuadricDrawStyle(cone, GLU_FILL);
	gluCylinder(cone, 0, topr, h, slice, stacks); // draw sphere with glu library; more slices and stacks, more smoother
	gluDeleteQuadric(cone); // delete the quadric obj in the memory
}

void p4bDemo() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glColor3f(1, 0, 0);
	drawCylinderLine(0.5, 0.5, 1, 30, 30);
	glColor3f(0, 1, 0);
	drawSphereLine(0.5, 30, 30);
}
void p4bQ1(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);

	glRotatef(rotateSpeed, 0.0, rY,rZ);
	

	//top ice cream
	glColor3f(0.647, 0.494, 0.337);
	drawSphere(0.2, 50, 50);

	//bottom ice cream
	glPushMatrix();
	glColor3f(0.7, 0.95, 0.8);
	glTranslatef(0.0, 0.25, 0.0);
	drawSphere(0.2,50,50);
	glPopMatrix();

	//cone filled
	glPushMatrix();
	glColor3f(0.72, 0.38, 0.11);
	glTranslatef(0.0, -0.6, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	drawCone(0.22, 0.6, 50, 50);
	glPopMatrix();

	//cone outline
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0, -0.6, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	drawCone(0.22, 0.6, 50, 50);
	glPopMatrix();

	//cone line
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0, -0.6, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	drawConeLine(0.22, 0.6, 50, 50);
	glPopMatrix();

	//cone paper
	glPushMatrix();
	glColor3f(0.952, 0.878, 0.69);
	glTranslatef(0.0, -0.7, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	drawCone(0.20, 0.6, 50, 50);
	glPopMatrix();

	//topping 1 (left choc)
	glPushMatrix();
	glTranslatef(-0.15, 0.45, 0.0);
	glRotatef(10, 1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	drawCylinder(0.08, 0.08, 0.02, 50, 50);
	glPopMatrix();

	//topping 2 (left choc)
	glPushMatrix();
	glTranslatef(-0.10, 0.45, -0.05);
	glRotatef(10, 1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	drawCylinder(0.08, 0.08, 0.02, 50, 50);
	glPopMatrix();

	//topping 3 (cherry)
	glPushMatrix();
	glTranslatef(0.05, 0.48, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	drawSphere(0.05, 50, 50);
	glPopMatrix();

	//topping 4 (wafer)
	glPushMatrix();
	glTranslatef(0.1, 0.3, 0.0);
	glRotatef(-70, 1.0, 1.0, 0.0);
	glColor3f(0.72, 0.38, 0.11);
	drawCylinder(0.03, 0.03, 0.5, 50, 50);
	glPopMatrix();

	//topping 4 (umbrella)
	glPushMatrix();
	glTranslatef(-0.05, 0.45, -0.15);
	glRotatef(-130, 1.0, 1.0, 0.0);
	glColor3f(1, 0.38, 0.11);
	drawCylinder(0.1, 0.0, 0.1, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.4, -0.1);
	glRotatef(-130, 1.0, 1.0, 0.0);
	glColor3f(1, 1, 1);
	drawCylinder(0.01, 0.01, 0.1, 50, 50);
	glPopMatrix();

	

	
}
void display()
{
	switch (qno)
	{
	case 1:
		p4bQ1();
		break;
	default:
		p4bDemo();
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
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
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