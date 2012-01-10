// ContentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ContentDlg.h"


// CContentDlg dialog

IMPLEMENT_DYNAMIC(CContentDlg, CDialog)

CContentDlg::CContentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CContentDlg::IDD, pParent)
{

}

CContentDlg::~CContentDlg()
{
}

void CContentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CContentDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CContentDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CContentDlg message handlers

void CContentDlg::OnBnClickedButtonClose()
{
	CDialog::OnOK();
}
