#pragma once
#include "resource.h"
#include "SearchCriteria.h"
#include "afxwin.h"
#include <list>
using std::list;

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
	afx_msg void OnBnClickedButtonSw2AddDest();
	afx_msg void OnBnClickedButtonSw2AddAllCity();
	afx_msg void OnBnClickedButtonSw2AddAllCounty();
	afx_msg void OnBnClickedButtonSw2Del();
	afx_msg void OnBnClickedButtonSw2Clean();
	afx_msg void OnBnClickedButtonSw2AddKeyWord();
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
	void InitFromProvinceList();
	void FillFromCityList(const CString& sProvince);
	void FillFromCountyList(const CString& sProvince, const CString& sCity);

	void InitToProvinceList();
	void FillToCityList(const CString& sProvince);
	void FillToCountyList(const CString& sProvince, const CString& sCity);
private:
	int m_nSearchType;

	CComboBox m_comboxFromProv;
	CComboBox m_comboxFromCity;
	CComboBox m_comboxFromCounty;
	CComboBox m_comboxKWPN;
	CListBox m_listToProvince;
	CListBox m_listToCity;
	CListBox m_listToCounty;
	CListBox m_listCriteria;

	list<CString> m_selCities;
	list<CString> m_selCounties;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioSw2All();
	afx_msg void OnBnClickedRadioSw2Goods();
	afx_msg void OnBnClickedRadioSw2Cars();
};
