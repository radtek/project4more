// PubSelectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "PubSelectDlg.h"


// CPubSelectDlg �Ի���

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


// CPubSelectDlg ��Ϣ�������

void CPubSelectDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
