#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#define WINDOW_TITLE "P2 Demo"
float tx = 0, ty = 0, tSpeed = 0.1; // translation Tx, Ty
float rx = 0; // rotation Rx
float r = 1, g = 1, b = 1; //rgb color
float r2 = 1, g1 = 0.9, g2 = 0.8, b2 = 0; //rgb color Q2
int qno = 0; // question no
int i = 0;

//transition: Tx right (+) left (-); Ty up (+) down (-) ; Tz forward (+) backward (-); glTranslatef(Tx,Ty,Tz)
//rotation: x'= x cos q - y sin q ; y'= x sin q + y cos q; glRotatef(angle,x, y, z); anti-clockwise(+), clockwise(-)
//scale: Original size (1.0); half (0.5); sclae value > 0; glScale(Sx, Sy, Sz)

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
		else if (wParam == 0x33)// press key '3'
			qno = 3;
		else if (wParam == 0x34)// press key '4'
			qno = 4;
		else if (wParam == VK_LEFT) {//VK_LEFT = Left key
			tx -= tSpeed; 
			rx += 0.2;
		}

		else if (wParam == VK_RIGHT) {//VK_RIGHT = Right key
			tx += tSpeed; 
			rx -= 0.2;
		}
			
		else if (wParam == VK_DOWN) //VK_DOWN = Down key
			ty -= tSpeed; 
		else if (wParam == VK_UP)//VK_UP = UP key
			ty += tSpeed; 
		else if (wParam == 0x52) { // press key 'R'
			r = 1;
			g = 0;
			b = 0;
		}
		else if (wParam == 0x47) { // presss key 'G'
			r = 0;
			g = 1;
			b = 0;
		}
		else if (wParam == 0x42) { // presss key 'B'
			r = 0;
			g = 0;
			b = 1;
		}
		else if (wParam == VK_SPACE) { // presss space key
			r = 1;
			g = 1;
			b = 1;
			r2 = 1;
			g1 = 0.9;
			g2 = 0.8;
			b2 = 0;
			tx = 0;
			ty = 0;
			rx = 0;
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

void p2Demo() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity(); // Reset the transformation, make it stop moving
	glTranslatef(-0.5, 0.5, 0.0); //Tx = -0.5, Ty = 0.5
	glRotatef(90, 0.0, 0.0, 1.0); // Rz(90), anti-clockwise
	glScalef(0.5, 0.5, 0.5); //Sx(0.5), Sy(0.5), half

	glBegin(GL_TRIANGLES); // object 1
	glVertex2f(-0.5, 0.0);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();

	glLoadIdentity(); // Reset the transformation, so it won't be affected by the transformation
	glScalef(0.5, 0.5, 0.5); //Sx(0.5), Sy(0.5), half
	glBegin(GL_QUADS); //object 2
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
}

void p2Q1() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity(); // Reset the transformation, make it stop moving
	glTranslatef(tx, ty, 0.0); //Tx, Ty

	glBegin(GL_TRIANGLES); // object 
	glColor3f(r, g, b);
	glVertex2f(-0.5, 0.0);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
}

void colorChange() {
	if (r2 >= 0 && i == 0) {
		if (r2 < 1) {
			r2 += 0.01;
			b2 -= 0.01;
		}
		else {
			i++;
			r2 -= 0.01;
			b2 += 0.01;
		}
	}
	else if (r2 > 0 && i == 1) {
		r2 -= 0.01;
		b2 += 0.01;
	}
	else if (r2 <= 0) {
		r2 += 0.01;
		b2 -= 0.01;
		i--;
	}


}

