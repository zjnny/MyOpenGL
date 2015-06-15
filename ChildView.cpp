
// ChildView.cpp : CGlView 类的实现
//

#include "stdafx.h"
#include "MyOpenGL.h"
#include "ChildView.h"
#include "GlWnd.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGlView

CGlView::CGlView()
{
}

CGlView::~CGlView()
{
}


BEGIN_MESSAGE_MAP(CGlView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CGlView 消息处理程序

BOOL CGlView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style|=WS_CLIPCHILDREN;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CGlView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
}



int CGlView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rt;
	GetClientRect(rt);
	m_wnd.Create(_T("MyGL"),_T("MyGL"),WS_VISIBLE|WS_CHILD,CRect(0,0,100,100),this,111);
	m_wnd.SetFocus();
	//m_wnd.ShowWindow(SW_SHOW);
		// TODO:  在此添加您专用的创建代码
	return 0;
}


void CGlView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	CRect rt;
	GetClientRect(rt);
	m_wnd.MoveWindow(rt);
	// TODO: 在此处添加消息处理程序代码
}
