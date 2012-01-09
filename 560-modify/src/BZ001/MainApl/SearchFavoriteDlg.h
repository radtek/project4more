#pragma once
#include "resource.h"

// CSearchFavoriteDlg dialog

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

	DECLARE_MESSAGE_MAP()
};
