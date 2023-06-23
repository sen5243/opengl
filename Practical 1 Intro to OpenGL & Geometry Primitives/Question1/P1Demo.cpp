#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#define WINDOW_TITLE "P1 Demo"
int qno = 1;
float angle = 0; // angle
float x2 = 0, y2 = 0; // point on circle (x2,y2)
float PI = 3.1429; // PI

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY: //when click on x button
		PostQuitMessage(0); //quit function
		break;

	case WM_KEYDOWN: // for pressing key
		if (wParam == VK_ESCAPE) PostQuitMessage(0); //VK_Escape = Esc key
		else if (wParam == 0x31) // press key '1'
			qno = 1;
		else if (wParam == 0x32)// press key '2'
			qno = 2;
		else if (wParam == 0x33)// press key '3'
			qno = 3;
		else if (wParam == 0x34)// press key '4'
			qno = 4;
		else if (wParam == 0x35)// press key '5'
			qno = 5;
		else if (wParam == 0x36)// press key '6'
			qno = 6;
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
void drawOutline() 
{
	glBegin(GL_LINE_LOOP);  //Outline
	glColor3f(0.0, 0.4, 0.74);
	glVertex2f(-0.9, -0.5); //p1
	glVertex2f(-0.9, 0.5); //p1	
	glVertex2f(0.9, 0.5); //p2	
	glVertex2f(0.9, -0.5);  //p3
	glEnd();
}
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


void drawBottomHalfCircle(float x, float y, float radius, float triNum, float r, float g, float b) {

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(r, g, b);
	glVertex2f(x, y); // origin of circle (x,y) = (0,0)
	// upper half circle:  0 to PI, bottom half circle : PI to 2PI, window resolution not same will become oval
	for (angle = PI; angle <= (2 * PI); angle += (2 * PI) / triNum) {
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}

	glEnd();
}

void pahangFlag()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // change background color, rgba
	glClear(GL_COLOR_BUFFER_BIT); // screen clear, clear the color buffer
	glLineWidth(1.0);

	glBegin(GL_QUADS);  //Upper rec
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.9, 0.0); //p1
	glVertex2f(-0.9, 0.5); //p1	
	glVertex2f(0.9, 0.5); //p2	
	glVertex2f(0.9, 0.0);  //p3
	glEnd();

	glBegin(GL_QUADS);  //Bottom rec
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.9, -0.5); //p1
	glVertex2f(-0.9, 0.0); //p1	
	glVertex2f(0.9, 0.0); //p2	
	glVertex2f(0.9, -0.5);  //p3
	glEnd();

	drawOutline();
}

void n9flag()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // change background color, rgba
	glClear(GL_COLOR_BUFFER_BIT); // screen clear, clear the color buffer
	glLineWidth(1.0);

	glBegin(GL_QUADS);  //Yellow flag
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-0.9, 0.5); //p1
	glVertex2f(-0.9, -0.5); //p2	
	glVertex2f(0.9, -0.5); //p3
	glVertex2f(0.9, 0.5);  //p4
	glEnd();

	glBegin(GL_TRIANGLES);  //Black triangle
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.9, 0.5); //p1
	glVertex2f(-0.9, 0.0); //p2	
	glVertex2f(0.0, 0.0);  //p3
	glEnd();

	glBegin(GL_TRIANGLES);  //Red triangle
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.0, 0.5); //p1
	glVertex2f(0.0, 0.0); //p2	
	glVertex2f(-0.9, 0.5);  //p3
	glEnd();
}

