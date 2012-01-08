// PubSelectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "PubSelectDlg.h"


// CPubSelectDlg 对话框

IMPLEMENT_DYNAMIC(CPubSelectDlg, CDialog)

CPubSelectDlg::CPubSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPubSelectDlg::IDD, pParent)
    , selectValue(0)
{

}

CPubSelectDlg::~CPubSelectDlg()
{
}

void CPubSelectDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_PUB_SELECT_GOODS, selectValue);
}


BEGIN_MESSAGE_MAP(CPubSelectDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPubSelectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPubSelectDlg 消息处理程序

void CPubSelectDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
