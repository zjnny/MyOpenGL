#include "stdafx.h"
#include "GLWnd.h"

#include <GL/GL.h>
#include <GL/GLU.h>
//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "glu32.lib")
CGLWnd::CGLWnd(void)
{
	m_isLDown=false;
	m_scale=1.0f;
}


CGLWnd::~CGLWnd(void)
{
	wglMakeCurrent(NULL,NULL);
	wglDeleteContext(m_RC);
	m_RC = NULL;
}
BEGIN_MESSAGE_MAP(CGLWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_TIMER()
//	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


int CGLWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	//SetTimer(1,100,NULL);
		// TODO:  在此添加您专用的创建代码
	InitOpenGl();
	
	return 0;
}


BOOL CGLWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	//return CWnd::OnEraseBkgnd(pDC);
}


void CGLWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_isLDown=true;
	CWnd::OnLButtonDown(nFlags, point);
}


void CGLWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_isLDown=false;
	CWnd::OnLButtonUp(nFlags, point);
}


void CGLWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_isLDown)
	{
		m_cam.roll(0.1f);
		//m_cam.pitch(0.1f);
		//m_cam.slide(0.1f,0.1f,0.1f);
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CGLWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(rect);
	
	//dc.FillRect(rect,CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	Render();

	//注意在OnPaint中使用Render图像静止，并且如果父窗口没有设置ClipChildren（被父窗口背景覆盖），
	//Erasebackground（闪烁严重）
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CWnd::OnPaint()
}


void CGLWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	glViewport(0, 0, cx, cy);//根据窗口大小
	
	//glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	//glLoadIdentity();						// reset projection matrix
	//
	m_cam.setShape(45.0f,(GLfloat)cx/(GLfloat)cy,1.0f,1000.0f);
	//// calculate perspective
	//gluPerspective(45.0f,(GLfloat)cx/(GLfloat)cy,1.0f,1000.0f);

	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();
	
	Invalidate();
	// TODO: 在此处添加消息处理程序代码
}


BOOL CGLWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	//父窗口必须要设置WS_CLIPCHILDREN防止闪烁，当前窗口设置没有意义（除非有子窗口）
	//cs.style|=WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	cs.style &= ~WS_BORDER;
	/*cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
	::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);*/
	//清除背景画刷，防止闪烁
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}
void CGLWnd::InitOpenGl()
{
	HDC hDC = GetDC()->m_hDC;
	GLuint PixelFormat;
	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		ASSERT(0&&"ChoosePixelFormat");
		return ;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))
	{
		ASSERT(0&&"SetPixelFormat");
		return ;
	}

	m_RC = wglCreateContext(hDC);

	if(!wglMakeCurrent(hDC, m_RC))
	{
		ASSERT(0&&"wglMakeCurrent");
		return ;
	}

	glClearColor(0.0, 0.0, 0.0, 0.0);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);
	//glDepthFunc(GL_LEQUAL);
	glViewport(0, 0, 100, 100);//根据窗口大小
	// select the projection matrix and clear it out
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// select modelview matrix and clear it out
	//glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 1000.0);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glClearDepth(1.0f);
	m_terrain.Init(260,260);
	//m_cam.setCamera(0.0f,10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}
void CGLWnd::Render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     
	glLoadIdentity();
	//垂直向下看eyey=centery
	/*gluLookAt(50.0,100.0, 150, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	static float angle=0.0f;
	angle+=1.5f;
	glRotatef(angle,0.0f,1.0f,0.0f);*/
	m_cam.setCamera(50.0,100.0, 150, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	////glDrawPixels

	//glBegin(GL_TRIANGLES);
	//glVertex3f(x,-x,0.0f);
	//glVertex3f(-x,-x,0.0f);
	//glVertex3f(0.0,x,0.0f);
	//glEnd();
	m_terrain.DrawTerrain();
	//m_terrain.DrawTerrainNet();
	SwapBuffers(GetDC()->GetSafeHdc());
}

void CGLWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}


//void CGLWnd::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	// 此功能要求 Windows Vista 或更高版本。
//	// _WIN32_WINNT 符号必须 >= 0x0600。
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	
//	CWnd::OnMouseHWheel(nFlags, zDelta, pt);
//}


BOOL CGLWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(zDelta<=0)
	{
	case true:
		m_scale+=zDelta/120;
		if(m_scale<=0.2f)
			m_scale=0.2f;
		m_terrain.SetScale(m_scale);
		Invalidate();
		break;
	case false:
		m_scale+=zDelta/120;
		if(m_scale>=10.0f)
			m_scale=10.0f;
		m_terrain.SetScale(m_scale);
		Invalidate();
		break;
	}
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}
