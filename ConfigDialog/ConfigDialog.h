
// ConfigDialog.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CConfigDialogApp:
// �йش����ʵ�֣������ ConfigDialog.cpp
//

class CConfigDialogApp : public CWinApp
{
public:
	CConfigDialogApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CConfigDialogApp theApp;