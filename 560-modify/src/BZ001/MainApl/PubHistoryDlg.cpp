// PubHistoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PubHistoryDlg.h"

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

	DWORD dwExtStyle = publishHistory.GetExStyle();
	dwExtStyle |= (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_ONECLICKACTIVATE);
	dwExtStyle &= ~LVS_EX_CHECKBOXES;
	publishHistory.SetExtendedStyle(dwExtStyle);

	initPublishHistory();

	return TRUE;
}

void CPubHistoryDlg::initPublishHistory()
{
	CRect	rect;
	publishHistory.GetClientRect(&rect);
	int cell = rect.Width()/5;
	publishHistory.InsertColumn(0, "出发地", LVCFMT_LEFT, cell);
	publishHistory.InsertColumn(1, "目的地", LVCFMT_LEFT, cell);
	publishHistory.InsertColumn(2, "消息", LVCFMT_LEFT, cell*3);

	publishes = CHistoryManager::getInstance()->getPublishes();
	publishIter	iter;
	int	count = 0;

	for ( iter = publishes.begin(); iter != publishes.end(); iter++ )
	{
		CString	temp;
		CPublishRecord* pRecord = (*iter);
		publishHistory.InsertItem(count, "record");
		temp = pRecord->get("strCityFrom");
		publishHistory.SetItemText(count, 0, temp);
		temp = pRecord->get("strCityTo");
		publishHistory.SetItemText(count, 1, temp);
		temp = pRecord->get("preview");
		publishHistory.SetItemText(count, 2, temp);
		count ++;
	}
}

BEGIN_MESSAGE_MAP(CPubHistoryDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PUBLISH, &CPubHistoryDlg::OnBnClickedButtonPublish)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CPubHistoryDlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CPubHistoryDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CPubHistoryDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CPubHistoryDlg message handlers

void CPubHistoryDlg::OnBnClickedButtonPublish()
{
	// TODO: Add your control notification handler code here
	int	pos = publishHistory.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);

	if ( pos == -1 )
	{
		MessageBox("请选择要发布的记录", "历史记录");
		return;
	}

	pSelectedRecord = publishes[pos];
	autoPublish = true;

	OnOK();
}

void CPubHistoryDlg::OnBnClickedButtonModify()
{
	// TODO: Add your control notification handler code here
	int	pos = publishHistory.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);

	if ( pos == -1 )
	{
		MessageBox("请选择要修改的记录", "历史记录");
		return;
	}

	pSelectedRecord = publishes[pos];
	autoPublish = false;

	OnOK();
}

void CPubHistoryDlg::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	int	pos = publishHistory.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);

	if ( pos == 0 )
	{
		MessageBox("请选择要删除的记录", "历史记录");
		return;
	}

	publishHistory.DeleteItem(pos);
	CHistoryManager::getInstance()->deletePublish(pos);
}

void CPubHistoryDlg::OnBnClickedButtonClose()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
