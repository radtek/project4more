#pragma once
#include "resource.h"
#include "HistoryManager.h"

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

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl			publishHistory;

	CPublishRecord*		pSelectedRecord;

	bool				autoPublish;

private:

	publishVector publishes;

	void	initPublishHistory();

public:
	afx_msg void OnBnClickedButtonPublish();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonDelete();

	
	afx_msg void OnBnClickedButtonClose();
};
