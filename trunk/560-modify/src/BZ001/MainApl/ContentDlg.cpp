// ContentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ContentDlg.h"
#include "CommDef.h"


// CContentDlg dialog

IMPLEMENT_DYNAMIC(CContentDlg, CDialog)

CContentDlg::CContentDlg(CWnd* pParent, CWnd* pCtrlWnd, const vector<CString> *pVecItems, CString *strOut)
	: CDialog(CContentDlg::IDD, pParent), m_pCtrlWnd(pCtrlWnd), m_pVecItems(pVecItems), m_strOut(strOut)
{
}

CContentDlg::~CContentDlg()
{
}

void CContentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_staticTitle);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_LIST_CONTENT, m_listContent);
}

BOOL CContentDlg::OnInitDialog()
{
	static int s_nColWidth = 50;
	CRect rc, rcStatic, rcBtn, rcList;
	int nCount = 0, nWidth = 0, nHeight = 0, nRow = 0, nColumn = 0;

	CDialog::OnInitDialog();

	vector<CString>::const_iterator it = m_pVecItems->begin(), end = m_pVecItems->end();
	for(it; it != end; ++it)
	{
		m_listContent.AddString(*it);
		nCount++;
	}

	if (nCount <= 5)
	{
		nColumn = 5;
		nRow = 1;
	}
	else
	{
		nColumn = 5;
		nRow = nCount / 5 + (nCount % 5 ? 1 : 0);
	}

	m_staticTitle.GetClientRect(&rcStatic);
	m_listContent.SetColumnWidth(s_nColWidth);
	m_listContent.MoveWindow(rcStatic.left, rcStatic.bottom + 2, nColumn * s_nColWidth + 2, nRow * m_listContent.GetItemHeight(0) + 4);

	m_btnClose.GetClientRect(rcBtn);
	m_listContent.GetClientRect(&rcList);
	m_staticTitle.MoveWindow(rcStatic.left, rcStatic.top, rcList.Width() - rcBtn.Width() - 4, rcStatic.Height());
	m_btnClose.MoveWindow(rcList.Width() - rcBtn.Width(), rcBtn.top, rcBtn.Width(), rcBtn.Height());

	if (m_pCtrlWnd)
	{
		m_pCtrlWnd->GetWindowRect(&rc);
		MoveWindow(rc.left, rc.bottom + 2, rcList.Width() + 6, rcStatic.Height() + rcList.Height() + 8);
	}
	return TRUE;
}


BEGIN_MESSAGE_MAP(CContentDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CContentDlg::OnBnClickedButtonClose)
	ON_LBN_SELCHANGE(IDC_LIST_CONTENT, &CContentDlg::OnLbnSelchangeListContent)
END_MESSAGE_MAP()


// CContentDlg message handlers

void CContentDlg::OnBnClickedButtonClose()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CContentDlg::OnLbnSelchangeListContent()
{
	// TODO: Add your control notification handler code here
	int nIndex = m_listContent.GetCurSel();
	if (nIndex >= 0 && nIndex < m_listContent.GetCount())
	{
		m_strOut->Empty();
		m_listContent.GetText(nIndex, *m_strOut);

		CDialog::OnOK();
	}
}
