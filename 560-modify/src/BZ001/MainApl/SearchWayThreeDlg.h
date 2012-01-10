#pragma once
#include "resource.h"
#include "SearchCriteria.h"

// CSearchWayThreeDlg dialog

class CSearchWayThreeDlg : public CDialog, public CSearchCriteria
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
public:
	int GetSearchType()
	{
		return m_nSearchType;
	}
	void SetSearchType(int nType)
	{
		m_nSearchType = nType;
	}
private:
	int m_nSearchType;
};
