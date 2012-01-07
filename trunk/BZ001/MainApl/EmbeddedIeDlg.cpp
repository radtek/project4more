// EmbeddedIeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "EmbeddedIeDlg.h"
#include "GLB.h"

// CEmbeddedIeDlg �Ի���

IMPLEMENT_DYNAMIC(CEmbeddedIeDlg, CDialog)

CEmbeddedIeDlg::CEmbeddedIeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmbeddedIeDlg::IDD, pParent)
{

}

CEmbeddedIeDlg::~CEmbeddedIeDlg()
{
}

void CEmbeddedIeDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EMBEDDED_IE_BROWSER, mWebBrowser);
}


BEGIN_MESSAGE_MAP(CEmbeddedIeDlg, CDialog)
    ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CEmbeddedIeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEmbeddedIeDlg ��Ϣ�������

BOOL CEmbeddedIeDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

	int cxScreen = ::GetSystemMetrics(SM_CXSCREEN);//�����Ļ�� 
    int cyScreen = ::GetSystemMetrics(SM_CYSCREEN); //�����Ļ�� 
    int x = (cxScreen - 800)/2;  // ����λ��x����
    int y = (cyScreen - 600)/2;  // ����λ��y����
    int w = 800;    //���ڿ�Ϊ800 
    int h = 600;    //���ڸ�Ϊ600 

	//SetWindowPos(this->m_hWnd,HWND_BOTTOM,x,y,w,h,SWP_NOZORDER);
	SetWindowPos(this,x,y,w,h,SWP_NOZORDER);
	CenterWindow(this);

	//m_flag = FALSE;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	mWebBrowser.Navigate(url.c_str(), NULL, NULL, NULL, NULL);
	mWebBrowser.Invalidate(TRUE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void CEmbeddedIeDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: �ڴ˴������Ϣ����������
	// ���ݴ��ڴ�С���Զ�����IE�ؼ���С��
	CWnd* pCBtn= GetDlgItem(IDC_EMBEDDED_IE_BROWSER);
	if( pCBtn != NULL) {
		RECT rct;
		GetClientRect(&rct);

		pCBtn->MoveWindow(rct.left, rct.top, rct.right - rct.left, rct.bottom - rct.top);
	}
}
BEGIN_EVENTSINK_MAP(CEmbeddedIeDlg, CDialog)
	ON_EVENT(CEmbeddedIeDlg, IDC_EMBEDDED_IE_BROWSER, 259, CEmbeddedIeDlg::DocumentCompleteEmbeddedIeBrowser, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CEmbeddedIeDlg, IDC_EMBEDDED_IE_BROWSER, 273, CEmbeddedIeDlg::NewWindow3EmbeddedIeBrowser, VTS_PDISPATCH VTS_PBOOL VTS_UI4 VTS_BSTR VTS_BSTR)
END_EVENTSINK_MAP()

void CEmbeddedIeDlg::DocumentCompleteEmbeddedIeBrowser(LPDISPATCH pDisp, VARIANT* URL)
{
	// TODO: �ڴ˴������Ϣ����������
	if (m_flag)
	{
// 		CString strUrl;
// 		strUrl = URL->bstrVal;
// 		if (!strUrl.CompareNoCase("http://www.666156.com/fmp/menu.toIndex.action"))
// 		{
// 			GoTo("http://www.666156.com/fmp/user.toUserCenter.action?page=personaldata");
// 			m_flag = FALSE;
// 		}
	}

}
void CEmbeddedIeDlg::SetDrump(BOOL bflag,std::string strl)
{
	m_flag = bflag;
}
void CEmbeddedIeDlg::GoTo( CString url )
{
	try
	{
		mWebBrowser.Navigate2(&CComVariant(url),NULL,NULL,NULL,NULL);
	}
	catch (...)
	{
		GoTo(url);
	}
}
void CEmbeddedIeDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_flag)
	{
		DestroyWindow();
		m_flag = FALSE;
	}
	
	CDialog::OnClose();
}

void CEmbeddedIeDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();
}

void CEmbeddedIeDlg::NewWindow3EmbeddedIeBrowser(LPDISPATCH* ppDisp, BOOL* Cancel, unsigned long dwFlags, LPCTSTR bstrUrlContext, LPCTSTR bstrUrl)
{
	// TODO: �ڴ˴������Ϣ����������
	CString strUrl = bstrUrl;
	CString myUrl;
	myUrl = WEB_SERVICE_ADDRESS.c_str();
	myUrl += "/fmp/myaccount.toRecharge.action";
	if(!strUrl.CompareNoCase(myUrl))
	{
		*Cancel = VARIANT_TRUE;
		//blogin = false;
		mWebBrowser.Navigate2(&CComVariant(bstrUrl),NULL,NULL,NULL,NULL);
	}
}
