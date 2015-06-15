
// ChildView.h : CGlView 类的接口
//


#pragma once


// CGlView 窗口
#include "GLWnd.h"
class CGlView : public CWnd
{
// 构造
public:
	CGlView();

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CGlView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
private:
	CGLWnd m_wnd;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

