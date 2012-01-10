// ContentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ContentDlg.h"
#include "CommDef.h"


// CContentDlg dialog

IMPLEMENT_DYNAMIC(CContentDlg, CDialog)

CContentDlg::CContentDlg(CWnd* pParent, int nEditCtrlID, const vector<CString> *pVecItems, CString *strOut)
	: CDialog(CContentDlg::IDD, pParent), m_nEditCtrlID(nEditCtrlID), m_pVecItems(pVecItems), m_strOut(strOut), m_pListBox(NULL)
{
}

CContentDlg::~CContentDlg()
{
}

void CContentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CContentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rc, rcEdit, rcListOrg, rcList;
	CWnd *pEditCtrl = ((CDialog *)GetParent())->GetDlgItem(m_nEditCtrlID);
	int nCount = 0, nWidth = 0, nHeight = 0, nRow = 0, nColumn = 0;

	if (m_pListBox = (CListBox *)GetDlgItem(IDC_LIST_CONTENT))
	{
		vector<CString>::const_iterator it = m_pVecItems->begin(), end = m_pVecItems->end();
		for(it; it != end; ++it)
		{
			m_pListBox->AddString(*it);
			nCount++;
		}

		if (nCount <= 5)
		{
			nColumn = nCount;
			nRow = 1;
		}
		else
		{
			nColumn = 5;
			nRow = nCount / 5 + (nCount % 5 ? 1 : 0);
		}

		m_pListBox->GetClientRect(&rcListOrg);
		rcList = rcListOrg;
		rcList.top += 20;
		rcList.right = rcList.left + nColumn * 50;
		rcList.bottom = rcList.top + nRow * 14;

		m_pListBox->SetColumnWidth(50);
		m_pListBox->MoveWindow(rcList);

		if (pEditCtrl)
		{
			GetClientRect(&rc);
			pEditCtrl->GetWindowRect(&rcEdit);

			MoveWindow(rcEdit.left, rcEdit.bottom + 2, rc.Width() + rcList.Width() - rcListOrg.Width(), rc.Height() + rcList.Height() - rcListOrg.Height());
		}
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
	if (m_pListBox)
	{
		int nIndex = m_pListBox->GetCurSel();
		if (nIndex > 0 && nIndex < m_pListBox->GetCount())
		{
			m_strOut->Empty();
			m_pListBox->GetText(nIndex, *m_strOut);

			CDialog::OnOK();
		}
	}
}
