// SearchSelectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WLRClient.h"
#include "SearchSelectDlg.h"


// CSearchSelectDlg �Ի���

IMPLEMENT_DYNAMIC(CSearchSelectDlg, CDialog)

CSearchSelectDlg::CSearchSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchSelectDlg::IDD, pParent)
    , selectValue(0)
{

}

CSearchSelectDlg::~CSearchSelectDlg()
{
}

void CSearchSelectDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_SEARCH_SELECT_GOODS, selectValue);
}


BEGIN_MESSAGE_MAP(CSearchSelectDlg, CDialog)
END_MESSAGE_MAP()


// CSearchSelectDlg ��Ϣ�������
