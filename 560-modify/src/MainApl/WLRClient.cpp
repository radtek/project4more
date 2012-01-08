// WLRClient.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "WLRClient.h"
#include "WLRClientDlg.h"
//#include "MyLib.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWLRClientApp

BEGIN_MESSAGE_MAP(CWLRClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWLRClientApp 构造

CWLRClientApp::CWLRClientApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CWLRClientApp 对象

CWLRClientApp theApp;


// CWLRClientApp 初始化

BOOL CWLRClientApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	

    /*
	//全局变量读写-配置文件读写
	#define MAX_SIZE 256
	TCHAR app_home[MAX_SIZE];

	VERIFY(::GetModuleFileName(	AfxGetApp()->m_hInstance, app_home, MAX_SIZE));		

	CString cs_app_home(app_home);
	int nIndex  = cs_app_home.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		cs_app_home = cs_app_home.Left(nIndex);
	}
	else {
		cs_app_home.Empty();
	}
	cs_app_home +="/main_app.config";

	FILE *fp = fopen(cs_app_home.GetBuffer(),"r");
	if(NULL != fp )
	{
		char fmp_home[256];
		int i = 0;
		int c;
		memset(fmp_home,0,sizeof(fmp_home));
		while ( (c = fgetc(fp)) != EOF && i<MAX_SIZE )
		{
			fmp_home[i++]=c;
		}

		//AfxMessageBox(fmp_home);
        //更新WEB_SERVICE_ADDRESS
		if ( strlen(fmp_home) > 0 )
		{
			//global_web_service_home=string(fmp_home);
		}
	}*/

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CWLRClientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此处放置处理何时用“确定”来关闭
		//  对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用“取消”来关闭
		//  对话框的代码
	}   

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
