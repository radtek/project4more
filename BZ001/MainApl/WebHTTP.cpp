// WebHTTP.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "WebHTTP.h"
#include "GLB.h"

// CWebHTTP 对话框

IMPLEMENT_DYNAMIC(CWebHTTP, CDialog)

CWebHTTP::CWebHTTP(CWnd* pParent /*=NULL*/)
	: CDialog(CWebHTTP::IDD, pParent)
{

}

CWebHTTP::~CWebHTTP()
{
}

void CWebHTTP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, mWebBrowser);
}


BEGIN_MESSAGE_MAP(CWebHTTP, CDialog)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CWebHTTP::OnBnClickedOk)
END_MESSAGE_MAP()


// CWebHTTP 消息处理程序

BOOL CWebHTTP::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CWebHTTP::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	CWnd* pCBtn= GetDlgItem(IDC_EXPLORER1);
	if( pCBtn != NULL) {
		RECT rct;
		GetClientRect(&rct);

		pCBtn->MoveWindow(rct.left, rct.top, rct.right - rct.left, rct.bottom - rct.top);
	}
	// TODO: 在此处添加消息处理程序代码
}

void CWebHTTP::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DestroyWindow();
	CDialog::OnClose();
}

void CWebHTTP::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
}
