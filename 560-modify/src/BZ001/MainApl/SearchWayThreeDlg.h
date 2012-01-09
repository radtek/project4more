#pragma once
#include "resource.h"

// CSearchWayThreeDlg dialog

class CSearchWayThreeDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchWayThreeDlg)

public:
	CSearchWayThreeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchWayThreeDlg();

// Dialog Data
	enum { IDD = IDD_SEARCH_WAY_THREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
