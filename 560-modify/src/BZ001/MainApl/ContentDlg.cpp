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
END_MESSAGE_MAP()


// CContentDlg message handlers
