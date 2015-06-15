
// ChildView.cpp : CGlView ���ʵ��
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



// CGlView ��Ϣ�������

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
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	
	// TODO: �ڴ˴������Ϣ����������
	
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
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
		// TODO:  �ڴ������ר�õĴ�������
	return 0;
}


void CGlView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	CRect rt;
	GetClientRect(rt);
	m_wnd.MoveWindow(rt);
	// TODO: �ڴ˴������Ϣ����������
}
