// WLRClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWLRClientApp:
// �йش����ʵ�֣������ WLRClient.cpp
//

class CWLRClientApp : public CWinApp
{
public:
	CWLRClientApp();
	//CMemoryState m_msOld, m_msNew, m_msDiff;
// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWLRClientApp theApp;