void englandFlag()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // change background color, rgba
	glClear(GL_COLOR_BUFFER_BIT); // screen clear, clear the color buffer
	glLineWidth(1.0);

	glBegin(GL_QUADS);  //White flag bottom left
	glColor3f(1.0, 1.0, 1.0); // white point
	glVertex2f(-0.9, 0.0); //p1
	glColor3f(0.7, 0.7, 0.7); //black point
	glVertex2f(-0.9, -0.5); //p2	
	glColor3f(1.0, 1.0, 1.0); // white point
	glVertex2f(0.0, -0.5); //p3
	glColor3f(1.0, 1.0, 1.0); // white point
	glVertex2f(0.0, 0.0);  //p4
	glEnd();

	glBegin(GL_QUADS);  //White flag top left
	glColor3f(0.7, 0.7, 0.7); //black point
	glVertex2f(-0.9, 0.5); //p1
	glColor3f(1.0, 1.0, 1.0); // white point
	glVertex2f(-0.9, 0.0); //p2	
	glColor3f(1.0, 1.0, 1.0); // white point
	glVertex2f(0.0, 0.0); //p3
	glColor3f(1.0, 1.0, 1.0); // white point
	glVertex2f(0.0, 0.5);  //p4
	glEnd();

	glBegin(GL_QUADS);  //White flag bottom right
	glColor3f(1.0, 1.0, 1.0); // white point
	glVertex2f(0.9, 0.0); //p1
	glColor3f(0.7, 0.7, 0.7); //black point
	glVertex2f(0.9, -0.5); //p2	
	glColor3f(1.0, 1.0, 1.0); // white point
	glVertex2f(0.0, -0.5); //p3
	glColor3f(1.0, 1.0, 1.0); // white point
	glVertex2f(0.0, 0.0);  //p4
	glEnd();

	glBegin(GL_QUADS);  //White flag top right
	glColor3f(0.7, 0.7, 0.7); //black point
	glVertex2f(0.9, 0.5); //p1
	glColor3f(1.0, 1.0, 1.0); // white point
	glVertex2f(0.9, 0.0); //p2	
	glColor3f(1.0, 1.0, 1.0); // white point
	glVertex2f(0.0, 0.0); //p3
	glColor3f(1.0, 1.0, 1.0); // white point
	glVertex2f(0.0, 0.5);  //p4
	glEnd();

	glBegin(GL_QUADS);  //+ at the middle
	glColor3f(0.6, 0.0, 0.0); //red 

	//horizontal rectangle
	glVertex2f(-0.9, 0.1); //p1
	glVertex2f(-0.9, -0.1); //p2
	glVertex2f(0.9, -0.1); //p3
	glVertex2f(0.9, 0.1);  //p4

	//vertical rectangle
	glVertex2f(-0.1, -0.5);  //p5
	glVertex2f(0.1, -0.5);  //p6
	glVertex2f(0.1, 0.5);  //p7
	glVertex2f(-0.1, 0.5);  //p8

	glEnd();

}

void scotlandFlag()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // change background color, rgba
	glClear(GL_COLOR_BUFFER_BIT); // screen clear, clear the color buffer
	glLineWidth(1.0);

	glBegin(GL_LINE_LOOP);  // blue outline
	glColor3f(0.0, 0.4, 0.74);
	glVertex2f(-0.91, 0.51); //p1
	glVertex2f(-0.91, -0.51); //p2	
	glVertex2f(0.91, -0.51); //p3
	glVertex2f(0.91, 0.51);  //p4
	glEnd();

	glBegin(GL_QUADS);  //white flag
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.9, 0.5); //p1
	glVertex2f(-0.9, -0.5); //p2	
	glVertex2f(0.9, -0.5); //p3
	glVertex2f(0.9, 0.5);  //p4
	glEnd();

	glBegin(GL_TRIANGLES);  // left triangle
	glColor3f(0.0, 0.4, 0.74);
	glVertex2f(-0.9, 0.35); //p1
	glVertex2f(-0.9, -0.35); //p2	
	glVertex2f(-0.25, 0.0); //p3
	glEnd();

	glBegin(GL_TRIANGLES);  // bottom triangle
	glColor3f(0.0, 0.4, 0.74);
	glVertex2f(-0.7, -0.5); //p1
	glVertex2f(0.7, -0.5); //p2	
	glVertex2f(0.0, -0.1); //p3
	glEnd();

	glBegin(GL_TRIANGLES);  // right triangle
	glColor3f(0.0, 0.4, 0.74);
	glVertex2f(0.9, 0.35); //p1
	glVertex2f(0.9, -0.35); //p2	
	glVertex2f(0.25, 0.0); //p3
	glEnd();

	glBegin(GL_TRIANGLES);  // top triangle
	glColor3f(0.0, 0.4, 0.74);
	glVertex2f(-0.7, 0.5); //p1
	glVertex2f(0.7, 0.5); //p2	
	glVertex2f(0.0, 0.1); //p3
	glEnd();
}

