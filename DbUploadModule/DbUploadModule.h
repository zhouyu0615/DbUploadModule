
// DbUploadModule.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDbUploadModuleApp: 
// �йش����ʵ�֣������ DbUploadModule.cpp
//

class CDbUploadModuleApp : public CWinApp
{
public:
	CDbUploadModuleApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDbUploadModuleApp theApp;