#pragma once
#include "resource.h"

// CPubHistoryDlg dialog

class CPubHistoryDlg : public CDialog
{
	DECLARE_DYNAMIC(CPubHistoryDlg)

public:
	CPubHistoryDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPubHistoryDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PUB_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
