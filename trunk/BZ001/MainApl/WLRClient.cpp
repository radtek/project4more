// WLRClient.cpp : ����Ӧ�ó��������Ϊ��
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


// CWLRClientApp ����

CWLRClientApp::CWLRClientApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CWLRClientApp ����

CWLRClientApp theApp;


// CWLRClientApp ��ʼ��

BOOL CWLRClientApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	

    /*
	//ȫ�ֱ�����д-�����ļ���д
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
        //����WEB_SERVICE_ADDRESS
		if ( strlen(fmp_home) > 0 )
		{
			//global_web_service_home=string(fmp_home);
		}
	}*/

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CWLRClientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}   

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
