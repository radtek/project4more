#pragma once
#include "resource.h"
#include "SearchCriteria.h"

// CSearchWayTwoDlg dialog

class CSearchWayTwoDlg : public CDialog, public CSearchCriteria
{
	DECLARE_DYNAMIC(CSearchWayTwoDlg)

public:
	CSearchWayTwoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSearchWayTwoDlg();

// Dialog Data
	enum { IDD = IDD_SEARCH_WAY_TWO };

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
