#pragma once
#include "resource.h"

// CPublishWayOne dialog

class CPublishWayOneDlg : public CDialog
{
	DECLARE_DYNAMIC(CPublishWayOneDlg)

public:
	CPublishWayOneDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPublishWayOneDlg();

// Dialog Data
	enum { IDD = IDD_PUB_WAY_ONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
