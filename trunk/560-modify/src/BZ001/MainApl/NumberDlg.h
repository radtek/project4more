#pragma once

#include "resource.h"

// CNumberDlg dialog

class CNumberDlg : public CDialog
{
	DECLARE_DYNAMIC(CNumberDlg)

public:
	CNumberDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNumberDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_NUMBER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
