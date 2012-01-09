#pragma once
#include "resource.h"

// CPublishWayTwoDlg dialog

class CPublishWayTwoDlg : public CDialog
{
	DECLARE_DYNAMIC(CPublishWayTwoDlg)

public:
	CPublishWayTwoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPublishWayTwoDlg();

// Dialog Data
	enum { IDD = IDD_PUB_WAY_TWO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
