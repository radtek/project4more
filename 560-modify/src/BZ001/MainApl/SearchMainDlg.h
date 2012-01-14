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
public:
	afx_msg void OnTcnSelchangeTabSearchWay(NMHDR *pNMHDR, LRESULT *pResult);
public:
	int GetSearchType()
	{
		return m_nSearchType;
	}
	void SetSearchType(int nType)
	{
		m_nSearchType = nType;
		m_oWayOneDlg.SetSearchType(m_nSearchType);
		m_oWayTwoDlg.SetSearchType(m_nSearchType);
		m_oWayThreeDlg.SetSearchType(m_nSearchType);
	}

	const CSearchCriteria* GetCurSearchCriteria()const
	{
		return m_pCurSearch;
	}

	bool ShouldUseSearchFavorite()const
	{
		return m_bUseSearchFavorite;
	}
	const CSearchFavorite* GetUsedSearchFavorite()const
	{
		return m_oFavoriteDlg.GetUsedSearchFav();
	}
public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonClean();
	afx_msg void OnBnClickedButtonAddFavorite();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonClose();

private:
	CTabCtrl m_tabSearchWay;
	CSearchWayOneDlg	m_oWayOneDlg;
	CSearchWayTwoDlg	m_oWayTwoDlg;
	CSearchWayThreeDlg	m_oWayThreeDlg;
	CSearchFavoriteDlg	m_oFavoriteDlg;
	CSearchCriteria*	m_pCurSearch;
	int	    m_nSearchType;//can be one or the combination of ESearchType
	bool    m_bUseSearchFavorite;
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
