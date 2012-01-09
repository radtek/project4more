#pragma once
#include "resource.h"

// CSearchWayOneDlg dialog

class CSearchWayOneDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchWayOneDlg)

public:
	CSearchWayOneDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchWayOneDlg();

// Dialog Data
	enum { IDD = IDD_SEARCH_WAY_ONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
