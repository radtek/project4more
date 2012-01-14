#pragma once
#include "resource.h"
#include "afxwin.h"

class CSearchFavorite;
// CSearchFavoriteDlg dialog

#define WM_USE_SEARCH_FAVORITE	(WM_USER+2000)

class CSearchFavoriteDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchFavoriteDlg)

public:
	CSearchFavoriteDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchFavoriteDlg();

// Dialog Data
	enum { IDD = IDD_SEARCH_FAVORITE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonUse();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonRename();
	afx_msg void OnLvnItemchangedListCtrlSearchFavorite(NMHDR *pNMHDR, LRESULT *pResult);
public:
	void RefreshFavorite()
	{
		InitFavoriteListBox();
	}

	const CSearchFavorite* GetUsedSearchFav()const
	{
		return m_pSelSearchFav;
	}
private:
	void InitFavoriteListBox();
	void GetSearchFavName(int nSel, CString& sName);
private:
	CListCtrl m_listCtrlFavorite;
	int		  m_nSelIndex;
	const CSearchFavorite* m_pSelSearchFav;
};
