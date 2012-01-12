#pragma once
#include "resource.h"
#include "hoverbutton.h"
#include "afxwin.h"

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
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CHoverButton m_btnFromProvince;
	CHoverButton m_btnFromCity;
	CHoverButton m_btnFromCounty;
	CHoverButton m_btnToProvince;
	CHoverButton m_btnToCity;
	CHoverButton m_btnToCounty;
};
