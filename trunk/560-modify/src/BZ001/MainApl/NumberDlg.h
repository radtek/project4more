#pragma once

#include "resource.h"

// CNumberDlg dialog

class CNumberDlg : public CDialog
{
	DECLARE_DYNAMIC(CNumberDlg)

public:
	CNumberDlg(CWnd* pParent, int nEditCtrlID);   // standard constructor
	virtual ~CNumberDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_NUMBER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnBnClickedButtonKbNumZero();
	afx_msg void OnBnClickedButtonKbNumDot();
	afx_msg void OnBnClickedButtonKbNumDZero();
	afx_msg void OnBnClickedButtonKbNumOne();
	afx_msg void OnBnClickedButtonKbNumTwo();
	afx_msg void OnBnClickedButtonKbNumThree();
	afx_msg void OnBnClickedButtonKbNumFour();
	afx_msg void OnBnClickedButtonKbNumFive();
	afx_msg void OnBnClickedButtonKbNumSix();
	afx_msg void OnBnClickedButtonKbNumSeven();
	afx_msg void OnBnClickedButtonKbNumEight();
	afx_msg void OnBnClickedButtonKbNumNine();
	afx_msg void OnBnClickedButtonKbNumBackspace();
	afx_msg void OnBnClickedButtonKbNumClean();
	afx_msg void OnBnClickedButtonKbNumSeven4();

private:
	void AppendEditCtrlText(CString num);

private:
	int m_nEditCtrlID;
	CEdit *m_pEditCtrl;
};
