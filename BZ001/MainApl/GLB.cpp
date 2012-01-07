#include "StdAfx.h"
#include "GLB.h"
#include "header.h"
GLB::GLB(void)
{
}

GLB::~GLB(void)
{
}




// 主对话框背景色
unsigned long GLB::mainDlgBgColor = 0;

// TAB控件背景色
unsigned long GLB::tabCtrlBgColor = 0;
    
// 滚动条文字色
unsigned long GLB::scrollBarFgColor = 0;
// 滚动条背景色
unsigned long GLB::scrollBarBgColor = 0;

// 是否最小化标志
bool GLB::ifMiniSize = false;

static CString GetStylesPath(void);

void OnShemaChanged(int nSchema)
{
	switch (nSchema)
	{
	case 0:
		XTPSkinManager()->LoadSkin(GetStylesPath() + _T("Office2007.cjstyles"), _T("NormalBlue.INI"));
		break;
	case 1:
		XTPSkinManager()->LoadSkin(GetStylesPath() + _T("Vista.cjstyles"), _T("NormalBlue.INI"));
		break;
    }
}

static CString GetStylesPath(void)
{
	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		

	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else {
		csStylesPath.Empty();
	}

	return csStylesPath + _T("\\Styles\\");
}

void SuspendMyThread()
{
	SuspendThread(hThread);
}
void ResumeMyThread()
{
	DWORD dip = 0;
	if (hThread != NULL)
	{
		while(1)
		{
			dip = ResumeThread(hThread);
			if (dip == 0)
			{
				break;
			}
			Sleep(100);
		}
	}
}
bool greatermark(const   CustomZoneInf&   s1,const   CustomZoneInf&   s2) 
{   
	return   atoi(s1.id.c_str())   >   atoi(s2.id.c_str());   
}
