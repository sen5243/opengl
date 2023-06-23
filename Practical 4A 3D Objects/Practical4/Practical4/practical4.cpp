#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#define WINDOW_TITLE "P4 Demo"

int qno = 0;
float rangle = 0, rx = 0, ry = 0, rz = 0, rSpeed = 10; //q2
float rangle2 = 0, rx2 = 0, ry2 = 0, rz2 = 0, rSpeed2 = 5; // q3 right part
float rangle3 = 0, rx3 = 0, ry3 = 0, rz3 = 0, rSpeed3 = 5; // q3 left part

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
		else if (wParam == 0x31) // press key '1'
			qno = 1;
		else if (wParam == 0x32)// press key '2'
			qno = 2;
		else if (wParam == 0x33) {// press key '3'
			qno = 3;
			rx = 0;
			ry = 0;
			rz = 0;
			rangle = 0;
		}
		else if (wParam == 0x34)// press key '4'
			qno = 4;
		else if (wParam == 0x58) {// press X key
			if (qno == 2) {
				ry = 0;
				rz = 0;
				rx = 1;
				rangle += rSpeed;
			}
		}
		else if (wParam == 0x59) {// press Y key
			if (qno == 2) {
				rz = 0;
				rx = 0;
				ry = 1;
				rangle += rSpeed;
			}
		}

		else if (wParam == 0x5A) {// press Z key
			if (qno == 2) {
				ry = 0;
				rx = 0;
				rz = 1;
				rangle += rSpeed;
			}
		}
		else if (wParam == VK_LEFT) {// press left key
			if (qno == 3) {
				ry = 1;
				rangle += rSpeed2;
			}
		}

		else if (wParam == VK_RIGHT) {// press left key
			if (qno == 3) {
				ry = 1;
				rangle -= rSpeed2;
			}
		}

		else if (wParam == VK_UP) {// press up key
			if (qno == 3) {
				if(rangle2 <= 85){
					rz2 = 1;
					rangle2 += rSpeed2;
				}

			}
		}

		else if (wParam == VK_DOWN) {// press down key
			if (qno == 3) {
				if (rangle2 >= -85) {
					rz2 = 1;
					rangle2 -= rSpeed2;
				}
			}
		}

		else if (wParam == VK_SPACE) {
			rangle = 0;
			rangle2 = 0;
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
void drawCube(float size){
	
	glBegin(GL_QUADS);
	// Face 1: Bottom
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin

	// Face 2: Left //next face must have connection with origin, where you stop is where you start
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(0.0f, size, size);
	glVertex3f(0.0f, 0.0f, size); //origin

	//Face 3 : Front
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(0.0f, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, 0.0f, size);//origin

	//Face 4 : Right
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, 0.0f);
	glVertex3f(size, 0.0f, 0.0f); //origin

	//Face 5 : Back
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(size, size, 0.0f);

	//Face 6 : Top
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(size, size, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(0.0f, size, size);
	glVertex3f(size, size, size);
	glEnd();
}

void drawPyramid(float size) {
	
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(size/2, size, size/2);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
}
void p4Demo() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	drawCube(0.5); // cube1
	drawCube(-0.5); // cube2


}
void drawWireCube(float height,float width) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	// Face 1: Bottom
	glVertex3f(0.0f, 0.0f, width);
	glVertex3f(height, 0.0f, width);
	glVertex3f(height, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin

	// Face 2: Left //next face must have connection with origin, where you stop is where you start
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, height, 0.0f);
	glVertex3f(0.0f, height, width);
	glVertex3f(0.0f, 0.0f, width); //origin

	//Face 3 : Front
	glVertex3f(0.0f, 0.0f, width);
	glVertex3f(0.0f, height, width);
	glVertex3f(height, height, width);
	glVertex3f(height, 0.0f, width);//origin

	//Face 4 : Right
	glVertex3f(height, 0.0f, width);
	glVertex3f(height, height, width);
	glVertex3f(height, height, 0.0f);
	glVertex3f(height, 0.0f, 0.0f); //origin

	//Face 5 : Back
	glVertex3f(height, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, height, 0.0f);
	glVertex3f(height, height, 0.0f);
	//Face 6 : Top
	glVertex3f(height, height, 0.0f);
	glVertex3f(0.0f, height, 0.0f);
	glVertex3f(0.0f, height, width);
	glVertex3f(height, height, width);
	glEnd();
	
}
void p4Q1() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	drawPyramid(0.5);
	glPopMatrix();

}
void p4Q2() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glRotatef(rangle, rx, ry, rz);
	drawPyramid(0.5);
	glPopMatrix();

}
void p4Q3() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	glPushMatrix();
	glRotated(rangle, rx, ry, rz);
	glPushMatrix();
	glRotated(rangle2, rx2, ry2, rz2);
	glRotated(120, 1, 1, 1);
	drawWireCube(0.5,0.9);
	glPopMatrix();

	glPushMatrix();
	glRotated(rangle3, rx3, ry3, rz3);
	glRotated(120, 1, 1, 1);
	drawWireCube(0.5, -0.9);
	glPopMatrix();
	glPopMatrix();
}


void display()
{
	switch (qno)
	{
	case 9:
		p4Demo();
		break;
	case 1:
		p4Q1();
		break;
	case 2:
		p4Q2();
		break;
	case 3:
		p4Q3();
		break;
	default:
		p4Demo();
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
	wc.style = CS_HREDRAW | CS_VREDRAW; // horizontal and vertical (2d)

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		800, 10, 400, 400,
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