void p2Q2() {
	
	glClear(GL_COLOR_BUFFER_BIT);

	if (!(GetKeyState(VK_SPACE) & 0x8000)) {
		colorChange();
	}
	
	//double d = 1.732; //triangle midpoint multiplier (midpoint height = sqrt(3) * length AB/2)
	//double l = 0.2; //length of the triangle
	

	//glBegin(GL_TRIANGLES); // middle triangle (left and right point)
	//glColor3f(1, 1, 1);
	//glVertex2f(-0.5, 0.25); 
	//glVertex2f(0.5, 0.25); 
	//glVertex2f(0.0, 0.0); //midpoint
	//glEnd();

	//glBegin(GL_TRIANGLES); // left triangle (middle and bottom left point)
	//glColor3f(1, 1, 1);
	//glVertex2f(0.0, 0.0);
	//glVertex2f(0.0, 0.5); 
	//glVertex2f(-0.35,-0.25);
	//glEnd();

	//glBegin(GL_TRIANGLES); // right triangle (middle and bottom right point)
	//glColor3f(1, 1, 1);
	//glVertex2f(0.0, 0.0);
	//glVertex2f(0.0, 0.5);
	//glVertex2f(0.35, -0.25);
	//glEnd();

	//glBegin(GL_TRIANGLES); // small middle triangle (left and right point)
	//glColor3f(1, 0, 0);
	//glVertex2f(-0.2, 0.1);
	//glVertex2f(0.2, 0.1);
	//glVertex2f(0.0, 0.0); //midpoint
	//glEnd();

	//glBegin(GL_QUADS); // quad (center)
	//glColor3f(0, 1, 0);
	//glVertex2f(-0.2, 0.1);
	//glVertex2f(0.2, 0.1);
	//glVertex2f(0.12, 0.25);
	//glVertex2f(-0.12, 0.25);
	//glEnd();

	//glPointSize(2.0);
	//glBegin(GL_POINTS); // center point
	//glColor3f(0, 0, 1);
	//glVertex2f(0.0, 0.175); //midpoint
	//glEnd();

	glRotatef(rx,0,0,1);
	glBegin(GL_TRIANGLES); // small triangle (left top)
	glColor3f(r2, g2, b2);
	glVertex2f(0.0, 0.175); // midpoint
	glVertex2f(-0.5, 0.25);
	glVertex2f(0.0, 0.25);
	glEnd();

	glBegin(GL_TRIANGLES); // small triangle (left bottom)
	glColor3f(r2, g1, b2);
	glVertex2f(0.0, 0.175); // midpoint
	glVertex2f(-0.5, 0.25);
	glVertex2f(-0.2, 0.1);
	glEnd();

	glBegin(GL_TRIANGLES); // small triangle (top left)
	glColor3f(r2, g1, b2);
	glVertex2f(0.0, 0.175); // midpoint
	glVertex2f(-0.12, 0.25);
	glVertex2f(0.0, 0.5);
	glEnd();

	glBegin(GL_TRIANGLES); // small triangle (right top)
	glColor3f(r2, g1, b2);
	glVertex2f(0.0, 0.175); // midpoint
	glVertex2f(0.5, 0.25);
	glVertex2f(0.0, 0.25);
	glEnd();

	glBegin(GL_TRIANGLES); // small triangle (right bottom)
	glColor3f(r2, g2, b2);
	glVertex2f(0.0, 0.175); // midpoint
	glVertex2f(0.5, 0.25);
	glVertex2f(0.2, 0.1);
	glEnd();

	glBegin(GL_TRIANGLES); // small middle triangle (top right)
	glColor3f(r2, g2, b2);
	glVertex2f(0.0, 0.175); // midpoint
	glVertex2f(0.12, 0.25);
	glVertex2f(0.0, 0.5);
	glEnd();

	glBegin(GL_TRIANGLES); // small triangle (bottom left-left)
	glColor3f(r2, g2, b2);
	glVertex2f(0.0, 0.175); // midpoint
	glVertex2f(-0.35, -0.25);
	glVertex2f(-0.2, 0.1);
	glEnd();

	glBegin(GL_TRIANGLES); // small triangle (bottom left-right)
	glColor3f(r2, g1, b2);
	glVertex2f(0.0, 0.175); // midpoint
	glVertex2f(-0.35, -0.25);
	glVertex2f(0.0,0.0);
	glEnd();

	glBegin(GL_TRIANGLES); // small triangle (bottom right-left)
	glColor3f(r2, g1, b2);
	glVertex2f(0.0, 0.175); // midpoint
	glVertex2f(0.35, -0.25);
	glVertex2f(0.2, 0.1);
	glEnd();

	glBegin(GL_TRIANGLES); // small triangle (bottom right-right)
	glColor3f(r2, g2, b2);
	glVertex2f(0.0, 0.175); // midpoint
	glVertex2f(0.35, -0.25);
	glVertex2f(0.0, 0.0);
	glEnd();


}

void p2Q3() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glRotatef(0.2, 0, 0, 1);
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex2f(0.0,-0.5);
	glEnd();

}

void p2Q4() {
	glClear(GL_COLOR_BUFFER_BIT);
	glScalef(1.1, 1.1, 0);
	glTranslatef(-0.0005, 0.0005, 0);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.5, 0.0);
	glVertex2f(0.5, -0.5);
	glVertex2f(0.0, -0.5);
	glEnd();

}
void display()
{
	switch (qno)
	{
	case 9:
		p2Demo();
		break;
	case 1:
		p2Q1();
		break;
	case 2:
		p2Q2();
		break;
	case 3:
		p2Q3();
		break;
	case 4:
		p2Q4();
		break;
	default:
		p2Q1();
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