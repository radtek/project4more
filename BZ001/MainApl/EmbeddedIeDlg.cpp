// EmbeddedIeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "EmbeddedIeDlg.h"
#include "GLB.h"

// CEmbeddedIeDlg 对话框

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


// CEmbeddedIeDlg 消息处理程序

BOOL CEmbeddedIeDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

	int cxScreen = ::GetSystemMetrics(SM_CXSCREEN);//获得屏幕宽 
    int cyScreen = ::GetSystemMetrics(SM_CYSCREEN); //获得屏幕高 
    int x = (cxScreen - 800)/2;  // 窗口位置x居中
    int y = (cyScreen - 600)/2;  // 窗口位置y居中
    int w = 800;    //窗口宽为800 
    int h = 600;    //窗口高为600 

	//SetWindowPos(this->m_hWnd,HWND_BOTTOM,x,y,w,h,SWP_NOZORDER);
	SetWindowPos(this,x,y,w,h,SWP_NOZORDER);
	CenterWindow(this);

	//m_flag = FALSE;
	// TODO:  在此添加额外的初始化
	mWebBrowser.Navigate(url.c_str(), NULL, NULL, NULL, NULL);
	mWebBrowser.Invalidate(TRUE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CEmbeddedIeDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
	// 根据窗口大小，自动缩放IE控件大小。
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
	// TODO: 在此处添加消息处理程序代码
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_flag)
	{
		DestroyWindow();
		m_flag = FALSE;
	}
	
	CDialog::OnClose();
}

void CEmbeddedIeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
}

void CEmbeddedIeDlg::NewWindow3EmbeddedIeBrowser(LPDISPATCH* ppDisp, BOOL* Cancel, unsigned long dwFlags, LPCTSTR bstrUrlContext, LPCTSTR bstrUrl)
{
	// TODO: 在此处添加消息处理程序代码
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
