#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#define WINDOW_TITLE "P3 Demo"

float tx1 = 0, ty1 = 0, tSpeed = 0.1; // obj 1 translation
float tx2 = 0, ty2 = 0; // obj 2 translation
float angle = 0; // angle
float x2 = 0, y2 = 0; // point on circle (x2,y2)
float PI = 3.1429; // PI
float tSpeed2 = 2, cSpeed = 0.1; // fan and clouds speed
float r = 10; //rotation for windmill fans
float x = 30; // rotation for sun
int n = 3; // number of fans
double d = 120; // each fan angle
int i = 0;
int qno = 0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY: //when click on x button
		PostQuitMessage(0); //quit function
		break;

	case WM_KEYDOWN: // for pressing key
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0); //VK_Escape = Esc key
		else if (wParam == 0x30) {
			qno = 0;
		}
		else if (wParam == 0x31) {

			qno = 1;
		}
		else if (wParam == 0x32) {
			qno = 2;
		}
		else if (wParam == VK_LEFT) {
			tx1 -= tSpeed; //VK_LEFT = Left key
			tx2 += tSpeed;
		}
		else if (wParam == 0x41) {//A key

			if (tSpeed2 == 0) {
				tSpeed2 = 2;
			}
			else {
				tSpeed2 = 10;
			}
			r += tSpeed2; // rotation speed of fan
		}
		else if (wParam == VK_RIGHT) {
			tx1 += tSpeed; //VK_RIGHT = Right key
			tx2 -= tSpeed; 
		}
		else if (wParam == 0x44) {//D key

			if (tSpeed2 == 0) {
				tSpeed2 = -2;
			}
			else {
				tSpeed2 = -10;
			}

			r += tSpeed2;
		}
		else if (wParam == VK_DOWN) {
			ty1 -= tSpeed; //VK_DOWN = Down key
			ty2 += tSpeed;

			if (qno == 2) {//Q2
				if (n > 1) {
					n -= 1;
				}

				d = 360 / (double)n;
			}

		}
			
		else if (wParam == VK_UP) {
			ty1 += tSpeed; //VK_UP = UP key
			ty2 -= tSpeed;

			if (qno == 2) {//Q2
				n += 1;
				d = 360 / (double)n;
			}
		}

		else if (wParam == VK_SPACE) { //Q1 reset
			tx1 = 0; 
			tx2 = 0;
			ty1 = 0;
			ty2 = 0; 

			if (qno == 2) { //Q2 reset
				tSpeed2 = 0;
				r = 0;
			}
		}
			
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

void p3Demo()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//Block 4: Grp obj 1,2,3 tgt
	
	glPushMatrix();// save the current state
	glScalef(0.5, 0.5, 0.5);


	//Block 1 : obj 1: Red Triangle

	glPushMatrix(); // save the current state
	glTranslatef(0.0, 0.5, 0.0); //Ty = 0.5

	glBegin(GL_TRIANGLES); // object 1
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.0);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
	glPopMatrix(); //load back to previous state (Line 75)

	//Block 5: Grp 2 and 3
	glPushMatrix();
	glRotatef(90, 0.0, 0.0, 1.0);

	//Block 2: obj 2: Green quad
	glPushMatrix();
	glTranslatef(0.5, 0.0, 0.0); //Tx = 0.5

	glBegin(GL_QUADS); //object 2
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();

	glPopMatrix();//load back to previous state (Line 95)

	//Block 3: obj 3: Blue quad
	glPushMatrix();
	glTranslatef(-0.5, 0.0, 0.0); //Tx = 0.5

	glBegin(GL_QUADS); //object 3
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
	glPopMatrix();//load back to previous state (Line 95)
	glPopMatrix();// load back to block 4
	glPopMatrix(); //pop all
}
//--------------------------------------------------------------------
void drawCircle(float x, float y, float radius, float triNum, float r, float g, float b) {
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(r, g, b);
	glVertex2f(x, y); // origin of circle (x,y) = (0,0)
	// upper half circle:  0 to PI, bottom half circle : PI to 2PI, window resolution not same will become oval
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / triNum) {
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}

	glEnd();
}

