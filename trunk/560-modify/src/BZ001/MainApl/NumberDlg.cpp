// NumberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NumberDlg.h"


// CNumberDlg dialog

IMPLEMENT_DYNAMIC(CNumberDlg, CDialog)

CNumberDlg::CNumberDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNumberDlg::IDD, pParent)
{

}

CNumberDlg::~CNumberDlg()
{
}

void CNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNumberDlg, CDialog)
END_MESSAGE_MAP()


// CNumberDlg message handlers
