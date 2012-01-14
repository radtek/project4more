// SearchFavRenameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SearchFavRenameDlg.h"


// CSearchFavRenameDlg �Ի���

IMPLEMENT_DYNAMIC(CSearchFavRenameDlg, CDialog)

CSearchFavRenameDlg::CSearchFavRenameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchFavRenameDlg::IDD, pParent)
	, m_sNewName(_T(""))
{

}

CSearchFavRenameDlg::~CSearchFavRenameDlg()
{
}

void CSearchFavRenameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FAVORITE_NAME, m_sNewName);
}


BEGIN_MESSAGE_MAP(CSearchFavRenameDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSearchFavRenameDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSearchFavRenameDlg ��Ϣ�������

void CSearchFavRenameDlg::OnBnClickedOk()
{
	UpdateData();
	OnOK();
}
