#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "SearchWayOneDlg.h"
#include "SearchWayTwoDlg.h"
#include "SearchWayThreeDlg.h"
#include "SearchFavoriteDlg.h"
// CSearchMainDlg dialog

class CSearchMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchMainDlg)

public:
	CSearchMainDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchMainDlg();

// Dialog Data
	enum { IDD = IDD_DLG_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CTabCtrl m_tabSearchWay;
	CSearchWayOneDlg	m_oWayOneDlg;
	CSearchWayTwoDlg	m_oWayTwoDlg;
	CSearchWayThreeDlg	m_oWayThreeDlg;
	CSearchFavoriteDlg	m_oFavoriteDlg;
public:
	afx_msg void OnTcnSelchangeTabSearchWay(NMHDR *pNMHDR, LRESULT *pResult);
};
