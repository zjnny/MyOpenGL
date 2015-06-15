#pragma once
#include "afxwin.h"
#include "GLTerrain.h"
#include "GLCamera.h"
class CGLWnd :
	public CWnd
{
public:
	CGLWnd(void);
	~CGLWnd(void);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
protected:
	void InitOpenGl();
	void Render();
private:
	HGLRC m_RC;
	GLTerrain m_terrain;
	GLCamera m_cam;
	CPoint m_lastPt;
	bool m_isLDown;
	float m_scale;

};

