#pragma once
#include "resource.h"

// CSearchWayTwoDlg dialog

class CSearchWayTwoDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchWayTwoDlg)

public:
	CSearchWayTwoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchWayTwoDlg();

// Dialog Data
	enum { IDD = IDD_SEARCH_WAY_TWO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
