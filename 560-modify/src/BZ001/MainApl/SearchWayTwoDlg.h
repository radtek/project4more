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
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioSw2All();
	afx_msg void OnBnClickedRadioSw2Goods();
	afx_msg void OnBnClickedRadioSw2Cars();

	afx_msg void OnCbnSelchangeComboSw2FromProvince();
	afx_msg void OnCbnSelchangeComboSw2FromCity();
	afx_msg void OnCbnSelchangeComboSw2FromCounty();

	afx_msg void OnBnClickedButtonSw2AddDest();
	afx_msg void OnBnClickedButtonSw2AddAllCity();
	afx_msg void OnBnClickedButtonSw2AddAllCounty();
	afx_msg void OnBnClickedButtonSw2Del();
	afx_msg void OnBnClickedButtonSw2Clean();
	afx_msg void OnBnClickedButtonSw2AddKeyWord();

	afx_msg void OnLbnSelchangeListSw2ToProvince();
	afx_msg void OnLbnSelchangeListSw2ToCity();
	afx_msg void OnLbnSelchangeListSw2ToCounty();
private:
	void InitSearchTypeRadio();

	void InitFromProvinceComboBox();
	void FillFromCityComboBox(const CString& sProvince);
	void FillFromCountyComboBox(const CString& sProvince, const CString& sCity);

	void InitToProvinceList();
	void FillToCityList(const CString& sProvince);
	void FillToCountyList(const CString& sProvince, const CString& sCity);

	void FillKeywordCombox();

	void Clean();
	void Confirm();
private:
	enum{eItemData_Province, eItemData_City, eItemData_County, eItemData_Keyword};

	CComboBox m_comboxFromProv;
	CComboBox m_comboxFromCity;
	CComboBox m_comboxFromCounty;
	CComboBox m_comboxKWPN;
	CListBox m_listToProvince;
	CListBox m_listToCity;
	CListBox m_listToCounty;
	CListBox m_listCriteria;

	CString m_sSelStartProv;
	CString m_sSelEndProv;
};