void drawUpperHalfCircle(float x, float y, float radius, float triNum, float r, float g, float b) {

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(r, g, b);
	glVertex2f(x, y); // origin of circle (x,y) = (0,0)
	// upper half circle:  0 to PI, bottom half circle : PI to 2PI, window resolution not same will become oval
	for (angle = 0; angle <= PI; angle += (2 * PI) / triNum) {
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}

	glEnd();
}
void drawDisk(double radius) {
	int d;
	glBegin(GL_POLYGON);
	for (d = 0; d < 32; d++) {
		double angle = 2 * PI / 32 * d;
		glVertex2d(radius * cos(angle), radius * sin(angle));
	}
	glEnd();
}
void drawSun() {

	int i;
	
	glPushMatrix();
	glColor3f(1, 1, 0);
	glRotatef(x, 0, 0, 1);
	x += 1;
	for (i = 0; i < 13; i++) { // Draw 13 rays, with different rotations.
		glRotatef(360 / 13, 0, 0, 1); 
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(0.75f, 0);
		glEnd();
	}
	drawDisk(0.5);
	glPopMatrix();
}
void drawGrass() {

	glColor3f(0.1, 1.0, 0.1);
	glBegin(GL_QUADS); //head
	glVertex2d(-1, -0.3);
	glVertex2d(1, -0.3);
	glVertex2d(1, -1);
	glVertex2d(-1, -1);
	glEnd();
}
void drawTriangle() {
	glColor3f(1, 0.3, 0.3);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(-0.5f, -0.5f);
	glEnd();
}
void drawFans() {

	glColor3f(0.4f, 0.4f, 0.8f);
	
	glPushMatrix();
	glTranslatef(0, 0.55, 0);
	glRotatef(r, 0, 0, 1);
	r += tSpeed2;
	
	for (int i = 0; i < n; i++) {
		glRotated(d, 0, 0, 1);  // Note: These rotations accumulate.
		glBegin(GL_POLYGON);
		glVertex2f(0.05, 0);
		glVertex2f(0.5f, 0.1f);
		glVertex2f(0.5f, 0);
		glVertex2f(0.5f, -0.1f);
		glEnd();
	}
	glPopMatrix();
}
void drawClouds() {
	//cloud 1
	glPushMatrix();
	glTranslatef(cSpeed, 0.0, 0.0);
	

	if (i == 0) { //move to right
		cSpeed += 0.005;
		if (cSpeed >= 1) {
			i++;
		}
	}
	else if(i == 1){ //move to left
		cSpeed -= 0.005;
		if (cSpeed <= 0) {
			i--;
		}
	}

	drawCircle(-0.45, 0.7, 0.15, 30, 1, 1, 1);
	drawCircle(-0.65, 0.7, 0.15, 30, 1, 1, 1);
	drawCircle(-0.55, 0.8, 0.15, 30, 1, 1, 1);

	//cloud 2
	drawCircle(0.45, 0.7, 0.15, 30, 1, 1, 1);
	drawCircle(0.65, 0.7, 0.15, 30, 1, 1, 1);
	drawCircle(0.55, 0.8, 0.15, 30, 1, 1, 1);
	glPopMatrix();
}
void drawWindmill() {


	drawUpperHalfCircle(0, 0.4, 0.3, 50, 1, 0.3, 0.3);
	drawCircle(0, 0.55, 0.05, 30, 1, 1, 0);

	glColor3f(0.749, 0.462, 0.211);
	glBegin(GL_QUADS); //head
		glVertex2d(-0.35, 0.45);
		glVertex2d(-0.35, 0.3);
		glVertex2d(0.35, 0.3);
		glVertex2d(0.35, 0.45);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON); // body
		glVertex2d(-0.35, 0.3);
		glVertex2d(-0.5, -0.9);
		glVertex2d(0.5, -0.9);
		glVertex2d(0.35, 0.3);
	glEnd();

	glColor3f(0.749, 0.462, 0.211);
	glBegin(GL_POLYGON); // door
	glVertex2d(-0.1, -0.6);
	glVertex2d(-0.1, -0.9);
	glVertex2d(0.1, -0.9);
	glVertex2d(0.1, -0.6);
	glEnd();

	drawCircle(0.06, -0.75, 0.02, 30, 1, 1, 0);



	drawFans();
}
void p3Q1() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // change background color, rgba
	glClear(GL_COLOR_BUFFER_BIT); // Fills the scene with blue.
	//Block 1: obj 1: Green quad
	glPushMatrix();
	glTranslatef(tx1, ty1, 0.0); //Translation for object 1

	glBegin(GL_QUADS); //object 1
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();

	glPopMatrix();//load back to previous state

	//Block 2: obj 2: Blue quad
	glPushMatrix();
	glTranslatef(tx2, ty2, 0.0); //Translation for object 2

	glBegin(GL_QUADS); //object 3
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
	glPopMatrix();//load back to previous state 
}
void p3Q2() {

	glClearColor(0.0f, 0.7f, 1.0f, 0.0f); // change background color, rgba
	glClear(GL_COLOR_BUFFER_BIT); // Fills the scene with blue.

	drawSun();
	drawGrass();
	drawClouds();
	drawWindmill();
	

}
void display() {
	switch (qno)
	{
	case 1:
		p3Q1();
		break;
	case 2:
		p3Q2();
		break;
	default:
		p3Demo();
		break;
	}

}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW; // horizontal and vertical (2d)

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		400, 10, 400, 400,
		NULL, NULL, wc.hInstance, NULL); // CW_USEDEFAULT = default location, 800, 600 (width,height of window)

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

	} //refresh screen, listening on the key input

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------