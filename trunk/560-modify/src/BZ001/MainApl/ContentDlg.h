#pragma once
#include "resource.h"

// CContentDlg dialog

class CContentDlg : public CDialog
{
	DECLARE_DYNAMIC(CContentDlg)

public:
	CContentDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CContentDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONTENT_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonClose();
};
