// PubHistoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PubHistoryDlg.h"
#include "HistoryManager.h"

// CPubHistoryDlg dialog

IMPLEMENT_DYNAMIC(CPubHistoryDlg, CDialog)

CPubHistoryDlg::CPubHistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPubHistoryDlg::IDD, pParent)
{
	
}

CPubHistoryDlg::~CPubHistoryDlg()
{
}

void CPubHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PUB_HISTORY, publishHistory);
}

BOOL CPubHistoryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	initPublishHistory();

	return TRUE;
}

void CPubHistoryDlg::initPublishHistory()
{
	CRect	rect;
	publishHistory.GetClientRect(&rect);
	int cell = rect.Width()/5;
	publishHistory.InsertColumn(0, "出发", LVCFMT_LEFT, cell);
	publishHistory.InsertColumn(1, "到达", LVCFMT_LEFT, cell);
	publishHistory.InsertColumn(2, "消息", LVCFMT_LEFT, cell*3);

	publishHistory.ModifyStyle(0, LVS_REPORT, NULL);
	publishHistory.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	publishList publishes = CHistoryManager::getInstance()->getPublishes();
	publishIter	iter;
	int	count = 0;

	for ( iter = publishes.begin(); iter != publishes.end(); iter++ )
	{
		CString	temp;
		CPublishRecord* pRecord = (*iter);
		publishHistory.InsertItem(pRecord->sn, "aaa");
		temp = pRecord->get("fromCity");
		publishHistory.SetItemText(pRecord->sn, 0, temp);
		temp = pRecord->get("toCity");
		publishHistory.SetItemText(pRecord->sn, 1, temp);
		temp = pRecord->get("msg");
		publishHistory.SetItemText(pRecord->sn, 2, temp);
	}
}

BEGIN_MESSAGE_MAP(CPubHistoryDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PUBLISH, &CPubHistoryDlg::OnBnClickedButtonPublish)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CPubHistoryDlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CPubHistoryDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CPubHistoryDlg message handlers

void CPubHistoryDlg::OnBnClickedButtonPublish()
{
	// TODO: Add your control notification handler code here
}

void CPubHistoryDlg::OnBnClickedButtonModify()
{
	// TODO: Add your control notification handler code here
}

void CPubHistoryDlg::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	POSITION	pos = publishHistory.GetFirstSelectedItemPosition();
}
