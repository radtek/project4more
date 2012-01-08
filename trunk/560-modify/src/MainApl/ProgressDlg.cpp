// ProgressDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "ProgressDlg.h"


// CProgressDlg 对话框
HWND m_progress;
IMPLEMENT_DYNAMIC(CProgressDlg, CDialog)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{

}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_wndProgHorz);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CProgressDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CProgressDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CProgressDlg 消息处理程序

BOOL CProgressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_progress = m_hWnd;
	// TODO:  在此添加额外的初始化
	m_wndProgHorz.SetRange(0, 100);
	m_wndProgHorz.SetStep(1);
	m_wndProgHorz.SetPos(0);
	int piAlpha[5] = { 25, 50, 75, 100, 100 };
	m_wndProgHorz.SetMarquee(TRUE, 50, 2, 12, piAlpha);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CProgressDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
}

void CProgressDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnCancel();
}

void CProgressDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