void japanFlag() 
{
	/*To draw a circle
		origin of circle (x,y)
		radius = 1
		angle (delta,point of the circle) (x2,y2)
		x2 = x + r * cos * delta
		y2 = y + r * sin * delta
		perimeter = 2 * pi (3.1429) * r 
		
		two type  of circle : line (GL_POINTS and GL_LINE_LOOP) and filled (GL_POLYGON, GL_TRIANGLE and GL_TRIANGLE_FAN)
		more triangle more smooth, delta need to be small
	*/

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // clear background color with black, rgba
	glClear(GL_COLOR_BUFFER_BIT); // screen clear, clear the color buffer
	glLineWidth(1.0);

	glBegin(GL_QUADS);  //white flag
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.9, 0.5); //p1
	glVertex2f(-0.9, -0.5); //p2	
	glVertex2f(0.9, -0.5); //p3
	glVertex2f(0.9, 0.5);  //p4
	glEnd();

	drawCircle(0, 0, 0.3, 30,1.0,0.0,0.0);

}

void face() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // change background color, rgba
	glClear(GL_COLOR_BUFFER_BIT); // screen clear, clear the color buffer
	glLineWidth(1.0);

	
	drawCircle(-0.5, 0.4, 0.2, 30, 0.94, 0.925, 0.87); //left ear
	drawCircle(-0.5, 0.4, 0.15, 30, 0, 0, 0); //left ear 2
	drawCircle(0.5, 0.4, 0.2, 30, 0.94, 0.925, 0.87);//right ear
	drawCircle(0.5, 0.4, 0.15, 30, 0, 0, 0 );//right ear 2


	drawCircle(0, 0, 0.6, 30, 0.94, 0.925, 0.87); //main face
	drawCircle(0.0, 0.0, 0.1, 30, 0, 0, 0); // nose
	drawBottomHalfCircle(0.0, -0.2, 0.25, 30, 1.0, 0.4, 0.4); // mouth

	//crown
	glBegin(GL_QUADS);  //rect
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-0.3, 0.6); //p1
	glVertex2f(-0.3, 0.5); //p1	
	glVertex2f(0.3, 0.5); //p2	
	glVertex2f(0.3, 0.6);  //p3
	glEnd();

	glBegin(GL_TRIANGLES);  // left triangle
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-0.25, 0.9); //p1
	glVertex2f(-0.3, 0.6); //p2	
	glVertex2f(-0.2, 0.6); //p3
	glEnd();

	glBegin(GL_TRIANGLES);  // middle triangle
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0.0, 0.9); //p1
	glVertex2f(-0.05, 0.6); //p2	
	glVertex2f(0.05, 0.6); //p3
	glEnd();

	glBegin(GL_TRIANGLES);  // right triangle
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0.25, 0.9); //p1
	glVertex2f(0.3, 0.6); //p2	
	glVertex2f(0.2, 0.6); //p3
	glEnd();

	drawCircle(0.0, 0.55, 0.05, 30, 1, 0, 0); //gem

	glBegin(GL_QUADS);  //left eye
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.3, 0.2); //p1
	glVertex2f(-0.3, 0.1); //p1	
	glVertex2f(-0.25, 0.1); //p2	
	glVertex2f(-0.25, 0.2);  //p3
	glEnd();

	glBegin(GL_QUADS);  //right eye
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.3, 0.2); //p1
	glVertex2f(0.3, 0.1); //p1	
	glVertex2f(0.25, 0.1); //p2	
	glVertex2f(0.25, 0.2);  //p3
	glEnd();
	
}
void display()
{
	switch (qno) {
	case 1:
		pahangFlag();
		break;
	case 2:
		n9flag();
		break;
	case 3:
		englandFlag();
		break;
	case 4:
		scotlandFlag();
		break;
	case 5:
		japanFlag();
		break;
	case 6:
		face();
		break;
	default:
		pahangFlag();
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
		CW_USEDEFAULT, CW_USEDEFAULT, 400, 400,
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


