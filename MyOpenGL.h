
// MyOpenGL.h : MyOpenGL Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMyGLApp:
// �йش����ʵ�֣������ MyOpenGL.cpp
//

class CMyGLApp : public CWinApp
{
public:
	CMyGLApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyGLApp theApp;
