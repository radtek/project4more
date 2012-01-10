// NumberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NumberDlg.h"


// CNumberDlg dialog

IMPLEMENT_DYNAMIC(CNumberDlg, CDialog)

CNumberDlg::CNumberDlg(CWnd* pParent, int nEditCtrlID)
	: CDialog(CNumberDlg::IDD, pParent), m_pEditCtrl(NULL), m_nEditCtrlID(nEditCtrlID)
{
}

CNumberDlg::~CNumberDlg()
{	
}

BOOL CNumberDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rc, rcEdit;

	if (m_pEditCtrl = (CEdit *)((CDialog *)GetParent())->GetDlgItem(m_nEditCtrlID))
	{
		GetClientRect(&rc);
		m_pEditCtrl->GetWindowRect(&rcEdit);

		MoveWindow(rcEdit.left, rcEdit.bottom + 2, rc.Width(), rc.Height());
	}
	return TRUE;
}

void CNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNumberDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_ZEOR1, &CNumberDlg::OnBnClickedButtonKbNumZero)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_DOT, &CNumberDlg::OnBnClickedButtonKbNumDot)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_ZERO2, &CNumberDlg::OnBnClickedButtonKbNumZero)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_D_ZERO, &CNumberDlg::OnBnClickedButtonKbNumDZero)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_ONE, &CNumberDlg::OnBnClickedButtonKbNumOne)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_TWO, &CNumberDlg::OnBnClickedButtonKbNumTwo)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_THREE, &CNumberDlg::OnBnClickedButtonKbNumThree)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_FOUR, &CNumberDlg::OnBnClickedButtonKbNumFour)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_FIVE, &CNumberDlg::OnBnClickedButtonKbNumFive)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_SIX, &CNumberDlg::OnBnClickedButtonKbNumSix)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_SEVEN, &CNumberDlg::OnBnClickedButtonKbNumSeven)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_EIGHT, &CNumberDlg::OnBnClickedButtonKbNumEight)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_NINE, &CNumberDlg::OnBnClickedButtonKbNumNine)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_BACKSPACE, &CNumberDlg::OnBnClickedButtonKbNumBackspace)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_CLEAN, &CNumberDlg::OnBnClickedButtonKbNumClean)
	ON_BN_CLICKED(IDC_BUTTON_KB_NUM_SEVEN4, &CNumberDlg::OnBnClickedButtonKbNumSeven4)
END_MESSAGE_MAP()


// CNumberDlg message handlers

void CNumberDlg::OnBnClickedButtonKbNumZero()
{
	// TODO: Add your control notification handler code here
	AppendEditCtrlText("1");
}

void CNumberDlg::OnBnClickedButtonKbNumDot()
{
	// TODO: Add your control notification handler code here
	AppendEditCtrlText(".");
}

void CNumberDlg::OnBnClickedButtonKbNumDZero()
{
	// TODO: Add your control notification handler code here
	AppendEditCtrlText("00");
}

void CNumberDlg::OnBnClickedButtonKbNumOne()
{
	// TODO: Add your control notification handler code here
	AppendEditCtrlText("1");
}

void CNumberDlg::OnBnClickedButtonKbNumTwo()
{
	// TODO: Add your control notification handler code here
	AppendEditCtrlText("2");
}

void CNumberDlg::OnBnClickedButtonKbNumThree()
{
	// TODO: Add your control notification handler code here
	AppendEditCtrlText("3");
}

void CNumberDlg::OnBnClickedButtonKbNumFour()
{
	// TODO: Add your control notification handler code here
	AppendEditCtrlText("4");
}

void CNumberDlg::OnBnClickedButtonKbNumFive()
{
	// TODO: Add your control notification handler code here
	AppendEditCtrlText("5");
}

void CNumberDlg::OnBnClickedButtonKbNumSix()
{
	// TODO: Add your control notification handler code here
	AppendEditCtrlText("6");
}

void CNumberDlg::OnBnClickedButtonKbNumSeven()
{
	// TODO: Add your control notification handler code here
	AppendEditCtrlText("7");
}

void CNumberDlg::OnBnClickedButtonKbNumEight()
{
	// TODO: Add your control notification handler code here
	AppendEditCtrlText("8");
}

void CNumberDlg::OnBnClickedButtonKbNumNine()
{
	// TODO: Add your control notification handler code here
	AppendEditCtrlText("9");
}

void CNumberDlg::OnBnClickedButtonKbNumBackspace()
{
	// TODO: Add your control notification handler code here
	if (m_pEditCtrl)
	{
		CString text;

		m_pEditCtrl->GetWindowText(text);
		text.Delete(text.GetLength() - 1);
		m_pEditCtrl->SetWindowText(text);
	}
}

void CNumberDlg::OnBnClickedButtonKbNumClean()
{
	// TODO: Add your control notification handler code here
	if (m_pEditCtrl)
		m_pEditCtrl->SetWindowText("");
}

void CNumberDlg::OnBnClickedButtonKbNumSeven4()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

// Private functions.
void CNumberDlg::AppendEditCtrlText(CString num)
{
	if (m_pEditCtrl)
	{
		CString text;

		m_pEditCtrl->GetWindowText(text);

		if (num == ".")
		{
			if (text.Find(num) == -1)
				text += num;
		}
		else
			text += num;
		
		m_pEditCtrl->SetWindowText(text);
	}
}
