// SearchSelectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WLRClient.h"
#include "SearchSelectDlg.h"


// CSearchSelectDlg 对话框

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


// CSearchSelectDlg 消息处理程序
