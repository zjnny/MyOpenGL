
// ChildView.h : CGlView ��Ľӿ�
//


#pragma once


// CGlView ����
#include "GLWnd.h"
class CGlView : public CWnd
{
// ����
public:
	CGlView();

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CGlView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
private:
	CGLWnd m_wnd;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

